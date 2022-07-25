#include "jerboa-pch.h"
#include "IndexBuffer.h"

#include "Jerboa/Platform/OpenGL/GL_IndexBuffer.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Debug.h"

namespace Jerboa {
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		std::shared_ptr<IndexBuffer> indexBuffer;

		switch (Platform::GetRenderApi()) {
			case RenderAPI::OpenGL:
				indexBuffer = std::make_shared<GL_IndexBuffer>(data, size);
		}

		JERBOA_ASSERT(indexBuffer, "Implementation is missing or render API is not set");
		return std::make_shared<GL_IndexBuffer>(data, size);
	}

	IndexBuffer::IndexBuffer(uint32_t size)
		: m_Size(size)
	{
	}
}