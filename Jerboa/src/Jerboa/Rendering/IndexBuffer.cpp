#include "jerboa-pch.h"
#include "IndexBuffer.h"

#include "Jerboa/Platform/OpenGL/OpenGL_IndexBuffer.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Debug.h"

namespace Jerboa {
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t size)
	{
		std::shared_ptr<IndexBuffer> indexBuffer;

		switch (Platform::GetRenderApi()) {
			case RenderAPI::OpenGL:
				indexBuffer = std::make_shared<OpenGL_IndexBuffer>(data, size);
		}

		JERBOA_ASSERT(indexBuffer, "Implementation is missing for 'IndexBuffer' or render API is not set");
		return std::make_shared<OpenGL_IndexBuffer>(data, size);
	}
}