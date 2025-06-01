#pragma once

#include "RenderAPI.h"

namespace Elysium{
	class RenderCommand {
	public:
		inline static void Clear(const vec4& color) {
			s_RenderAPI->Clear(color);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			s_RenderAPI->DrawIndexed(vertexArray);
		}
	private:
		static RenderAPI* s_RenderAPI;
	};
}