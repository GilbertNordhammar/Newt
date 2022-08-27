#pragma once

#include "Jerboa/Core/Types.h"
#include <vector>
#include <functional>

namespace Jerboa
{
	using GenerateResourceFunc = std::function<void(uintptr* resource)>;
	using DeleteResourceFunc = std::function<void(uintptr* resource)>;

	class GPUResource
	{
	public:
		GPUResource() = default;
		GPUResource(const GPUResource& other) = delete;
		GPUResource(GPUResource&& other);
		~GPUResource();

		uintptr Get() const { return m_ResourceReference; }

		GPUResource&operator=(GPUResource& other) = delete;
		GPUResource&operator=(GPUResource&& other) noexcept;

	protected:
		void Create(GenerateResourceFunc genObjFunc, DeleteResourceFunc delObjFunc);
		void CleanUp();
		void Move(GPUResource& other);

		uintptr m_ResourceReference = 0;
		DeleteResourceFunc fm_DeleteObject;
		
		friend class GPUResourceAllocator;
		friend class GL_GPUResourceAllocator;
	};
} // namespace Jerboa
