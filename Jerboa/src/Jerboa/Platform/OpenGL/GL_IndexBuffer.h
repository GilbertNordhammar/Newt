#pragma once

#include "Jerboa/Rendering/IndexBuffer.h"

#include "Objects/GL_Buffer.h"

namespace Jerboa
{
	class GL_IndexBuffer : public IndexBuffer
	{
	public:
		GL_IndexBuffer(uint32_t *data, uint32_t size);

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		GL_Buffer m_Buffer;
	};
} // namespace Jerboa
