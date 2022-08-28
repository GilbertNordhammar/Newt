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
	class FrameBuffer
	{
	public:
		void Create(const FrameBufferConfig& config, const GPUResourceAllocator& allocator);

		const GPUResource& GetGPUResouce() const { return m_GPUResource; }
		const Texture2D* GetColorAttachment(ColorAttachmentSlot slot);
		const Texture2D* GetDepthAttachment() { return m_DepthAttachment.get(); }
		const Texture2D* GetStencilAttachment() { return m_StencilAttachment.get(); }

	private:
		GPUResource m_GPUResource;

		// TODO: Don't store textures as raw pointers
		std::array<std::shared_ptr<Texture2D>, EnumToInt<int>(ColorAttachmentSlot::Count)> m_ColorAttachments = { nullptr };
		std::shared_ptr<Texture2D> m_DepthAttachment = nullptr;
		std::shared_ptr<Texture2D> m_StencilAttachment = nullptr;
	};
}