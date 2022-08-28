#pragma once

#include "Jerboa/Rendering/Resource/Texture.h"

#include <memory>

namespace Jerboa
{
	class Texture2D;

	enum class ColorAttachmentSlot
	{
		S0 = 0, S1, S2, S3, S4, S5, S6, S7, Count
	};

	enum class RenderPassBeginAction
	{
		Clear, Keep
	};

	class FrameBufferAttachment
	{
	public:
		void Set(std::shared_ptr<Texture2D> texture, RenderPassBeginAction action)
		{
			m_Texture = texture;
			m_RenderPassBeginAction = action;
		}

		const Texture2D*		GetTexture() const { return m_Texture.get(); }
		RenderPassBeginAction	GetRenderPassBeginAction() const { return m_RenderPassBeginAction; }
		bool					Empty() const { return m_Texture == nullptr; }

	private:
		std::shared_ptr<Texture2D> m_Texture = nullptr;
		RenderPassBeginAction m_RenderPassBeginAction = RenderPassBeginAction::Clear;
	};

	struct FrameBufferConfig
	{
		std::array<FrameBufferAttachment, EnumToInt<int>(ColorAttachmentSlot::Count)> m_ColorAttachments;
		FrameBufferAttachment m_DepthAttachment;
		FrameBufferAttachment m_StencilAttachment;

	};
}