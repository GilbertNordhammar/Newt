#pragma once

#include "Jerboa/Rendering/GPUResourceAllocator.h"

namespace Jerboa
{
	class GL_RenderState;

	class GL_GPUResourceAllocator : public GPUResourceAllocator
	{
	public:
		GL_GPUResourceAllocator(GL_RenderState* renderState);

		GPUResource	CreateVertexBuffer(const VertexBufferData& bufferData) override;
		GPUResource CreateVertexArrayObject() override; // Needed for OpenGL
		GPUResource	CreateIndexBuffer(const IndexBufferData& bufferData) override;
		GPUResource	CreateTexture(const TextureData& textureData) override;
	private:
		GL_RenderState* m_RenderStateGL;
	};
}
