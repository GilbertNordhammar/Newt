#include "jerboa-pch.h"
#include "GL_RenderState.h"

#include "glad/glad.h"

namespace Jerboa
{
    GLbitfield GetBufferClearBitsGL(BufferClearBits clearBits)
    {
        GLbitfield clearBitsGL = 0;
        if (EnumToInt<int>(clearBits | BufferClearBits::Color))
            clearBitsGL |= GL_COLOR_BUFFER_BIT;
        if (EnumToInt<int>(clearBits | BufferClearBits::Depth))
            clearBitsGL |= GL_DEPTH_BUFFER_BIT;
        if (EnumToInt<int>(clearBits | BufferClearBits::Stencil))
            clearBitsGL |= GL_STENCIL_BUFFER_BIT;

        return clearBitsGL;
    }

    GLenum GetCompareFunctionGL(CompareFunction compareFunction)
    {
        switch (compareFunction)
        {
            case CompareFunction::Always:           return GL_ALWAYS;
            case CompareFunction::Never:            return GL_NEVER;
            case CompareFunction::Equal:            return GL_EQUAL;
            case CompareFunction::NotEqual:         return GL_NOTEQUAL;
            case CompareFunction::Less:             return GL_LESS;
            case CompareFunction::LessOrEqual:      return GL_LEQUAL;
            case CompareFunction::Greater:          return GL_GREATER;
            case CompareFunction::GreaterOrEqual:   return GL_GEQUAL;
        }

        JERBOA_ASSERT(false, "Invalid or unhandled CompareFunction entry");
        return GL_INVALID_ENUM;
    }

    GLenum GetStencilOperationGL(StencilOperation operation)
    {
        switch (operation)
        {
            case StencilOperation::Keep:            return GL_KEEP;
            case StencilOperation::Zero:            return GL_ZERO;
            case StencilOperation::Replace:         return GL_REPLACE;
            case StencilOperation::Increment:       return GL_INCR;
            case StencilOperation::IncrementWrap:   return GL_INCR_WRAP;
            case StencilOperation::Decrement:       return GL_DECR;
            case StencilOperation::DecrementWrap:   return GL_DECR_WRAP;
            case StencilOperation::Invert:          return GL_INVERT;
        }

        JERBOA_ASSERT(false, "Invalid or unhandled StencilOperation entry");
        return GL_INVALID_ENUM;
    }

    void GL_RenderState::SetClearColorImpl(const glm::vec4& clearColor)
    {
        if (m_ClearColor == clearColor) return; // Is this floating point comparison?
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    }

    void GL_RenderState::SetClearDepthImpl(float clearDepth)
    {
        glClearDepth(clearDepth);
    }

    void GL_RenderState::SetClearStencilImpl(float clearStencil)
    {
        glClearStencil(clearStencil);
    }

    void GL_RenderState::SetClearBitsImpl(BufferClearBits clearBits)
    {
        // Clear bits are set as an argument to glClear, so this function can be empty
    }

    void GL_RenderState::SetStencilCompareFunctionImpl(CompareFunction compareFunction, int compareValue)
    {
        glStencilFunc(GetCompareFunctionGL(compareFunction), compareValue, 0xFF);
    }

    void GL_RenderState::SetStencilTestingEnabledImpl(bool enabled)
    {
        enabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
    }

    void GL_RenderState::SetStencilOperationsImpl(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass)
    {
        glStencilOp(GetStencilOperationGL(stencilFail), GetStencilOperationGL(depthFail), GetStencilOperationGL(pass));
    }

    void GL_RenderState::SetStencilReadMaskImpl(int readMask)
    {

    }

    void GL_RenderState::SetStencilWriteMaskImpl(int writeMask)
    {

    }

    void GL_RenderState::SetDepthTestingEnabledImpl(bool enabled)
    {

    }

    void GL_RenderState::SetDepthWritingEnabledImpl(bool enabled)
    {

    }

    void GL_RenderState::SetDepthCompareFunctionImpl(CompareFunction compareFunction)
    {

    }

    void GL_RenderState::SetFaceCullingModeImpl(FaceCullingMode mode)
    {

    }

    void GL_RenderState::SetFrontFaceWindingImpl(FrontFaceWinding winding)
    {

    }

    void GL_RenderState::SetBlendingEnabledImpl(bool enabled)
    {

    }

    void GL_RenderState::SetBlendingColorImpl(glm::vec4 color)
    {

    }

    void GL_RenderState::SetBlendingFactorImpl(BlendingFactor factor)
    {

    }
}