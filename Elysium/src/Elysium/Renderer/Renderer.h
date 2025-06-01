#pragma once

#include "Shader.h"
#include "RenderCommand.h"
#include "Camera.h"

namespace Elysium {

	class Renderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	private:
		struct SceneData {
			mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}