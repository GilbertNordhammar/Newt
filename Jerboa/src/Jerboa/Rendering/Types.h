#pragma once

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Enum.h"

namespace Jerboa
{
	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	enum class VertexAttributeType : uint32
	{
		NONE = 0,
		START_ITERATOR = 1,
		Position = 1,
		Position2D = 2,
		Normal = 4,
		TextureCoordinates = 8,
		Tangent = 16,
		Bitangent = 32,
		END_ITERATOR
	};
	JERBOA_ENABLE_ENUM_FLAG_OPERATORS(VertexAttributeType);

	class VertexAttribute 
	{
		friend class VertexLayout;
	public:
		VertexAttribute(VertexAttributeType attributeType, bool normalized = false)
			: m_AttributeType(attributeType), m_Normalized(normalized)
		{
		}

		VertexAttributeType m_AttributeType;
		bool m_Normalized = false;

		uint32 GetOffset() const { return m_Offset; }

		uint32 GetComponentCount() const
		{
			switch (GetDataType())
			{
				case ShaderDataType::Float:    return 1;
				case ShaderDataType::Float2:   return 2;
				case ShaderDataType::Float3:   return 3;
				case ShaderDataType::Float4:   return 4;
				case ShaderDataType::Mat3:     return 9;
				case ShaderDataType::Mat4:     return 16;
				case ShaderDataType::Int:      return 1;
				case ShaderDataType::Int2:     return 2;
				case ShaderDataType::Int3:     return 3;
				case ShaderDataType::Int4:     return 4;
				case ShaderDataType::Bool:     return 1;
			}

			JERBOA_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

		uint32 GetSize() const
		{
			switch (GetDataType())
			{
				case ShaderDataType::Float:    return 4;
				case ShaderDataType::Float2:   return 8;
				case ShaderDataType::Float3:   return 12;
				case ShaderDataType::Float4:   return 16;
				case ShaderDataType::Mat3:     return 36;
				case ShaderDataType::Mat4:     return 64;
				case ShaderDataType::Int:      return 4;
				case ShaderDataType::Int2:     return 8;
				case ShaderDataType::Int3:     return 12;
				case ShaderDataType::Int4:     return 16;
				case ShaderDataType::Bool:     return 1;
			}

			JERBOA_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

		ShaderDataType GetDataType() const
		{
			switch (m_AttributeType)
			{
				case VertexAttributeType::Position:				return ShaderDataType::Float3;
				case VertexAttributeType::Position2D:			return ShaderDataType::Float2;
				case VertexAttributeType::Normal:				return ShaderDataType::Float3;
				case VertexAttributeType::TextureCoordinates:	return ShaderDataType::Float2;
				case VertexAttributeType::Tangent:				return ShaderDataType::Float3;
				case VertexAttributeType::Bitangent:			return ShaderDataType::Float3;
				default:
					JERBOA_ASSERT(false, "Unknown vertex attribute type");
			}

			return ShaderDataType::Float; // What to return here?
		}

	private:
		uint32 m_Offset = 0;
	};

	class VertexLayout {
	public:
		VertexLayout() = default;
		VertexLayout(std::initializer_list<VertexAttribute> attributes)
			: m_Attributes(attributes)
		{
			if (!HasDuplicateOfSameAttribute())
			{
				CalcOffsetAndStride();
			}
		}

		std::vector<VertexAttribute>::iterator begin() { return m_Attributes.begin(); }
		std::vector<VertexAttribute>::iterator end() { return m_Attributes.end(); }

		int GetStride() const { return m_Stride; }
	private:
		bool HasDuplicateOfSameAttribute()
		{
			bool duplicateAttribute = false;
			VertexAttributeType accumulatedAttributeTypes = VertexAttributeType::NONE;

			for (const auto attribute : m_Attributes)
			{
				duplicateAttribute = static_cast<bool>(accumulatedAttributeTypes & attribute.m_AttributeType);
				accumulatedAttributeTypes = accumulatedAttributeTypes | attribute.m_AttributeType;
				JERBOA_ASSERT(!duplicateAttribute, "Duplicate of same vertex attribute found");
				if (duplicateAttribute)
					break;
			}

			return duplicateAttribute;
		}

		void CalcOffsetAndStride() 
		{
			int offset = 0;
			m_Stride = 0;
			for (auto& elem : m_Attributes) {
				elem.m_Offset = offset;
				offset += elem.GetSize();
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