#include "jerboa-pch.h"
#include "GPUResource.h"

namespace Jerboa
{
	void GPUResource::Create(GenerateResourceFunc genObjFunc, DeleteResourceFunc delObjFunc)
	{
		JERBOA_ASSERT(!m_ID, "GPU resource has already been created");
		JERBOA_ASSERT(genObjFunc, "Generate callback can't be null");
		JERBOA_ASSERT(delObjFunc, "Delete callback can't be null");

		if (m_ID)
		{
			JERBOA_ASSERT(false, "Resource has already been created")
			return;
		}

		genObjFunc(&m_ID);
		fm_DeleteObject = delObjFunc;
	}

	GPUResource::GPUResource(GPUResource&& other)
	{
		Move(other);
	}

	GPUResource::~GPUResource()
	{
		CleanUp();
	}

	GPUResource::operator uint64()
	{ 
		return m_ID; 
	}

	void GPUResource::Move(GPUResource& other)
	{
		CleanUp();
		m_ID = std::move(other.m_ID);
		fm_DeleteObject = std::move(other.fm_DeleteObject);

		other.m_ID = 0;
		other.fm_DeleteObject = nullptr;
	}

	void GPUResource::CleanUp()
	{
		if (fm_DeleteObject && m_ID)
			fm_DeleteObject(&m_ID);			
	}

	GPUResource& GPUResource::operator=(GPUResource&&other) noexcept
	{
		Move(other);
		return *this;
	}
} // namespace Jerboa