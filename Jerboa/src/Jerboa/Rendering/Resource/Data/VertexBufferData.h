#pragma once

#include "Jerboa/Rendering/Types.h"

namespace Jerboa
{
    struct VertexBufferData
    {
        uint32 GetDataByteSize() const
        {
            return m_Data.size() * sizeof(float);
        }

        std::vector<float> m_Data;
        VertexBufferUsage m_Usage = VertexBufferUsage::Static;
        VertexLayout m_Layout;
    };
}