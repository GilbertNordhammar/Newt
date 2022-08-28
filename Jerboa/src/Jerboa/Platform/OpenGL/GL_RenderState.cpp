#include "jerboa-pch.h"
#include "GL_RenderState.h"

#include "Jerboa/Core/Enum.h"
#include "Jerboa/Platform/OpenGL/OpenGL.h"
#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Resource/Shader.h"
#include "Jerboa/Rendering/Resource/Texture.h"

namespace Jerboa
{
    GLbitfield ConvertBufferClearBitsToGL(BufferClearBits clearBits)
    {
        GLbitfield clearBitsGL = 0;
        if (EnumHasFlags(clearBits, BufferClearBits::Color))
            clearBitsGL |= GL_COLOR_BUFFER_BIT;
        if (EnumHasFlags(clearBits, BufferClearBits::Depth))
            clearBitsGL |= GL_DEPTH_BUFFER_BIT;
        if (EnumHasFlags(clearBits, BufferClearBits::Stencil))
            clearBitsGL |= GL_STENCIL_BUFFER_BIT;

        return clearBitsGL;
    }

    GLenum ConvertCompareFunctionToGL(CompareFunction compareFunction)
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

    GLenum ConvertStencilOperationToGL(StencilOperation operation)
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

    GLenum ConvertFaceCullingModeToGL(FaceCullingMode mode)
    {
        switch (mode)
        {
            case FaceCullingMode::Back:     return GL_BACK;
            case FaceCullingMode::Front:    return GL_FRONT;
            case FaceCullingMode::None:     return GL_NONE;
        }

        JERBOA_ASSERT(false, "Invalid or unhandled FaceCullingMode entry");
        return GL_INVALID_ENUM;
    }

    GLenum ConvertFrontFaceWindingToGL(FrontFaceWinding winding)
    {
        switch (winding)
        {
            case FrontFaceWinding::Clockwise:           return GL_CW;
            case FrontFaceWinding::CounterClockwise:    return GL_CCW;
        }

        JERBOA_ASSERT(false, "Invalid or unhandled FrontFaceWinding entry");
        return GL_INVALID_ENUM;
    }

    GLenum ConvertBlendingFactorToGL(BlendingFactor factor)
    {
        switch (factor)
        {
            case BlendingFactor::Zero:                              return GL_ZERO;
            case BlendingFactor::One:                               return GL_ONE;
            case BlendingFactor::SourceColor:                       return GL_SRC_COLOR;
            case BlendingFactor::OneMinusSourceColor:               return GL_ONE_MINUS_SRC_COLOR;
            case BlendingFactor::DestinationColor:                  return GL_DST_COLOR;
            case BlendingFactor::OneMinusDestinationColor:          return GL_ONE_MINUS_DST_COLOR;
            case BlendingFactor::SourceAlpha:                       return GL_SRC_ALPHA;
            case BlendingFactor::OneMinusSourceAlpha:               return GL_ONE_MINUS_SRC_ALPHA;
            case BlendingFactor::DestinationAlpha:                  return GL_DST_ALPHA;
            case BlendingFactor::OneMinusDestinationAlpha:          return GL_ONE_MINUS_DST_ALPHA;
            case BlendingFactor::BlendColor:                        return GL_CONSTANT_COLOR;
            case BlendingFactor::OneMinusBlendColor:                return GL_ONE_MINUS_CONSTANT_COLOR;
            case BlendingFactor::BlendAlpha:                        return GL_CONSTANT_ALPHA;
            case BlendingFactor::OneMinusBlendAlpha:                return GL_ONE_MINUS_CONSTANT_ALPHA;
        }

        JERBOA_ASSERT(false, "Invalid or unhandled BlendingFactor entry");
        return GL_INVALID_ENUM;
    }

    void GL_RenderState::BeginRenderPassImpl(FrameBuffer& frameBuffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.GetGPUResouce().Get());

        std::vector<GLenum> activeColorAttachmentIndexes;
        auto colorAttachments = frameBuffer.GetColorAttachments();
        for (int i = 0; i < colorAttachments.size(); i++)
        {
            if (!colorAttachments[i].Empty())
                activeColorAttachmentIndexes.push_back(i);
        }

        glDrawBuffers(activeColorAttachmentIndexes.size(), activeColorAttachmentIndexes.data());
        for (const auto& index : activeColorAttachmentIndexes)
        {
            if(colorAttachments[index].GetRenderPassBeginAction() == RenderPassBeginAction::Clear)
                glClearBufferfv(GL_COLOR, GL_COLOR_ATTACHMENT0 + index, &m_ClearColor[0]);
        }

        auto depthAttachment = frameBuffer.GetDepthAttachment();
        if (!depthAttachment.Empty() && depthAttachment.GetRenderPassBeginAction() == RenderPassBeginAction::Clear)
            glClearBufferfv(GL_DEPTH, 0, &m_ClearDepth);

