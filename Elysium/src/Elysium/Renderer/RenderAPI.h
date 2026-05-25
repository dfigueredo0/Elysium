#pragma once

#include "Elysium/Math/Math.hpp"
#include "VertexArray.h"

namespace Elysium {
	class RenderAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			DirectX3D = 2,
			Vulkan = 3
		};

		virtual void Init() = 0;

		virtual void Clear(const vec4& color) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		virtual void SetViewport(u32 x, u32 y, u32 width, u32 height) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}