#include "elypch.h"

#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Elysium {
	Ref<Texture2D> Texture2D::Create(u32 width, u32 height, void* data, GLenum internalFormat, GLenum dataFormat)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			ELY_CORE_ASSERT(false, "RenderAPI::None is not currently supported!");
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height, data);
		case RenderAPI::API::DirectX3D:
			ELY_CORE_ASSERT(false, "RenderAPI::DirectX3D is not currently supported!");
		case RenderAPI::API::Vulkan:
			ELY_CORE_ASSERT(false, "RenderAPI::Vulkan is not currently supported!");
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			ELY_CORE_ASSERT(false, "RenderAPI::None is not currently supported!");
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		case RenderAPI::API::DirectX3D:
			ELY_CORE_ASSERT(false, "RenderAPI::DirectX3D is not currently supported!");
		case RenderAPI::API::Vulkan:
			ELY_CORE_ASSERT(false, "RenderAPI::Vulkan is not currently supported!");
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}