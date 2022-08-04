#include "jerboa-pch.h"
#include "Texture.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"

namespace Jerboa 
{
	void Texture2D::Create(TextureType type, const TextureData& data, GPUResourceAllocator& allocator)
	{
		m_TextureResource = allocator.CreateTexture(data);
		m_Width = data.GetWidth();
		m_Height = data.GetHeight();
		m_Type = type;
		m_PixelFormat = data.GetPixelFormat();
	}
}

