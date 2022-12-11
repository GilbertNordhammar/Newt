#pragma once

#include "Jerboa/Rendering/Types.h"

namespace Jerboa
{
    struct VertexBufferData
    {
        VertexBufferData(VertexLayout layout)
            : m_Layout(layout)
        {
        }

        uint32 GetDataByteSize() const
        {
            return m_Data.size() * sizeof(float);
        }

        std::vector<float> m_Data;
        VertexBufferUsage m_Usage = VertexBufferUsage::Static;
        VertexLayout m_Layout;
    };
}