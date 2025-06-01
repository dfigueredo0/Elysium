#include <Elysium.h>

#include <imgui.h>

class ExampleLayer : public Elysium::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		m_VertexArray.reset(Elysium::VertexArray::Create());

		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 0.85f, 0.85f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.73f, 0.92f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.85f, 0.0f, 0.85f, 1.0f
		};

		std::shared_ptr<Elysium::VertexBuffer> vBuffer;
		vBuffer.reset(Elysium::VertexBuffer::Create(vertices, sizeof(vertices)));
		Elysium::BufferLayout layout = {
			{ Elysium::ShaderDataType::Float3, "a_Position" },
			{ Elysium::ShaderDataType::Float4, "a_Color" }
		};
		vBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vBuffer);

		u32 indices[3] = { 0, 1, 2 };
		std::shared_ptr<Elysium::IndexBuffer> iBuffer;
		iBuffer.reset(Elysium::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(iBuffer);

		m_SquareVA.reset(Elysium::VertexArray::Create());

		float sqVertices[12] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Elysium::VertexBuffer> SquareVB;
		SquareVB.reset(Elysium::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		SquareVB->SetLayout({
			{ Elysium::ShaderDataType::Float3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(SquareVB);

		u32 points[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Elysium::IndexBuffer> SquareIB;
		SquareIB.reset(Elysium::IndexBuffer::Create(points, sizeof(points) / sizeof(u32)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		std::string vertexSource = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Elysium::Shader(vertexSource, fragmentSource));

		std::string vertexSrc = R"(
			#version 450 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_BlueShader.reset(new Elysium::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Elysium::Timestep ts) override {
		if (Elysium::Input::IsKeyPressed(ELY_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		} else if (Elysium::Input::IsKeyPressed(ELY_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Elysium::Input::IsKeyPressed(ELY_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		} else if (Elysium::Input::IsKeyPressed(ELY_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}

		if (Elysium::Input::IsKeyPressed(ELY_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if (Elysium::Input::IsKeyPressed(ELY_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		Elysium::RenderCommand::Clear({ 0.13f, 0.13f, 0.13f, 1.0f });

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Elysium::Renderer::BeginScene(m_Camera);


		Elysium::Renderer::Submit(m_BlueShader, m_SquareVA);
		Elysium::Renderer::Submit(m_Shader, m_VertexArray);

		Elysium::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override {

	}

	void OnEvent(Elysium::Event& e) override {
	}

private:
	std::shared_ptr<Elysium::Shader> m_Shader;
	std::shared_ptr<Elysium::Shader> m_BlueShader;

	std::shared_ptr<Elysium::VertexArray> m_VertexArray;
	std::shared_ptr<Elysium::VertexArray> m_SquareVA;

	Elysium::OrthographicCamera m_Camera;
	vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 30.0f;
};

class Sandbox : public Elysium::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
	}
};

Elysium::Application* Elysium::CreateApplication() {
	return new Sandbox();
}