#include "elypch.h"
#include "Application.h"
#include "Input.h"

#include "Elysium/Log.h"

#include "Math/Types.h"

#include <glad/glad.h>

namespace Elysium
{
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type)
		{
		case Elysium::ShaderDataType::Int:
			return GL_INT;
		case Elysium::ShaderDataType::Int2:
			return GL_INT;
		case Elysium::ShaderDataType::Int3:
			return GL_INT;
		case Elysium::ShaderDataType::Int4:
			return GL_INT;
		case Elysium::ShaderDataType::Float:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Float2:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Float3:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Float4:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Vec2:
			return GL_FLOAT_VEC2;
		case Elysium::ShaderDataType::Vec3:
			return GL_FLOAT_VEC3;
		case Elysium::ShaderDataType::Vec4:
			return GL_FLOAT_VEC4;
		case Elysium::ShaderDataType::Mat3:
			return GL_FLOAT_MAT3;
		case Elysium::ShaderDataType::Mat4:
			return GL_FLOAT_MAT4;
		case Elysium::ShaderDataType::Bool:
			return GL_BOOL;
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown ShaderDataType!")
		return 0;
	}

	Application::Application()
	{
		ELY_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(ELY_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.85f, 0.85f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.73f, 0.92f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.85f, 0.0f, 0.85f, 1.0f
		};

		{
			m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};
			m_VertexBuffer->SetLayout(layout);
		}

		u32 index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& e : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				e.GetComponentCount(), 
				ShaderDataTypeToOpenGLType(e.type), 
				e.normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(),
				(const void*) e.offset);
			index++;
		}


		u32 indices[3] = { 0, 1, 2 };

		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

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

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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