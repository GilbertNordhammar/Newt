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

			VertexBufferLayout layout = bufferData.m_Layout;
			int index = 0;
			for (auto& elem : layout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(
					index,
					elem.ComponentCount,
					GetOpenGLBaseType(elem.Type),
					elem.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(void*)elem.Offset);
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
			m_RenderStateGL->m_BoundMeshStateDirty = true;
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
			glGenTextures(1, &glObject);
			*textureObject = glObject;
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

	void GL_GPUResourceAllocator::UploadTextureData(GPUResource& texture, const TextureData& textureData) const
	{
		auto textureGPUResource = texture.Get();
		JERBOA_ASSERT(textureGPUResource, "Can't upload data since no gpu resource has been created for the texture");
		if (!textureGPUResource)
		{
			return;
		}

		glBindTexture(GL_TEXTURE_2D, textureGPUResource);
		GLenum pixelFormat = GetPixelFormatGL(textureData.GetPixelFormat());
		glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, textureData.GetWidth(), textureData.GetHeight(), 0, pixelFormat, GL_UNSIGNED_BYTE, textureData.GetData());

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, pixelFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, pixelFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Rebinding last bound texture in order to not corrupt the bound texture state
		TextureSlot lastBoundSlot = m_RenderStateGL->GetLastBoundTextureSlot();
		Texture2D* lastBoundTexture = m_RenderStateGL->GetBoundTexture(lastBoundSlot);
		if(lastBoundTexture)
			m_RenderStateGL->BindTexture(*lastBoundTexture, lastBoundSlot);
	}
}