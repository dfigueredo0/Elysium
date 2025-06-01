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

		virtual void Clear(const vec4& color) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}