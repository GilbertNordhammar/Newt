#include "jerboa-pch.h"
#include "VertexBuffer.h"
#include "Jerboa/Platform/OpenGL/OpenGL_VertexBuffer.h"

namespace Jerboa {
	std::shared_ptr<VertexBuffer> Jerboa::VertexBuffer::Create(
		void* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout)
	{
		return std::make_shared<OpenGL_VertexBuffer>(data, size, usage, layout);
	}
}