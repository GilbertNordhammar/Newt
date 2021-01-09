#pragma once

#include "Jerboa/Rendering/VertexBuffer.h"
#include "OpenGL_Buffer.h"
#include "glad/glad.h"

namespace Jerboa {
	class OpenGL_VertexBuffer : public VertexBuffer
	{
	public:
		OpenGL_VertexBuffer(void* data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout);
	private:
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void SetLayout() override;

		OpenGL_Buffer mBuffer;
	};
}
 



