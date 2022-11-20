#include "jerboa-pch.h"
#include "Renderer2D.h"

#include "Jerboa/Core/Enum.h"
#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Renderer.h"
#include "Jerboa/Resource/Loaders/ShaderLoaderGLSL.h"

namespace Jerboa
{
	Renderer2D::Renderer2D(Renderer& renderer)
		: m_Renderer(renderer)
	{
		CreateFullscreenQuad();
	}

	void Renderer2D::DrawFullscreenPostEffect(Shader& shader, const FrameBuffer& source, FrameBuffer* destination)
	{
		RenderState& renderState = m_Renderer.GetState();
		ShaderState& shaderState = m_Renderer.GetShaderState();

		renderState.BindShader(shader);

		const auto& colorAttachments = source.GetColorAttachments();

		for (int i = 0; i < colorAttachments.size(); i++)
		{
			if (colorAttachments[i].Assigned())
			{
				shaderState.SetInt("JB_uColorTexture" + std::to_string(i), i);
				Texture2D* texture = colorAttachments[i].GetTexture();
				if(EnumHasFlags(texture->GetUsage(), TextureUsage::Read))
					renderState.BindTexture(*colorAttachments[i].GetTexture(), static_cast<TextureSlot>(i));
			}
		}

		auto depthStencilAttachment = source.GetDepthStencilAttachment();
		if (depthStencilAttachment.Assigned())
		{
			Texture2D* texture = depthStencilAttachment.GetTexture();
			if (texture->IsDepthTexture() && texture->IsReadable())
			{
				shaderState.SetInt("JB_uDepthTexture", EnumToInt(TextureSlot::_7));
				renderState.BindTexture(*depthStencilAttachment.GetTexture(), TextureSlot::_7);
			}
		}

		if (destination)
		{
			renderState.BeginRenderPass(*destination);
		}
		else
		{
			renderState.BeginDefaultRenderPass();
		}

		bool prevDepthTestEnabled = renderState.GetDepthTestingEnabled();
		renderState.SetDepthTestingEnabled(false);
		m_Renderer.Draw(m_FullscreenQuad);
		renderState.SetDepthTestingEnabled(prevDepthTestEnabled);
	}

	void Renderer2D::CreateFullscreenQuad()
	{
		float quadVertices[] = {
			// positions   // texCoords
			-1.0f, -1.0f,	0.0f, 0.0f,
			 1.0f, 1.0f,	1.0f, 1.0f,
			-1.0f, 1.0f,	0.0f, 1.0f,

			-1.0f, -1.0f,	0.0f, 0.0f,
			 1.0f, -1.0f,	1.0f, 0.0f,
			 1.0f, 1.0f,	1.0f, 1.0f
		};

		VertexBufferData vertexData(quadVertices, sizeof(quadVertices), VertexBufferUsage::Static,
			{
				VertexAttribute(VertexAttributeType::Position2D),
				VertexAttribute(VertexAttributeType::TextureCoordinates1)
			}
		);

		m_FullscreenQuad.Create(vertexData, nullptr, PrimitiveType::Triangle, m_Renderer.GetAllocator());
	}
}