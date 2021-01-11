#pragma once

#include "Jerboa/Rendering/VertexBuffer.h"
#include "OpenGL_Buffer.h"
#include "glad/glad.h"

namespace Jerboa {
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	public:
		OpenGL_VertexBuffer(float* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout);

		virtual void Bind() override;
		virtual void UnBind() override;
		virtual const VertexBufferUsage& GetUsage() const override { return mUsage; };
		virtual const VertexBufferLayout& GetLayout() const override { return mLayout; };
		virtual uint32_t GetSize() const override { return mSize; }

	private:
		OpenGL_Buffer mBuffer;
		VertexBufferUsage mUsage;
		VertexBufferLayout mLayout;
		uint32_t mSize = 0;
	};
}
 



