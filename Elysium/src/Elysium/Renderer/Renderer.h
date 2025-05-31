#pragma once

namespace Elysium {
	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
		DirectX3D = 2,
		Vulkan = 3
	};

	class Renderer {
	public:
		inline static RendererAPI SetAPI(RendererAPI API) { s_RendererAPI = API; }
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;

	};
}