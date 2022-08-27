#pragma once

#include "Jerboa/Core/Singleton.h"
#include "Jerboa/Rendering/Resource/IndexBuffer.h"
#include "Jerboa/Rendering/Resource/VertexBuffer.h"
#include "Jerboa/Rendering/Resource/Config/TextureConfig.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include "Jerboa/Resource/Data/TextureData.h"
#include "Jerboa/Resource/Data/ShaderDataGLSL.h"

namespace Jerboa
{
	class GPUResourceAllocator : Singleton<GPUResourceAllocator>
	{
	public:
		virtual GPUResource	CreateVertexBuffer(const VertexBufferData& bufferData) const = 0;
		virtual GPUResource CreateVertexArrayObject() const; // Needed for OpenGL
		virtual GPUResource	CreateIndexBuffer(const IndexBufferData& bufferData) const = 0;
		virtual GPUResource	CreateTexture(const TextureConfig& config) const = 0;
		virtual GPUResource	CreateShader(const ShaderDataGLSL& shaderData) const = 0;
		
		virtual void UploadTextureData(GPUResource& texture, const TextureData& textureData) const = 0;
	};
}
