#pragma once

#include "../Core.h"

#include "Elysium/Math/Math.hpp"

#include <string>

namespace Elysium{
	class Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const mat4& matrix);
	private:
		u32 m_RendererID;
	};
}