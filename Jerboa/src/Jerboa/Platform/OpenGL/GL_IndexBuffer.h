#pragma once

#include "Jerboa/Rendering/IndexBuffer.h"

#include "Objects/GL_Buffer.h"

namespace Jerboa
{
	class GL_IndexBuffer : public IndexBuffer
	{
	public:
		GL_IndexBuffer(uint32_t *data, uint32_t size);

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual uint32_t GetSize() const override { return mSize; };
		virtual uint32_t GetCount() const override { return mCount; };

	private:
		GL_Buffer mBuffer;
		uint32_t mSize;
		uint32_t mCount;
	};
} // namespace Jerboa
