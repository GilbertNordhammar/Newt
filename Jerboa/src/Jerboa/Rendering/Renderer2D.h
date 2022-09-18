#pragma once

#include "Jerboa/Rendering/Renderer.h"
#include "Jerboa/Rendering/Resource/FrameBuffer.h"

namespace Jerboa
{
	class Renderer2D
	{
	public:
		Renderer2D(Renderer& renderer);

		void					DrawFullscreenPostEffect(const FrameBuffer& source, FrameBuffer* destination = nullptr);

	private:
		void					CreateFullscreenQuad();
		void					CreateFullscreenShader();

		Renderer&				m_Renderer;
		Mesh					m_FullscreenQuad;
		Shader					m_PassthroughShader;
	};
}