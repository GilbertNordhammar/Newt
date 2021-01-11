#pragma once

#include "Jerboa/Rendering/IndexBuffer.h"

#include "OpenGL_Buffer.h"

namespace Jerboa {
	class OpenGL_IndexBuffer : public IndexBuffer
	{
	public:
		OpenGL_IndexBuffer(uint32_t* data, uint32_t size);

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual uint32_t GetSize() const override { return mSize; };
		virtual uint32_t GetCount() const override { return mCount; };
	private:
		OpenGL_Buffer mBuffer;
		uint32_t mSize;
		uint32_t mCount;
	};
}


