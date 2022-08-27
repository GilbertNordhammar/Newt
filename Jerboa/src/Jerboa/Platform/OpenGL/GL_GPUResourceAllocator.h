#pragma once

#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa
{
	class GL_RenderState;

	class GL_GPUResourceAllocator : public GPUResourceAllocator
	{
	public:
		GL_GPUResourceAllocator(GL_RenderState* renderState);

		GPUResource	CreateVertexBuffer(const VertexBufferData& bufferData) const override;
		GPUResource CreateVertexArrayObject() const override; // Needed for OpenGL
		GPUResource	CreateIndexBuffer(const IndexBufferData& bufferData) const override;
		GPUResource	CreateTexture(const TextureConfig& config) const override;
		GPUResource	CreateShader(const ShaderDataGLSL& shaderData) const override;

		void UploadTextureData(GPUResource& texture, const TextureData& textureData) const override;
	private:
		GL_RenderState* m_RenderStateGL;
	};
}
