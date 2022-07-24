#pragma once

#include "Jerboa/Rendering/VertexBuffer.h"
#include "Objects/GL_Buffer.h"
#include "Jerboa/Platform/OpenGL/OpenGL.h"

namespace Jerboa
{
	class GL_VertexBuffer : public VertexBuffer
	{
	public:
		GL_VertexBuffer(float *data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout);

		virtual void Bind() override;
		virtual void UnBind() override;
		virtual const VertexBufferUsage &GetUsage() const override { return mUsage; };
		virtual const VertexBufferLayout &GetLayout() const override { return mLayout; };
		virtual uint32_t GetSize() const override { return mSize; }

	private:
		GL_Buffer mBuffer;
		VertexBufferUsage mUsage;
		VertexBufferLayout mLayout;
		uint32_t mSize = 0;
	};
} // namespace Jerboa
