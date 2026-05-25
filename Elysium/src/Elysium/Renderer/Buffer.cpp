#include "elypch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Elysium {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, u32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ELY_CORE_ASSERT(false, "Renderer API None is currently not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		case RenderAPI::API::DirectX3D:
			ELY_CORE_ASSERT(false, "Renderer API DirectX3D is currently not supported!");
			return nullptr;
		case RenderAPI::API::Vulkan:
			ELY_CORE_ASSERT(false, "Renderer API Vulkan is currently not supported!");
			return nullptr;
		}
		ELY_CORE_ASSERT(false, "Unknown Renderer!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(u32* indices, u32 size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ELY_CORE_ASSERT(false, "Renderer API None is currently not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
		case RenderAPI::API::DirectX3D:
			ELY_CORE_ASSERT(false, "Renderer API DirectX3D is currently not supported!");
			return nullptr;
		case RenderAPI::API::Vulkan:
			ELY_CORE_ASSERT(false, "Renderer API Vulkan is currently not supported!");
			return nullptr;
		}
		ELY_CORE_ASSERT(false, "Unknown Renderer!");
		return nullptr;
	}
}