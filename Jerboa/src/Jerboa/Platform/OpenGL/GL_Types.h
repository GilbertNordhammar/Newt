#pragma once

#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include "Jerboa/Rendering/Types.h"

namespace Jerboa
{
	static GLenum GetOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}
		JERBOA_ASSERT(false, "Unknown ShaderDataType!");
		return GL_INVALID_ENUM;
	}

	static GLenum GetOpenGLUsage(VertexBufferUsage usage)
	{
		switch (usage)
		{
			case VertexBufferUsage::Dynamic:	return GL_DYNAMIC_DRAW;
			case VertexBufferUsage::Static:		return GL_STATIC_DRAW;
		}

		JERBOA_ASSERT(false, "Unknown usage!");
		return GL_INVALID_ENUM;
	}

	static GLenum GetPixelFormatGL(PixelFormat pixelFormat)
	{
		switch (pixelFormat)
		{
			case PixelFormat::Red:		return GL_RED;
			case PixelFormat::RGB:		return GL_RGB;
			case PixelFormat::RGBA:		return GL_RGBA;
		}

		JERBOA_ASSERT(false, "Unhandled PixelFormat entry");
		return GL_INVALID_ENUM;
	}
}