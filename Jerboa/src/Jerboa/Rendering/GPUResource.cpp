#include "jerboa-pch.h"
#include "GPUResource.h"

namespace Jerboa
{
	void GPUResource::Create(GenerateResourceFunc genObjFunc, DeleteResourceFunc delObjFunc)
	{
		JERBOA_ASSERT(!m_ResourceReference, "GPU resource has already been created");
		JERBOA_ASSERT(genObjFunc, "Generate callback can't be null");
		JERBOA_ASSERT(delObjFunc, "Delete callback can't be null");

		genObjFunc(&m_ResourceReference);
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

	void GPUResource::Move(GPUResource& other)
	{
		CleanUp();
		m_ResourceReference = std::move(other.m_ResourceReference);
		fm_DeleteObject = std::move(other.fm_DeleteObject);

		other.m_ResourceReference = 0;
		other.fm_DeleteObject = nullptr;
	}

	void GPUResource::CleanUp()
	{
		if (fm_DeleteObject && m_ResourceReference)
			fm_DeleteObject(&m_ResourceReference);			
	}

	GPUResource& GPUResource::operator=(GPUResource&&other) noexcept
	{
		Move(other);
		return *this;
	}
} // namespace Jerboa