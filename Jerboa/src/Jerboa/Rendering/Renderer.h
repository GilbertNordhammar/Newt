#pragma once

#include "VertexBuffer.h"

namespace Jerboa {
	class Renderer
	{
		public:
			static void BeginPass();
			static void EndPass();
			static void Clear();
			static void Submit(std::shared_ptr<VertexBuffer> vertexBuffer);
			static void Draw(int nVertices); //temporary
	};
}


