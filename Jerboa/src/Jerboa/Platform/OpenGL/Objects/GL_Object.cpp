#include "jerboa-pch.h"
#include "GL_Object.h"

namespace Jerboa
{
	GL_Object::GL_Object(
		GenerateObjectFunc genObjFunc,
		DeleteObjectFunc delObjFunc) : DeleteObjects(delObjFunc)
	{
		genObjFunc(&mObject);
	}

	GL_Object::GL_Object(GL_Object &&other)
	{
		Move(other);
	}

	GL_Object::~GL_Object()
	{
		CleanUp();
	}

	void GL_Object::Move(GL_Object &other)
	{
		CleanUp();
		mObject = std::move(other.mObject);
		DeleteObjects = std::move(other.DeleteObjects);

		other.mObject = 0;
		other.DeleteObjects = nullptr;
	}

	void GL_Object::CleanUp()
	{
		if (DeleteObject)
			DeleteObjects(&mObject);
	}

	GL_Object &GL_Object::operator=(GL_Object &&other) noexcept
	{
		Move(other);
		return *this;
	}
} // namespace Jerboa