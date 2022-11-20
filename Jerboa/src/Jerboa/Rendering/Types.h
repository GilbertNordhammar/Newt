#pragma once

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Enum.h"
#include "Jerboa/Core/Bit.h"

namespace Jerboa
{
	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	enum class VertexAttributeType : uint32
	{
		NONE					= 0,
		Position				= BITMASK_1,
		Position2D				= BITMASK_2,
		TextureCoordinates1		= BITMASK_3,
		TextureCoordinates2		= BITMASK_4,
		TextureCoordinates3		= BITMASK_5,
		TextureCoordinates4		= BITMASK_6,
		Normal					= BITMASK_7,
		Tangent					= BITMASK_8,	
		Color1					= BITMASK_9,
		Color2					= BITMASK_10,
		Color3					= BITMASK_11,
		Color4					= BITMASK_12,
	};
	JERBOA_ENABLE_ENUM_FLAG_OPERATORS(VertexAttributeType);

	constexpr uint32 JERBOA_VERTEX_ATTRIBUTE_MAX_TEXTURE_COORDINATES = 4;
	constexpr uint32 JERBOA_VERTEX_ATTRIBUTE_MAX_COLORS = 4;

	static uint32 GetVertexAttributeLayoutIndex(VertexAttributeType attributeType)
	{
		switch (attributeType)
		{
			case VertexAttributeType::Position:				return 0;
			case VertexAttributeType::Position2D:			return 0;
			case VertexAttributeType::TextureCoordinates1:	return 1;
			case VertexAttributeType::TextureCoordinates2:	return 2;
			case VertexAttributeType::TextureCoordinates3:	return 3;
			case VertexAttributeType::TextureCoordinates4:	return 4;
			case VertexAttributeType::Normal:				return 5;
			case VertexAttributeType::Tangent:				return 6;
			case VertexAttributeType::Color1:				return 7;
			case VertexAttributeType::Color2:				return 8;
			case VertexAttributeType::Color3:				return 9;
			case VertexAttributeType::Color4:				return 10;
			default:
				JERBOA_ASSERT(false, "Unhandled vertex attribute");
				return 0;
		}
	}

	class VertexAttribute 
	{
		friend class VertexLayout;
	public:
		VertexAttribute(VertexAttributeType attributeType, bool normalized = false)
			: m_AttributeType(attributeType), 
			m_LayoutIndex(GetVertexAttributeLayoutIndex(attributeType)), 
			m_Normalized(normalized)
		{
		}

		uint32	GetLayoutIndex() const	{ return m_LayoutIndex; }
		uint32	GetOffset() const		{ return m_Offset; }
		bool	Normalized() const		{ return m_Normalized; }

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
				case VertexAttributeType::TextureCoordinates1:	return ShaderDataType::Float2;
				case VertexAttributeType::TextureCoordinates2:	return ShaderDataType::Float2;
				case VertexAttributeType::TextureCoordinates3:	return ShaderDataType::Float2;
				case VertexAttributeType::TextureCoordinates4:	return ShaderDataType::Float2;
				case VertexAttributeType::Normal:				return ShaderDataType::Float3;
				case VertexAttributeType::Tangent:				return ShaderDataType::Float3;
				case VertexAttributeType::Color1:				return ShaderDataType::Float4;
				case VertexAttributeType::Color2:				return ShaderDataType::Float4;
				case VertexAttributeType::Color3:				return ShaderDataType::Float4;
				case VertexAttributeType::Color4:				return ShaderDataType::Float4;
				default:
					JERBOA_ASSERT(false, "Unhandled vertex attribute");
			}

			return ShaderDataType::Float; // What to return here?
		}

	private:
		uint32 m_Offset = 0;
		VertexAttributeType m_AttributeType;
		uint32 m_LayoutIndex = 0;
		bool m_Normalized = false;
	};

	class VertexLayout {
	public:
		VertexLayout() = default;
		VertexLayout(std::initializer_list<VertexAttribute> attributes)
			: m_Attributes(attributes)
		{
			if (AreAttributesValid())
			{
				CalculateAttributeOffsetsAndStride();
			}
			else
			{
				m_Attributes.clear();
			}
		}

		VertexLayout(const std::vector<VertexAttribute>& attributes)
			: m_Attributes(attributes)
		{
			if (AreAttributesValid())
			{
				CalculateAttributeOffsetsAndStride();
			}
			else
			{
				m_Attributes.clear();
			}
		}

		std::vector<VertexAttribute>::iterator begin() { return m_Attributes.begin(); }
		std::vector<VertexAttribute>::iterator end() { return m_Attributes.end(); }

		int GetStride() const { return m_Stride; }
	private:
		bool AreAttributesValid()
		{
			bool validAttributes = true;
			VertexAttributeType accumulatedAttributeTypes = VertexAttributeType::NONE;

			for (const auto attribute : m_Attributes)
			{
				validAttributes = !EnumHasFlags(accumulatedAttributeTypes, attribute.m_AttributeType);
				JERBOA_ASSERT(validAttributes, "Duplicate of same vertex attribute found");
				if (!validAttributes)
					break;
				accumulatedAttributeTypes = accumulatedAttributeTypes | attribute.m_AttributeType;
			}

			validAttributes = !EnumHasFlags(accumulatedAttributeTypes, VertexAttributeType::Position | VertexAttributeType::Position2D);
			JERBOA_ASSERT(validAttributes, "VertexAttributeType::Position and VertexAttributeType::Position2D can't both exist in the same vertex layout!");

			return validAttributes;
		}

		void CalculateAttributeOffsetsAndStride() 
		{
			int offset = 0;
			m_Stride = 0;
			for (auto& elem : m_Attributes) 
			{
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