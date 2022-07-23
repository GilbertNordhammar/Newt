#include "jerboa-pch.h"
#include "GL_Object.h"

namespace Jerboa
{
	GL_Object::GL_Object(GenerateObjectFunc genObjFunc, DeleteObjectFunc delObjFunc)
		: fm_GenerateObject(genObjFunc), fm_DeleteObject(delObjFunc)
	{
		JERBOA_ASSERT(genObjFunc, "GL Object generation function can't be null");
		JERBOA_ASSERT(delObjFunc, "GL Object deletion function can't be null");
	}

	GL_Object::GL_Object(GL_Object &&other)
	{
		Move(other);
	}

	GL_Object::~GL_Object()
	{
		CleanUp();
	}

	GL_Object::operator GLuint() 
	{ 
		if (fm_GenerateObject && !m_CreationMethodHasRun)
		{
			fm_GenerateObject(&m_ObjectGL);
			JERBOA_ASSERT(m_ObjectGL, "GL object failed to get generated");
			m_CreationMethodHasRun = true;
		}
		return m_ObjectGL; 
	}

	void GL_Object::Move(GL_Object &other)
	{
		CleanUp();
		m_ObjectGL = std::move(other.m_ObjectGL);
		fm_DeleteObject = std::move(other.fm_DeleteObject);

		other.m_ObjectGL = 0;
		other.fm_DeleteObject = nullptr;
	}

	void GL_Object::CleanUp()
	{
		if (fm_DeleteObject && m_ObjectGL)
			fm_DeleteObject(&m_ObjectGL);			
	}

	GL_Object &GL_Object::operator=(GL_Object &&other) noexcept
	{
		Move(other);
		return *this;
	}
} // namespace Jerboa