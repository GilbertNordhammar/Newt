#pragma once

#include <memory>

namespace Jerboa {
	class IndexBuffer
	{
	public:
		static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t size);

		virtual void	Bind() = 0;
		virtual void	Unbind() = 0;

		uint32_t		GetSize() const { return m_Size; };
		uint32_t		GetCount() const { return m_Size / sizeof(uint32_t); };

		virtual ~IndexBuffer() {};
	protected:
		IndexBuffer(uint32_t size);

		uint32_t m_Size;
	};
}


