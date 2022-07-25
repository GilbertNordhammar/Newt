#pragma once

#include "Jerboa/Rendering/VertexBuffer.h"
#include "Objects/GL_Buffer.h"
#include "Jerboa/Platform/OpenGL/OpenGL.h"

namespace Jerboa
{
	class GL_VertexBuffer : public VertexBuffer
	{
	public:
		GL_VertexBuffer(float *data, uint32_t size, VertexBufferUsage usage, VertexBufferLayout layout);

		virtual void Bind() override;
		virtual void UnBind() override;

	private:
		GL_Buffer mBuffer;
	};
} // namespace Jerboa
