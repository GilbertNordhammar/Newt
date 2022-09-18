#pragma once

#include "Jerboa/Core/Enum.h"
#include "Jerboa/Rendering/Resource/Config/FrameBufferConfig.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResource.h"
#include "Jerboa/Rendering/Resource/Internal/GPUResourceAllocator.h"
#include "Jerboa/Rendering/Resource/Texture.h"

#include <array>
#include <memory>

namespace Jerboa
{
	using FrameBufferAttachmentArray = std::array<FrameBufferAttachment, EnumToInt<int>(ColorAttachmentSlot::Count)>;

	class FrameBuffer
	{
	public:
		void								Create(const FrameBufferConfig& config, const GPUResourceAllocator& allocator);

		const GPUResource&					GetGPUResouce() const { return m_GPUResource; }
		const FrameBufferAttachment&		GetColorAttachment(ColorAttachmentSlot slot) const;
		const FrameBufferAttachmentArray&	GetColorAttachments() const { return m_Config.m_ColorAttachments; }
		const FrameBufferAttachment&		GetDepthStencilAttachment() const { return m_Config.m_DepthStencilAttachment; }
		const bool							UseStencil() const { return m_Config.m_UseStencil; }
		const FrameBufferConfig&			GetConfig() const { return m_Config; }

	private:
		GPUResource m_GPUResource;

		// TODO: Don't store textures as raw pointers
		FrameBufferConfig m_Config;
	};
}