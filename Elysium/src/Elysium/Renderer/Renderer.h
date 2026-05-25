#pragma once

#include "Shader.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Texture.h"

namespace Elysium {

	class Renderer {
	public:
		static void Init();
		static void OnWindowResize(u32 width, u32 height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const mat4& transform = mat4(1.0f));

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		struct SceneData {
			mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const vec2& position, const vec2& size, const vec4& color);
		static void DrawQuad(const vec3& position, const vec2& size, const vec4& color);
		static void DrawQuad(const vec2& position, const vec2& size, const Ref<Texture2D> texture, float tileFactor = 1.0f, const vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const vec3& position, const vec2& size, const Ref<Texture2D> texture, float tileFactor = 1.0f, const vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

		static void DrawRotatedQuad(const vec2& position, const vec2& size, const vec4& color, float rotation = 0);
		static void DrawRotatedQuad(const vec3& position, const vec2& size, const vec4& color, float rotation = 0);
		static void DrawRotatedQuad(const vec2& position, const vec2& size, const Ref<Texture2D> texture, float rotation = 0, float tileFactor = 1.0f, const vec4& tintColor = {1.0f, 1.0f, 1.0f, 1.0f});
		static void DrawRotatedQuad(const vec3& position, const vec2& size, const Ref<Texture2D> texture, float rotation = 0, float tileFactor = 1.0f, const vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
	};
}