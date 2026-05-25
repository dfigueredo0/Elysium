#include "elypch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Elysium {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		ELY_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		ELY_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ELY_CORE_ASSERT(status, "Failed to initialize GLAD");

		ELY_CORE_INFO("OpenGL Renderer: {0}, {1}", (const char*)glGetString(0x1F00), (const char*)glGetString(0x1F01));

#ifdef ELY_ENABLE_ASSERTS
		int versionMajor, versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		ELY_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Elyisum requires at least OpenGL 4.5");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		ELY_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}