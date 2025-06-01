#pragma once

#include "Elysium/Renderer/RenderAPI.h"

namespace Elysium {
	class OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void Clear(const vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}