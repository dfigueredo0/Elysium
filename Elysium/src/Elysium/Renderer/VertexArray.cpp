#include "elypch.h"

#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Elysium {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case Elysium::RendererAPI::None:
			break;
		case Elysium::RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		case Elysium::RendererAPI::DirectX3D:
			break;
		case Elysium::RendererAPI::Vulkan:
			break;
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown Renderer!");
		return nullptr;
	}
}