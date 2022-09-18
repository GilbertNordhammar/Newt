#pragma once

#include "Jerboa/Rendering/Renderer.h"

namespace Jerboa {
	class Mesh;
	class GL_RenderState;

	class GL_Renderer : public Renderer
	{
	public:
		GL_Renderer(GL_RenderState* renderStateGL);

		virtual void	BeginFrameImpl() override;
		virtual void	EndFrameImpl() override;

		void			Draw(Mesh& mesh) override;

		GL_RenderState* m_RenderStateGL;
	};
}