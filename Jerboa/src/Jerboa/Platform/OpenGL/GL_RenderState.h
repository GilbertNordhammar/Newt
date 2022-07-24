#pragma once

#include "Jerboa/Rendering/RenderState.h";

#include "glad/glad.h"

namespace Jerboa
{
    GLbitfield ConvertBufferClearBitsToGL(BufferClearBits clearBits);
    GLenum     ConvertCompareFunctionToGL(CompareFunction compareFunction);
    GLenum     ConvertStencilOperationToGL(StencilOperation operation);
    GLenum     ConvertFaceCullingModeToGL(FaceCullingMode mode);
    GLenum     ConvertFrontFaceWindingToGL(FrontFaceWinding winding);
    GLenum     ConvertBlendingFactorToGL(BlendingFactor factor);

	class GL_RenderState : public RenderState
	{
        // Buffer clearing
        void        SetClearColorImpl(const glm::vec4& clearColor) override;
        void        SetClearDepthImpl(float clearDepth) override;
        void        SetClearStencilImpl(float clearStencil) override;
        void        SetClearBitsImpl(BufferClearBits clearBits) override;

        // Stencil testing
        void        SetStencilParametersImpl(CompareFunction compareFunction, int compareValue, int readMask, int writeMask) override;
        void        SetStencilTestingEnabledImpl(bool enabled) override;
        void        SetStencilOperationsImpl(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass) override;

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
        void        SetBlendingFactorImpl(BlendingFactor source, BlendingFactor destination) override;
	};
}