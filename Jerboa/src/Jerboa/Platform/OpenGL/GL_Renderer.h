#pragma once

#include "Jerboa/Rendering/Renderer.h"

namespace Jerboa {
	class Mesh;

	class GL_Renderer : public Renderer
	{
	public:
		void Clear() override;
		void Draw(Mesh& mesh) override;
	};
}