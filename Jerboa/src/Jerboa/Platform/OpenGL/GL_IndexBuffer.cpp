#include "jerboa-pch.h"
#include "GL_IndexBuffer.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h"

namespace Jerboa
{
	Jerboa::GL_IndexBuffer::GL_IndexBuffer(uint32_t *data, uint32_t size)
		: mSize(size), mCount(mSize / sizeof(uint32_t))
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // Might make usage a variable in the future
	}

	void GL_IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
	}

	void Jerboa::GL_IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
} // namespace Jerboa
