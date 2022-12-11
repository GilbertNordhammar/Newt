#pragma once

#include "Jerboa/Core/Types.h"
#include <vector>

namespace Jerboa
{
    struct IndexBufferData
    {
        uint32 GetDataByteSize() const
        {
            return m_Data.size() * sizeof(uint32);
        }

        std::vector<uint32> m_Data;
    };
}