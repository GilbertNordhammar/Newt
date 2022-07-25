#include "jerboa-pch.h"
#include "GL_VertexBuffer.h"
#include "Jerboa/Debug.h"
#include "GL_Types.h"

namespace Jerboa
{
	GL_VertexBuffer::GL_VertexBuffer(float *data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout)
		: VertexBuffer(size, usage, layout)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, GetOpenGLUsage(usage));

		int index = 0;
		for (auto &elem : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				elem.ComponentCount,
				GetOpenGLBaseType(elem.Type),
				elem.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(void *)elem.Offset);
			index++;
		}
	}
	void GL_VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
	}
	void GL_VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
} // namespace Jerboa
