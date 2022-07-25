#pragma once

#include "Jerboa/Rendering/Renderer.h"

namespace Jerboa {
	class Mesh;
	class GL_RenderState;

	class GL_Renderer : public Renderer
	{
	public:
		GL_Renderer(GL_RenderState* renderStateGL);

		void Clear() override;
		void Draw(Mesh& mesh) override;
	private:
		GL_RenderState* m_RenderStateGL;
	};
}