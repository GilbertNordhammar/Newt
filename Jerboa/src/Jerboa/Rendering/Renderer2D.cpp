#include "jerboa-pch.h"
#include "Renderer2D.h"

#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Renderer.h"
#include "Jerboa/Resource/Loaders/ShaderLoaderGLSL.h"

namespace Jerboa
{
	Renderer2D::Renderer2D(Renderer& renderer)
		: m_Renderer(renderer)
	{
		CreateFullscreenQuad();
		CreateFullscreenShader();
	}

	void Renderer2D::DrawFullscreenPostEffect(const FrameBuffer& source, FrameBuffer* destination)
	{
		RenderState& renderState = m_Renderer.GetState();
		ShaderState& shaderState = m_Renderer.GetShaderState();

		renderState.BindShader(m_PassthroughShader);

		const auto& colorAttachments = source.GetColorAttachments();

		for (int i = 0; i < colorAttachments.size(); i++)
		{
			if (colorAttachments[i].Assigned())
			{
				shaderState.SetInt("JB_uColorTexture" + std::to_string(i), i);
				renderState.BindTexture(*colorAttachments[i].GetTexture(), static_cast<TextureSlot>(i));
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
		//float vertices[] = {
		//	 1.0f,  1.0f, 0.0f,  // 0 top right
		//	 1.0f, -1.0f, 0.0f,  // 1 bottom right
		//	-1.0f, -1.0f, 0.0f,  // 2 bottom left
		//	-1.0f,  1.0f, 0.0f   // 3 top left 
		//};
		//VertexBufferData vertexData(vertices, sizeof(vertices), VertexBufferUsage::Static, { Jerboa::ShaderDataType::Float3 });

		//unsigned int indices[] = {
		//	0, 3, 1,  // first triangle
		//	1, 3, 2   // second triangle
		//};
		//auto indexData = Jerboa::IndexBufferData(indices, sizeof(indices));

		//m_FullscreenQuad.Create(vertexData, &indexData, PrimitiveType::Triangle, m_Renderer.GetAllocatorPtr());

		float quadVertices[] = {
			// positions   // texCoords
			-1.0f, -1.0f,	0.0f, 0.0f,
			 1.0f, 1.0f,	1.0f, 1.0f,
			-1.0f, 1.0f,	0.0f, 1.0f,

			-1.0f, -1.0f,	0.0f, 0.0f,
			 1.0f, -1.0f,	1.0f, 0.0f,
			 1.0f, 1.0f,	1.0f, 1.0f
		};
		VertexBufferData vertexData(quadVertices, sizeof(quadVertices), VertexBufferUsage::Static, { Jerboa::ShaderDataType::Float2, Jerboa::ShaderDataType::Float2 });

		m_FullscreenQuad.Create(vertexData, nullptr, PrimitiveType::Triangle, m_Renderer.GetAllocatorPtr());
	}

	void Renderer2D::CreateFullscreenShader()
	{
		ShaderDataGLSL data = ShaderLoaderGLSL::Load("assets/shaders/PostProcessing/default.vert", "assets/shaders/PostProcessing/Passthrough.frag");
		m_PassthroughShader.Create(data, m_Renderer.GetAllocator());
	}
}