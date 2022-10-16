#include "jerboa-pch.h"
#include "GL_GPUResourceAllocator.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/OpenGL/GL_RenderState.h"
#include "Jerboa/Platform/OpenGL/GL_ShaderUtils.h"
#include "Jerboa/Platform/OpenGL/GL_Types.h"
#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include "Jerboa/Rendering/Resource/Texture.h";

namespace Jerboa
{
	static GLenum GetTextureSamplingFilterGL(TextureSamplingFilter samplingFilter, MipmapInterpolationFilter mipmapInterpolationFilter)
	{
		switch (samplingFilter)
		{
			case TextureSamplingFilter::Linear:
				if (mipmapInterpolationFilter == MipmapInterpolationFilter::Linear)
					return GL_LINEAR_MIPMAP_LINEAR;
				else if (mipmapInterpolationFilter == MipmapInterpolationFilter::Nearest)
					return GL_LINEAR_MIPMAP_NEAREST;
				else
					return GL_LINEAR;
				break;
			case TextureSamplingFilter::Nearest:
				if (mipmapInterpolationFilter == MipmapInterpolationFilter::Linear)
					return GL_NEAREST_MIPMAP_LINEAR;
				else if (mipmapInterpolationFilter == MipmapInterpolationFilter::Nearest)
					return GL_NEAREST_MIPMAP_NEAREST;
				else
					return GL_NEAREST;
				break;
		}

		JERBOA_ASSERT(false, "Invalid enum argument in GetGLTextureSamplingFilter()");
		return GL_INVALID_ENUM;
	}

	static GLenum GetTextureWrappingModeGL(TextureSamplingWrapMode mode)
	{
		switch (mode)
		{
			case TextureSamplingWrapMode::Repeat:		return GL_REPEAT;
			case TextureSamplingWrapMode::MirrorRepeat: return GL_MIRRORED_REPEAT;
			case TextureSamplingWrapMode::ClampToEdge:	return GL_CLAMP_TO_EDGE;
		}

		JERBOA_ASSERT(false, "Invalid enum argument in GetGLTextureWrappingMode()");
		return GL_INVALID_ENUM;
	}

	GL_GPUResourceAllocator::GL_GPUResourceAllocator(GL_RenderState* renderState)
		: m_RenderStateGL(renderState)
	{
		JERBOA_ASSERT(renderState, "Render state is null");
	}

	GPUResource GL_GPUResourceAllocator::CreateVertexBuffer(const VertexBufferData& bufferData) const
	{
		auto generateVertexBuffer = [&](uintptr* vertexBufferObject)
		{
			GLuint glObject = 0;
			glGenBuffers(1, &glObject);
			*vertexBufferObject = glObject;

			glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, bufferData.m_Size, bufferData.m_Data, GetOpenGLUsage(bufferData.m_Usage));

			VertexLayout layout = bufferData.m_Layout;
			int index = 0;
			for (auto& elem : layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(
					index,
					elem.GetComponentCount(),
					GetOpenGLBaseType(elem.GetDataType()),
					elem.m_Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(void*)elem.m_Offset);
				index++;
			}
		};

		auto deleteVertexBuffer = [](uintptr* vertexBufferObject) {
			GLuint glObject = *vertexBufferObject;
			glDeleteBuffers(1, &glObject);
		};

