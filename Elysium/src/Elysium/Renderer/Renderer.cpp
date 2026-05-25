#include "elypch.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

typedef struct GLenum;

namespace Elysium {
	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		ELY_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(u32 width, u32 height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	
	}
	
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const mat4& transform)
	{
		shader->Bind();
		std::static_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::static_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer2D::Init()
	{
		ELY_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float sqVertices[20] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> SquareVB;
		SquareVB = VertexBuffer::Create(sqVertices, sizeof(sqVertices));
		SquareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data->QuadVertexArray->AddVertexBuffer(SquareVB);

		u32 points[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> SquareIB;
		SquareIB = IndexBuffer::Create(points, sizeof(points) / sizeof(u32));
		s_Data->QuadVertexArray->SetIndexBuffer(SquareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1, (void*)1, (GLenum)0x8058, (GLenum)0x1908); // TODO: data and format parameters fixing
		u32 whiteTextureData = 0xFFFFFFFF;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(u32));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}
	
	void Renderer2D::Shutdown()
	{
		ELY_PROFILE_FUNCTION();

		delete s_Data;
	}
	
	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		ELY_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}
	
	void Renderer2D::EndScene()
	{
		ELY_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const vec4& color)
	{
		ELY_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();

		mat4 transform = Math::translateMatrix(position) * Math::scaleMatrix(vec3(size.x, size.y, 1.0f));
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const Ref<Texture2D> texture, float tileFactor, const vec4& tintColor)
	{
		ELY_PROFILE_FUNCTION();

		//s_Data->TextureShader->SetFloat4("u_Color", color); TODO: Add a way to keep color for a tint and/or opacity, would need a data struct for this.
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TileFactor", tileFactor);
		texture->Bind();

		mat4 transform = Math::translateMatrix(position) * Math::scaleMatrix(vec3(size.x, size.y, 1.0f));
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const vec4& color)
	{
		DrawQuad(vec3(position.x, position.y, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const Ref<Texture2D> texture, float tileFactor, const vec4& tintColor)
	{
		DrawQuad(vec3(position.x, position.y, 0.0f), size, texture, tileFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, const vec4& color, float rotation)
	{
		ELY_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();

		mat4 transform = Math::translateMatrix(position) * Math::scaleMatrix(vec3(size.x, size.y, 1.0f)) * Math::rotateMatrix(rotation, {0.0f, 0.0f, 1.0f});
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, const Ref<Texture2D> texture, float rotation, float tileFactor, const vec4& tintColor)
	{
		ELY_PROFILE_FUNCTION();

		//s_Data->TextureShader->SetFloat4("u_Color", color); TODO: Add a way to keep color for a tint and/or opacity, would need a data struct for this.
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TileFactor", tileFactor);
		texture->Bind();

		mat4 transform = Math::translateMatrix(position) * Math::scaleMatrix(vec3(size.x, size.y, 1.0f)) * Math::rotateMatrix(rotation, { 0.0f, 0.0f, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, const vec4& color, float rotation)
	{
		DrawRotatedQuad(vec3(position.x, position.y, 0.0f), size, color, rotation);
	}

	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, const Ref<Texture2D> texture, float rotation, float tileFactor, const vec4& tintColor)
	{
		DrawRotatedQuad(vec3(position.x, position.y, 0.0f), size, texture, rotation, tileFactor, tintColor);
	}
}