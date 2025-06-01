#include "elypch.h"

#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Elysium {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case Elysium::RenderAPI::API::None:
			break;
		case Elysium::RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
		case Elysium::RenderAPI::API::DirectX3D:
			break;
		case Elysium::RenderAPI::API::Vulkan:
			break;
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown Renderer!");
		return nullptr;
	}
}