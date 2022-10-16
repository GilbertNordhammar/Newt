#pragma once

#include "Jerboa/Debug.h"

namespace Jerboa
{
	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	class VertexAttribute {
	public:
		VertexAttribute(ShaderDataType type, bool normalized = false)
			: Type(type), Normalized(normalized), Size(GetSize(type)), ComponentCount(GetComponentCount(type))
		{}

		ShaderDataType Type;
		int Size;
		int ComponentCount;
		bool Normalized;
		int Offset;
	private:
		int GetSize(ShaderDataType data) {
			switch (data)
			{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
			}

			JERBOA_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

		int GetComponentCount(ShaderDataType data) {
			switch (data)
			{
			case ShaderDataType::Float:    return 1;
			case ShaderDataType::Float2:   return 2;
			case ShaderDataType::Float3:   return 3;
			case ShaderDataType::Float4:   return 4;
			case ShaderDataType::Mat3:     return 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
			}

			JERBOA_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class VertexLayout {
	public:
		VertexLayout() = default;
		VertexLayout(std::initializer_list<VertexAttribute> attributes)
			: m_Attributes(attributes)
		{
			CalcOffsetAndStride();
		}

		std::vector<VertexAttribute>::iterator begin() { return m_Attributes.begin(); }
		std::vector<VertexAttribute>::iterator end() { return m_Attributes.end(); }

		int GetStride() const { return m_Stride; }
	private:
		void CalcOffsetAndStride() 
		{
			int offset = 0;
			m_Stride = 0;
			for (auto& elem : m_Attributes) {
				elem.Offset = offset;
				offset += elem.Size;
			}
			m_Stride = offset;
		}

		std::vector<VertexAttribute> m_Attributes;
		int m_Stride = 0;
	};

	enum class VertexBufferUsage
	{
		Static = 1, Dynamic = 2
	};

	enum class PixelFormat
	{
		None, Red, RGB, RGBA, Depth, Depth_Stencil
	};
}