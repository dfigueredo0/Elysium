#include "elypch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Elysium {
	VertexBuffer* VertexBuffer::Create(float* vertices, u32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			ELY_CORE_ASSERT(false, "Renderer API None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::DirectX3D:
			ELY_CORE_ASSERT(false, "Renderer API DirectX3D is currently not supported!");
			return nullptr;
		case RendererAPI::Vulkan:
			ELY_CORE_ASSERT(false, "Renderer API Vulkan is currently not supported!");
			return nullptr;
		}
		ELY_CORE_ASSERT(false, "Unknown Renderer!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(u32* indices, u32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			ELY_CORE_ASSERT(false, "Renderer API None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		case RendererAPI::DirectX3D:
			ELY_CORE_ASSERT(false, "Renderer API DirectX3D is currently not supported!");
			return nullptr;
		case RendererAPI::Vulkan:
			ELY_CORE_ASSERT(false, "Renderer API Vulkan is currently not supported!");
			return nullptr;
		}
		ELY_CORE_ASSERT(false, "Unknown Renderer!");
		return nullptr;
	}
}