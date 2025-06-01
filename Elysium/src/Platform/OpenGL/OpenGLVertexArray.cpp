#include "elypch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Elysium {
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type)
		{
		case Elysium::ShaderDataType::Int:
			return GL_INT;
		case Elysium::ShaderDataType::Int2:
			return GL_INT;
		case Elysium::ShaderDataType::Int3:
			return GL_INT;
		case Elysium::ShaderDataType::Int4:
			return GL_INT;
		case Elysium::ShaderDataType::Float:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Float2:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Float3:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Float4:
			return GL_FLOAT;
		case Elysium::ShaderDataType::Vec2:
			return GL_FLOAT_VEC2;
		case Elysium::ShaderDataType::Vec3:
			return GL_FLOAT_VEC3;
		case Elysium::ShaderDataType::Vec4:
			return GL_FLOAT_VEC4;
		case Elysium::ShaderDataType::Mat3:
			return GL_FLOAT_MAT3;
		case Elysium::ShaderDataType::Mat4:
			return GL_FLOAT_MAT4;
		case Elysium::ShaderDataType::Bool:
			return GL_BOOL;
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown ShaderDataType!")
			return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		ELY_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		u32 index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& e : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				e.GetComponentCount(),
				ShaderDataTypeToOpenGLType(e.type),
				e.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)e.offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}