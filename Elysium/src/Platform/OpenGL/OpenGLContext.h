#pragma once

#include "Elysium/Renderer/RenderContext.h"

struct GLFWwindow;

namespace Elysium {
	class OpenGLContext : public RenderContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}