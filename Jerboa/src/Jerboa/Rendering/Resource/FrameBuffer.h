#pragma once

#include "Jerboa/Core/Enum.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include "Jerboa/Rendering/Resource/Texture.h"

#include <array>

namespace Jerboa
{
	enum class ColorAttachmentSlot
	{
		S0 = 0, S1, S2, S3, S4, S5, S6, S7, Count
	};

	class ColorAttachment
	{
		ColorAttachment(ColorAttachmentSlot slot, Texture2D& texture)
			: m_Slot(slot), m_Texture(texture)
		{
		}

	public:
		ColorAttachmentSlot GetSlot() const { return m_Slot; }
		Texture2D& GetTexture() const { return m_Texture; }

	private:
		ColorAttachmentSlot m_Slot = ColorAttachmentSlot::S0;
		Texture2D& m_Texture;
	};

	class FrameBuffer
	{
	public:
		FrameBuffer(
			std::vector<ColorAttachment>* colorAttachments,
			Texture2D* depthAttachment,
			Texture2D* stencilAttachment
		);

		const GPUResource& GetGPUResouce() const { return m_GPUResource; }
		const Texture2D* GetColorAttachment(ColorAttachmentSlot slot);
		const Texture2D* GetDepthAttachment() { return m_DepthAttachment; }
		const Texture2D* GetStencilAttachment() { return m_StencilAttachment; }

	private:
		GPUResource m_GPUResource;

		std::array<Texture2D*, EnumToInt<int>(ColorAttachmentSlot::Count)> m_ColorAttachments = {};
		Texture2D*			   m_DepthAttachment = nullptr;
		Texture2D*			   m_StencilAttachment = nullptr;
	};
}