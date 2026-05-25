#pragma once

#include "Elysium/Renderer/Shader.h"
#include "Elysium/Math/Math.hpp"

// TODO: TEMP FIX
typedef unsigned int GLenum;

namespace Elysium {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat3(const std::string& name, const vec3& value) override;
		virtual void SetFloat4(const std::string& name, const vec4& value) override;
		virtual void SetMat4(const std::string& name, const mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const vec2& values);
		void UploadUniformFloat3(const std::string& name, const vec3& values);
		void UploadUniformFloat4(const std::string& name, const vec4& values);

		void UploadUniformMat3(const std::string& name, const mat3& matrix);
		void UploadUniformMat4(const std::string& name, const mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& src);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);

		u32 m_RendererID;
		std::string m_Name;
	};
}