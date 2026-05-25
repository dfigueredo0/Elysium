#pragma once

#include "RenderAPI.h"

namespace Elysium{
	class RenderCommand {
	public:
		inline static void Init() {
			s_RenderAPI->Init();
		}

		inline static void Clear(const vec4& color) {
			s_RenderAPI->Clear(color);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RenderAPI->DrawIndexed(vertexArray);
		}

		inline static void SetViewport(u32 x, u32 y, u32 width, u32 height) {
			s_RenderAPI->SetViewport(x, y, width, height);
		}
	private:
		static RenderAPI* s_RenderAPI;
	};
}