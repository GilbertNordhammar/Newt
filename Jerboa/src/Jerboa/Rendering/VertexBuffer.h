#pragma once

#include "Jerboa/Debug.h"

#include <vector>
#include <memory>
#include <initializer_list>

namespace Jerboa {
	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};



	class VertexBufferElement {
	public:
		VertexBufferElement(ShaderDataType type, bool normalized = false)
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

	class VertexBufferLayout {
	public:
		VertexBufferLayout(std::initializer_list<VertexBufferElement> elements)
			: mElements(elements) 
		{
			CalcOffsetAndStride();
		}

		std::vector<VertexBufferElement>::iterator begin() { return mElements.begin(); }
		std::vector<VertexBufferElement>::iterator end() { return mElements.end(); }

		int GetStride() const { return mStride; }
	private:
		void CalcOffsetAndStride() {
			int offset = 0;
			mStride = 0;
			for (auto& elem : mElements) {
				elem.Offset = offset;
				offset += elem.Size;
			}
			mStride = offset;
		}

		std::vector<VertexBufferElement> mElements;
		int mStride = 0;
	};

	enum class VertexBufferUsage
	{
		Static = 1, Dynamic = 2
	};

	class VertexBuffer
	{
	public:
		static std::shared_ptr<VertexBuffer> Create(void* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout);
		
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void SetLayout() = 0;
		
		virtual ~VertexBuffer() = 0 {}
	};
}


