#include "elypch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Elysium {
	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI;
}