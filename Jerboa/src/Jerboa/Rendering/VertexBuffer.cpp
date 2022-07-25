#include "jerboa-pch.h"
#include "VertexBuffer.h"

#include "Jerboa/Platform/OpenGL/GL_VertexBuffer.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Debug.h"

namespace Jerboa {
	std::shared_ptr<VertexBuffer> Jerboa::VertexBuffer::Create(
		float* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout)
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;

		switch (Platform::GetRenderApi()) {
			case RenderAPI::OpenGL:
				vertexBuffer = std::make_shared<GL_VertexBuffer>(data, size, usage, layout);
		}

		JERBOA_ASSERT(vertexBuffer, "Implementation is missing or render API is not set");
		return vertexBuffer;
	}

	VertexBuffer::VertexBuffer(uint32 size, VertexBufferUsage usage, VertexBufferLayout layout)
		: m_Usage(usage), m_Layout(layout), m_Size(size)
	{
	}
}