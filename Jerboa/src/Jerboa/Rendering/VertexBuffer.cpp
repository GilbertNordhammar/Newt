#include "jerboa-pch.h"
#include "VertexBuffer.h"

#include "Jerboa/Platform/OpenGL/OpenGL_VertexBuffer.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Debug.h"

namespace Jerboa {
	std::shared_ptr<VertexBuffer> Jerboa::VertexBuffer::Create(
		float* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout)
	{
		std::shared_ptr<VertexBuffer> vertexBuffer;

		switch (Platform::GetRenderApi()) {
			case RenderAPI::OpenGL:
				vertexBuffer = std::make_shared<OpenGL_VertexBuffer>(data, size, usage, layout);
		}

		JERBOA_ASSERT(vertexBuffer, "Implementation is missing for 'VertexBuffer' or render API is not set");
		return vertexBuffer;
	}
}