#pragma once

#include "Elysium/Renderer/RenderAPI.h"

namespace Elysium {
	class OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void Init() override;

		virtual void Clear(const vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

		virtual void SetViewport(u32 x, u32 y, u32 width, u32 height) override;
	};
}