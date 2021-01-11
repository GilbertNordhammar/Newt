#include "jerboa-pch.h"
#include "IndexBuffer.h"

#include "Jerboa/Platform/OpenGL/OpenGL_IndexBuffer.h"

namespace Jerboa {
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		return std::make_shared<OpenGL_IndexBuffer>(data, size);
	}
}