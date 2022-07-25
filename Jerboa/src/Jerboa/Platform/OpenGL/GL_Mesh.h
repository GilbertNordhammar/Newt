#pragma once

#include "Jerboa/Platform/OpenGL/Objects/GL_VertexArrayObject.h";
#include "Jerboa/Rendering/Mesh.h"

namespace Jerboa
{
	class GL_Mesh : public Mesh
	{
	public:
		//GL_Mesh(const VertexBufferData& vertexBufferData, const IndexBufferData& indexBufferData);
		//void Bind() override;
	private:
		GL_VertexArrayObject m_VAO;
	};
}