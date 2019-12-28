#pragma once

namespace Engine
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Mat3,
		Mat4,
		Bool
	};

	static unsigned int ShaderDataTypeSize(const ShaderDataType& type)
	{
		switch (type)
		{
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Float:		return sizeof(float);
			case ShaderDataType::Float2:	return sizeof(float) * 2;
			case ShaderDataType::Float3:	return sizeof(float) * 3;
			case ShaderDataType::Float4:	return sizeof(float) * 4;
			case ShaderDataType::Int:		return sizeof(int);
			case ShaderDataType::Int2:		return sizeof(int) * 2;
			case ShaderDataType::Int3:		return sizeof(int) * 3;
			case ShaderDataType::Int4:		return sizeof(int) * 4;
			case ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
			case ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
			case ShaderDataType::Bool:		return sizeof(bool);
			default:						ENGINE_ASSERT(false, "Unknow shader data type");
		}

		return 0;
	}

	static unsigned int ShaderDataTypeToGLType(const ShaderDataType& type)
	{
		switch (type)
		{
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Bool:		return GL_BOOL;
			default:						ENGINE_ASSERT(false, "Unknow shader data type");
		}

		return 0;
	}

	struct BufferElement
	{
		std::string	   name;
		ShaderDataType type;
		unsigned int   offset;
		unsigned int   size;
		bool		   normalized;

		BufferElement(
			const ShaderDataType& type = ShaderDataType::None,
			const std::string& name = "",
			bool normalized = false
		)
			: name(name)
			, type(type)
			, offset(0)
			, size(ShaderDataTypeSize(type))
			, normalized(normalized)
		{
		}

		inline unsigned int GetElementCount() const
		{
			switch (type)
			{
				case ShaderDataType::None:		return 0;
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Mat3:		return 3 * 3;
				case ShaderDataType::Mat4:		return 4 * 4;
				case ShaderDataType::Bool:		return 1;
				default:						ENGINE_ASSERT(false, "Unknow shader data type");
			}

			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		~BufferLayout();

		const std::vector<BufferElement>& GetElements() const;
		unsigned int GetStride() const;

		std::vector<BufferElement>::iterator begin();
		std::vector<BufferElement>::iterator end();
		std::vector<BufferElement>::const_iterator begin() const;
		std::vector<BufferElement>::const_iterator end() const;
	private:
		void CalculateOffSetsAndStride();
	private:
		unsigned int				mStride;
		std::vector<BufferElement>	mElements;
	};
}
