#include "elypch.h"

#include "OpenGLTexture.h"

namespace Elysium {
	OpenGLTexture2D::OpenGLTexture2D(u32 width, u32 height, void* data, GLenum internalFormat, GLenum dataFormat) : m_Width(width), m_Height(height)
	{
		ELY_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // want to paramerterize GL_LINEAR and GL_NEAREST
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	}
	
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
	{
		ELY_PROFILE_FUNCTION();

		int channels = 0;
		auto data = 1; //data would be image texture use own file extnesion like .elys

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, (const void*)data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		ELY_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, u32 size)
	{
		ELY_PROFILE_FUNCTION();

		u32 bytesPerPixel = m_DataFormat == GL_RGBA ? 4 : 3;
		ELY_CORE_ASSERT(size == m_Width * m_Height * bytesPerPixel, "Data must be entire texture!")
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(u32 slot) const
	{
		ELY_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);
	}
}