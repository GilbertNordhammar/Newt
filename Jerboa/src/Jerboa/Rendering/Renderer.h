#pragma once

#include "Jerboa/Rendering/RenderState.h"

#include <memory>

namespace Jerboa {
	class Mesh;
	class RenderState;

	class Renderer
	{
	public:
		static Renderer* Create();

		virtual void Clear() = 0;
		virtual void Draw(Mesh& mesh) = 0;

		RenderState* GetState() { return m_RenderState.get(); }
	protected:
		std::shared_ptr<RenderState> m_RenderState;
	};
}


