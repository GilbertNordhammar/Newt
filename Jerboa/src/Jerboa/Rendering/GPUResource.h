#pragma once

#include "Jerboa/Core/Types.h"
#include <vector>
#include <functional>

namespace Jerboa
{
	using GenerateResourceFunc = std::function<void(uint64 *)>;
	using DeleteResourceFunc = std::function<void(uint64 *)>;

	class GPUResource
	{
	public:
		GPUResource() = default;
		GPUResource(const GPUResource& other) = delete;
		GPUResource(GPUResource&& other);
		~GPUResource();

		void Create(GenerateResourceFunc genObjFunc, DeleteResourceFunc delObjFunc);
		uint64 Get() const { return m_ID; }

		GPUResource&operator=(GPUResource& other) = delete;
		GPUResource&operator=(GPUResource&& other) noexcept;
		operator uint64();

	protected:
		void CleanUp();
		void Move(GPUResource& other);

		uint64 m_ID = 0;
		DeleteResourceFunc fm_DeleteObject;
	};
} // namespace Jerboa
