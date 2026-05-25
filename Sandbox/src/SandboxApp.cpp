#include <Elysium.h>
#include <Elysium/Core/EntryPoint.h>
#include <imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"

class ExampleLayer : public Elysium::Layer {
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f), m_SquarePos(0.0f, 0.0f, 0.0f) {
		m_VertexArray = Elysium::VertexArray::Create();

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.85f, 0.85f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.73f, 0.92f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.85f, 0.0f, 0.85f, 1.0f
		};

		Elysium::Ref<Elysium::VertexBuffer> vBuffer;
		vBuffer = Elysium::VertexBuffer::Create(vertices, sizeof(vertices));
		Elysium::BufferLayout layout = {
			{ Elysium::ShaderDataType::Float3, "a_Position" },
			{ Elysium::ShaderDataType::Float4, "a_Color" }
		};
		vBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vBuffer);

		u32 indices[3] = { 0, 1, 2 };
		Elysium::Ref<Elysium::IndexBuffer> iBuffer;
		iBuffer = Elysium::IndexBuffer::Create(indices, 3);
		m_VertexArray->SetIndexBuffer(iBuffer);

		m_SquareVA = Elysium::VertexArray::Create();


		std::string vertexSource = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
						
			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
			
		)";

		std::string fragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 rgba;	
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				rgba = vec4(0.2, 0.4, 0.8, 1.0);
			}
		)";

		m_BlueShader = Elysium::Shader::Create("FlatBlueColor", vertexSrc, fragmentSrc);

		std::string textureVertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main() {
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
			
		)";

		std::string textureFragmentSrc = R"(
			#version 450 core
			
			layout(location = 0) out vec4 rgba;	
			
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main() {
				rgba = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader = Elysium::Shader::Create("Texture", textureVertexSrc, textureFragmentSrc);
		std::dynamic_pointer_cast<Elysium::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Elysium::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Elysium::Timestep ts) override {
		m_CameraController.OnUpdate(ts);

		if (Elysium::Input::IsKeyPressed(ELY_KEY_J)) {
			m_SquarePos.x -= m_SquareMoveSpeed * ts;
		}
		else if (Elysium::Input::IsKeyPressed(ELY_KEY_L)) {
			m_SquarePos.x += m_SquareMoveSpeed * ts;
		}

		if (Elysium::Input::IsKeyPressed(ELY_KEY_K)) {
			m_SquarePos.y -= m_SquareMoveSpeed * ts;
		}
		else if (Elysium::Input::IsKeyPressed(ELY_KEY_I)) {
			m_SquarePos.y += m_SquareMoveSpeed * ts;
		}

		Elysium::RenderCommand::Clear({ 0.13f, 0.13f, 0.13f, 1.0f });


		Elysium::Renderer::BeginScene(m_CameraController.GetCamera());

		mat4 transform = Math::translateMatrix(m_SquarePos);

		Elysium::Renderer::Submit(m_TextureShader, m_SquareVA, transform);
		Elysium::Renderer::Submit(m_Shader, m_VertexArray);

		Elysium::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

	void OnEvent(Elysium::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	Elysium::ShaderLibrary m_ShaderLibrary;
	Elysium::Ref<Elysium::Shader> m_Shader;
	Elysium::Ref<Elysium::Shader> m_BlueShader;
	Elysium::Ref<Elysium::Shader> m_TextureShader;

	Elysium::Ref<Elysium::VertexArray> m_VertexArray;
	Elysium::Ref<Elysium::VertexArray> m_SquareVA;

	Elysium::Ref<Elysium::Texture2D> m_Texture;

	Elysium::OrthographicCameraController m_CameraController;

	vec3 m_SquarePos;
	float m_SquareMoveSpeed = 1.0f;
};

class Sandbox : public Elysium::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {
	}
};

Elysium::Application* Elysium::CreateApplication() {
	return new Sandbox();
}