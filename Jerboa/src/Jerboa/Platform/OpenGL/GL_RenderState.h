#pragma once

#include "Jerboa/Rendering/RenderState.h";

#include "glad/glad.h"

namespace Jerboa
{
    GLbitfield GetBufferClearBitsGL(BufferClearBits clearBits);
    GLenum     GetCompareFunctionGL(CompareFunction compareFunction);
    GLenum     GetStencilOperationGL(StencilOperation operation);

	class GL_RenderState : public RenderState
	{
        // Buffer clearing
        void        SetClearColorImpl(const glm::vec4& clearColor) override;
        void        SetClearDepthImpl(float clearDepth) override;
        void        SetClearStencilImpl(float clearStencil) override;
        void        SetClearBitsImpl(BufferClearBits clearBits) override;

        // Stencil testing
        void        SetStencilCompareFunctionImpl(CompareFunction compareFunction, int compareValue) override;
        void        SetStencilTestingEnabledImpl(bool enabled) override;
        void        SetStencilOperationsImpl(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass) override;
        void        SetStencilReadMaskImpl(int readMask) override;
        void        SetStencilWriteMaskImpl(int writeMask) override;

        // Depth testing
        void        SetDepthTestingEnabledImpl(bool enabled) override;
        void        SetDepthWritingEnabledImpl(bool enabled) override;
        void        SetDepthCompareFunctionImpl(CompareFunction compareFunction) override;

        // Face culling
        void        SetFaceCullingModeImpl(FaceCullingMode mode) override;
        void        SetFrontFaceWindingImpl(FrontFaceWinding winding) override;

        // Color blending
        void        SetBlendingEnabledImpl(bool enabled) override;
        void        SetBlendingColorImpl(glm::vec4 color) override;
        void        SetBlendingFactorImpl(BlendingFactor factor) override;
	};
}