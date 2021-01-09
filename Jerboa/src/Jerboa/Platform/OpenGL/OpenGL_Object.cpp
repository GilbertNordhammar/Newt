#include "jerboa-pch.h"
#include "OpenGL_Object.h"

namespace Jerboa {
	OpenGL_Object::OpenGL_Object
	(
		GenerateObjectFunc genObjFunc,
		DeleteObjectFunc delObjFunc
	) : DeleteObjects(delObjFunc) 
	{
		genObjFunc(&mObject);
	}

	OpenGL_Object::OpenGL_Object(OpenGL_Object&& other)
	{
		Move(other);
	}

	OpenGL_Object::~OpenGL_Object()
	{
		CleanUp();
	}

	void OpenGL_Object::Move(OpenGL_Object& other)
	{
		CleanUp();
		mObject = std::move(other.mObject);
		DeleteObjects = std::move(other.DeleteObjects);

		other.mObject = 0;
		other.DeleteObjects = nullptr;
	}

	void OpenGL_Object::CleanUp()
	{
		if(DeleteObject)
			DeleteObjects(&mObject);
	}

	OpenGL_Object& OpenGL_Object::operator=(OpenGL_Object&& other) noexcept
	{
		Move(other);
		return *this;
	}
}