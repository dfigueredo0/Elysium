#pragma once

namespace Elysium {
	enum class ShaderDataType : u8 {
		None = 0, 
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Vec2, Vec3, Vec4,
		Mat3, Mat4,
		Bool
	};

	static u32 ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case Elysium::ShaderDataType::Int:
			return 4;
		case Elysium::ShaderDataType::Int2:
			return 8;
		case Elysium::ShaderDataType::Int3:
			return 12;
		case Elysium::ShaderDataType::Int4:
			return 16;
		case Elysium::ShaderDataType::Float:
			return 4;
		case Elysium::ShaderDataType::Float2:
			return 8;
		case Elysium::ShaderDataType::Float3:
			return 12;
		case Elysium::ShaderDataType::Float4:
			return 16;
		case Elysium::ShaderDataType::Vec2:
			return 8;
		case Elysium::ShaderDataType::Vec3:
			return 12;
		case Elysium::ShaderDataType::Vec4:
			return 16;
		case Elysium::ShaderDataType::Mat3:
			return 36;
		case Elysium::ShaderDataType::Mat4:
			return 64;
		case Elysium::ShaderDataType::Bool:
			return 1;
		default:
			break;
		}

		ELY_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	struct BufferElement {
		std::string name;
		ShaderDataType type;
		u32 size;
		u32 offset;
		bool normalized;


		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

		u32 GetComponentCount() const {
			switch (type)
			{
			case Elysium::ShaderDataType::Int:
				return 1;
			case Elysium::ShaderDataType::Int2:
				return 2;
			case Elysium::ShaderDataType::Int3:
				return 3;
			case Elysium::ShaderDataType::Int4:
				return 4;
			case Elysium::ShaderDataType::Float:
				return 1;
			case Elysium::ShaderDataType::Float2:
				return 2;
			case Elysium::ShaderDataType::Float3:
				return 3;
			case Elysium::ShaderDataType::Float4:
				return 4;
			case Elysium::ShaderDataType::Vec2:
				return 2;
			case Elysium::ShaderDataType::Vec3:
				return 3;
			case Elysium::ShaderDataType::Vec4:
				return 4;
			case Elysium::ShaderDataType::Mat3:
				return 9;
			case Elysium::ShaderDataType::Mat4:
				return 16;
			case Elysium::ShaderDataType::Bool:
				return 1;
			default:
				break;
			}

			ELY_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		inline u32 GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride() {
			u32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
		}

		std::vector<BufferElement> m_Elements;
		u32 m_Stride;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, u32 size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual u32 GetCount() const = 0;

		static IndexBuffer* Create(u32* vertices, u32 size);
	};
}