        auto stencilAttachment = frameBuffer.GetStencilAttachment();
        if (!stencilAttachment.Empty() && stencilAttachment.GetRenderPassBeginAction() == RenderPassBeginAction::Clear)
            glClearBufferiv(GL_STENCIL, 0, &m_ClearStencil);
    }

    void GL_RenderState::BeginDefaultRenderPassImpl()
    {
        if(m_BoundFrameBuffer)
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GL_RenderState::BindTextureImpl(Texture2D& texture, TextureSlot slot)
    {
        m_LastBoundTextureSlot = slot;
        glActiveTexture(GL_TEXTURE0 + EnumToInt<int>(slot));
        glBindTexture(GL_TEXTURE_2D, texture.GetGPUResouce().Get());
    }

    void GL_RenderState::BindShaderImpl(Shader& shader)
    {
        glUseProgram(shader.GetGPUResource().Get());
    }

    void GL_RenderState::BindMeshImpl(Mesh& mesh)
    {
        glBindVertexArray(mesh.GetVAO().Get());
    }

    void GL_RenderState::ClearBoundTextureImpl(TextureSlot slot)
    {
        glActiveTexture(GL_TEXTURE0 + EnumToInt<int>(slot));
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GL_RenderState::ClearBoundShaderImpl()
    {
        glUseProgram(0);
    }

    void GL_RenderState::ClearBoundMeshImpl()
    {
        glBindVertexArray(0);
    }

    void GL_RenderState::SetClearColorImpl(const glm::vec4& clearColor)
    {
        if (m_ClearColor != clearColor) return; // Is this floating point comparison?
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    }

    void GL_RenderState::SetClearDepthImpl(float clearDepth)
    {
        glClearDepth(clearDepth); // TODO: Add cache check
    }

    void GL_RenderState::SetClearStencilImpl(int clearStencil)
    {
        glClearStencil(clearStencil); // TODO: Add cache check
    }

    void GL_RenderState::SetClearBitsImpl(BufferClearBits clearBits)
    {
        // Clear bits are set as an argument to glClear, so this function can be empty
    }

    void GL_RenderState::SetStencilParametersImpl(CompareFunction compareFunction, int compareValue, int readMask, int writeMask)
    {
        if(m_StencilCompareFunction != compareFunction || m_StencilCompareValue != compareValue || m_StencilReadMask != readMask)
            glStencilFunc(ConvertCompareFunctionToGL(compareFunction), compareValue, readMask);

        if(m_StencilWriteMask != writeMask)
            glStencilMask(writeMask);
    }

    void GL_RenderState::SetStencilTestingEnabledImpl(bool enabled)
    {
        if(m_StencilTestingEnabled != enabled)
            enabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
    }

    void GL_RenderState::SetStencilOperationsImpl(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass)
    {
        if(m_StencilFailOperation != stencilFail || m_StencilDepthFailOperation != depthFail || m_StencilPassOperation != pass)
            glStencilOp(ConvertStencilOperationToGL(stencilFail), ConvertStencilOperationToGL(depthFail), ConvertStencilOperationToGL(pass));
    }

    void GL_RenderState::SetDepthTestingEnabledImpl(bool enabled)
    {
        if (m_DepthTestingEnabled != enabled)
            enabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }

    void GL_RenderState::SetDepthWritingEnabledImpl(bool enabled)
    {
        if(m_DepthWritingEnabled != enabled)
            glDepthMask(enabled);
    }

    void GL_RenderState::SetDepthCompareFunctionImpl(CompareFunction compareFunction)
    {
        glDepthFunc(ConvertCompareFunctionToGL(compareFunction));
    }

    void GL_RenderState::SetFaceCullingModeImpl(FaceCullingMode mode)
    {
        if (m_FaceCullingMode == mode)
            return;
        
        if (m_FaceCullingMode == FaceCullingMode::None && mode != FaceCullingMode::None)
        {
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glDisable(GL_CULL_FACE);
        }

        if (mode != FaceCullingMode::None)
            glCullFace(ConvertFaceCullingModeToGL(mode));
    }

    void GL_RenderState::SetFrontFaceWindingImpl(FrontFaceWinding winding)
    {
        if(m_FrontFaceWinding != winding)
            glFrontFace(ConvertFrontFaceWindingToGL(winding));
    }

    void GL_RenderState::SetBlendingEnabledImpl(bool enabled)
    {
        if (m_BlendingEnabled != enabled)
            enabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    }

    void GL_RenderState::SetBlendingColorImpl(glm::vec4 color)
    {
        glBlendColor(color.r, color.g, color.b, color.a); // TODO: Add cache check
    }

    void GL_RenderState::SetBlendingFactorImpl(BlendingFactor source, BlendingFactor destination)
    {
        if (m_BlendingFactorSource != source || m_BlendingFactorDestination != destination)
            glBlendFunc(ConvertBlendingFactorToGL(source), ConvertBlendingFactorToGL(destination));
    }

    void GL_RenderState::RebindCurrentMesh()
    {
        if(m_BoundMesh)
            BindMesh(*m_BoundMesh);
    }

    void GL_RenderState::RebindLastBoundTexture()
    {
        Texture2D* lastBoundTexture = GetBoundTexture(m_LastBoundTextureSlot);
        if (lastBoundTexture)
            BindTexture(*lastBoundTexture, m_LastBoundTextureSlot);
    }
}