		GPUResource vertexBuffer;
		vertexBuffer.Create(generateVertexBuffer, deleteVertexBuffer);
		return vertexBuffer;
	}

	GPUResource GL_GPUResourceAllocator::CreateIndexBuffer(const IndexBufferData& bufferData) const
	{
		auto generateIndexBuffer = [&](uintptr* indexBufferObject)
		{
			GLuint glObject = 0;
			glGenBuffers(1, &glObject);
			*indexBufferObject = glObject;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferData.m_Size, bufferData.m_Data, GL_STATIC_DRAW); // Might make usage a variable in the future
			
		};

		auto deleteIndexBuffer = [](uintptr* indexBufferObject) {
			GLuint glObject = *indexBufferObject;
			glDeleteBuffers(1, &glObject);
		};

		GPUResource indexBuffer;
		indexBuffer.Create(generateIndexBuffer, deleteIndexBuffer);
		return indexBuffer;
	}

	GPUResource GL_GPUResourceAllocator::CreateVertexArrayObject() const
	{
		auto generateVAO = [&](uintptr* vao)
		{
			GLuint glObject = 0;
			glGenVertexArrays(1, &glObject);
			*vao = glObject;
			glBindVertexArray(*vao);
			m_RenderStateGL->m_BoundVAO = glObject;
		};

		auto deleteVAO = [](uintptr* vao) {
			GLuint glObject = *vao;
			glDeleteVertexArrays(1, &glObject);
		};

		GPUResource VAO;
		VAO.Create(generateVAO, deleteVAO);
		return VAO;
	}

	GPUResource	GL_GPUResourceAllocator::CreateTexture([[maybe_unused]] const TextureConfig& config) const
	{
		auto generateTexture = [&](uintptr* textureObject)
		{
			GLuint glObject = 0;

			if (EnumHasFlags(config.m_Usage, TextureUsage::Read))
			{
				glGenTextures(1, &glObject);
				glBindTexture(GL_TEXTURE_2D, glObject);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetTextureWrappingModeGL(config.m_SamplerWrappingMode));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetTextureWrappingModeGL(config.m_SamplerWrappingMode));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetTextureSamplingFilterGL(config.m_SamplingFilter, config.m_MipMapInterpolationFilter));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetTextureSamplingFilterGL(config.m_SamplingFilter, config.m_MipMapInterpolationFilter));
			}
			else if(EnumHasFlags(config.m_Usage, TextureUsage::Write))
			{
				glGenRenderbuffers(1, &glObject);
				glBindRenderbuffer(GL_RENDERBUFFER, glObject);		
			}
			*textureObject = glObject;

			// Rebinding last bound texture in order to not corrupt the bound texture state
			m_RenderStateGL->RebindLastBoundTexture();
		};

		auto deleteTexture = [](uintptr* vao) {
			GLuint glObject = *vao;
			glDeleteTextures(1, &glObject);
			
		};

		GPUResource texture;
		texture.Create(generateTexture, deleteTexture);
		return texture;
	}

	GPUResource GL_GPUResourceAllocator::CreateShader(const ShaderDataGLSL& shaderData) const
	{
		auto generateShader = [&](uintptr* shaderObject)
		{
			using namespace ShaderUtils;

			const std::string& vertexCode = shaderData.GetVertexSource().GetCode();
			const std::string& fragmentCode = shaderData.GetFragmentSource().GetCode();
			unsigned int vertexId = CompileShader(shaderData.GetVertexName(), vertexCode, GL_VERTEX_SHADER);
			unsigned int fragmentId = CompileShader(shaderData.GetFragmentName(), fragmentCode, GL_FRAGMENT_SHADER);

			if (vertexId && fragmentId)
				*shaderObject = CreateAndLinkProgram(vertexId, fragmentId);

			if(vertexId)
				glDeleteShader(vertexId);
			if (fragmentId)
				glDeleteShader(fragmentId);
		};

		auto deleteShader = [](uintptr* shaderObject) {
			GLuint glObject = *shaderObject;
			glDeleteProgram(glObject);
		};

		GPUResource shader;
		shader.Create(generateShader, deleteShader);
		return shader;
	}

	GPUResource GL_GPUResourceAllocator::CreateFrameBuffer(const FrameBufferGPUResourceConfig& config) const
	{
		auto generateFbo = [&](uintptr* fbo)
		{
			GLuint glObject = 0;
			glGenFramebuffers(1, &glObject);
			*fbo = glObject;
			glBindFramebuffer(GL_FRAMEBUFFER, *fbo);

			for (int i = 0; i < config.m_ColorAttachments.size(); i++)
			{
				const GPUResource* colorAttachment = config.m_ColorAttachments[i];
				const TextureConfig& colorAttachmentConfig = config.m_ColorAttachmentsTextureConfig[i];
				AssignFrameBufferAttachment(GL_COLOR_ATTACHMENT0 + i, colorAttachment, colorAttachmentConfig);
			}
			
			if (config.m_DepthStencilAttachment)
			{
				GLenum attachment = config.m_DepthStencilAttachmentTextureConfig.m_PixelFormat == PixelFormat::Depth_Stencil
					? GL_DEPTH_STENCIL_ATTACHMENT
					: GL_DEPTH_ATTACHMENT;
				AssignFrameBufferAttachment(attachment, config.m_DepthStencilAttachment, config.m_DepthStencilAttachmentTextureConfig);
			}
			
			CheckFrambufferStatus();
			glBindFramebuffer(GL_FRAMEBUFFER, 0); // TODO: Do proper state restoration
		};

		auto deleteFbo = [](uintptr* fbo) 
		{
			GLuint glObject = *fbo;
			glDeleteFramebuffers(1, &glObject);
		};

		GPUResource fbo;
		fbo.Create(generateFbo, deleteFbo);
		return fbo;
	}

	void GL_GPUResourceAllocator::AssignFrameBufferAttachment(GLenum attachment, const GPUResource* textureResource, TextureConfig textureConfig) const
	{
		if (!textureResource)
			return;
		if (!textureResource->Get())
			return;

		GLenum pixelFormat = GetPixelFormatGL(textureConfig.m_PixelFormat);

		if (EnumHasFlags(textureConfig.m_Usage, TextureUsage::Read))
		{
			glBindTexture(GL_TEXTURE_2D, textureResource->Get());
			glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, textureConfig.m_Width, textureConfig.m_Height, 0, pixelFormat, GL_UNSIGNED_BYTE, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureResource->Get(), 0);
		}
		else if(EnumHasFlags(textureConfig.m_Usage, TextureUsage::Write))
		{
			glBindRenderbuffer(GL_RENDERBUFFER, textureResource->Get());
			glRenderbufferStorage(GL_RENDERBUFFER, pixelFormat, textureConfig.m_Width, textureConfig.m_Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, textureResource->Get());
		}
	}

	void GL_GPUResourceAllocator::CheckFrambufferStatus() const {
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			JERBOA_LOG_ERROR("Framebuffer is not complete!");

			switch (status)
			{
			case GL_FRAMEBUFFER_UNSUPPORTED:
				JERBOA_LOG_ERROR(" - GL_FRAMEBUFFER_UNSUPPORTED");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				JERBOA_LOG_ERROR(" - GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
				break;
			default:
				JERBOA_LOG_ERROR(" - UNKNOWN_GL_ERROR");
			}
		}

	}

	void GL_GPUResourceAllocator::UploadTextureData(GPUResource& texture, const GPUTextureResourceData& data) const
	{
		auto textureGPUResource = texture.Get();
		if (!textureGPUResource)
		{
			return;
		}

		glBindTexture(GL_TEXTURE_2D, textureGPUResource);
		GLenum pixelFormatGL = GetPixelFormatGL(data.m_PixelFormat);
		glTexImage2D(GL_TEXTURE_2D, 0, pixelFormatGL, data.m_Width, data.m_Height, 0, pixelFormatGL, GL_UNSIGNED_BYTE, data.m_PixelData);

		if (data.m_GenerateMipmaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		// Rebinding last bound texture in order to not corrupt the bound texture state
		m_RenderStateGL->RebindLastBoundTexture();
	}
}