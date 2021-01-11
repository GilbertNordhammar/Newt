#pragma once

#include <memory>

namespace Jerboa {
	class IndexBuffer
	{
	public:
		static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t size);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;;
		virtual uint32_t GetSize() const = 0;
		virtual uint32_t GetCount() const = 0;
	};
}


