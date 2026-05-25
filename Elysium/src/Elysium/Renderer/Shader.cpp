#include "elypch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Elysium {
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			ELY_CORE_ASSERT(false, "RenderAPI::None is currently not supported")
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		case RenderAPI::API::DirectX3D:
			ELY_CORE_ASSERT(false, "RenderAPI::DirectX3D is currently not supported")
		case RenderAPI::API::Vulkan:
			ELY_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported")
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			ELY_CORE_ASSERT(false, "RenderAPI::None is currently not supported")
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
		case RenderAPI::API::DirectX3D:
			ELY_CORE_ASSERT(false, "RenderAPI::DirectX3D is currently not supported")
		case RenderAPI::API::Vulkan:
			ELY_CORE_ASSERT(false, "RenderAPI::Vulkan is currently not supported")
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		ELY_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ELY_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}