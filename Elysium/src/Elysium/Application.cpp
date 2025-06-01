#include "elypch.h"
#include "Application.h"
#include "Input.h"

#include "Elysium/Log.h"

#include "Math/Types.h"

#include <glad/glad.h>

namespace Elysium
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ELY_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(ELY_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.85f, 0.85f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.73f, 0.92f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.85f, 0.0f, 0.85f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vBuffer;
		vBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vBuffer);

		u32 indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> iBuffer;
		iBuffer.reset(IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(iBuffer);

		m_SquareVA.reset(VertexArray::Create());
		
		float sqVertices[12] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> SquareVB;
		SquareVB.reset(VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		SquareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
		});
		m_SquareVA->AddVertexBuffer(SquareVB);

		u32 points[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(points, sizeof(points) / sizeof(u32)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		std::string vertexSource = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
			
		)";

		std::string fragmentSource = R"(
			#version 450 core
			
			layout(location = 0) out vec4 rgba;
	
			in vec3 v_Position;	
			in vec4 v_Color;
	
			void main() {
				rgba = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
			
		)";

		std::string fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 rgba;
	
			in vec3 v_Position;	
	
			void main() {
				rgba = vec4(0.2f, 0.4f, 0.8f, 1.0);
			}
		)";

		m_BlueShader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.13f, 0.13f, 0.13f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_BlueShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ELY_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}