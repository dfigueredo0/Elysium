#pragma once

#include "Elysium/Renderer/Texture.h"

#include <glad/glad.h>

namespace Elysium {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(u32 width, u32 height, void* data, GLenum internalFormat, GLenum dataFormat);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
		
		virtual void SetData(void* data, u32 size) override;

		virtual void Bind(u32 slot = 0) const override;
	private:
		std::string m_Path;
		GLenum m_InternalFormat, m_DataFormat;
		u32 m_Width;
		u32 m_Height;
		u32 m_RendererID;
	};
}