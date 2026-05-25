#include "elypch.h"

#include "RenderContext.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"


namespace Elysium {
    Scope<RenderContext> RenderContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::None:
                break;
        case RenderAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        case RenderAPI::API::DirectX3D:
            break;
        case RenderAPI::API::Vulkan:
            break;
        default:
            break;
        }

        ELY_CORE_ASSERT(false, "Unknown RenderAPI");
        return nullptr;
    }
}