#pragma once

#include "Jerboa/Core/Enum.h"
#include "Jerboa/Core/Singleton.h"
#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Resource/Shader.h"
#include "Jerboa/Rendering/Resource/Texture.h"

#include "glm/glm.hpp"
#include <memory>
#include <array>

namespace Jerboa
{
    enum class BufferClearBits
    {
        None = 0,
        Color = 1, 
        Depth = 2, 
        Stencil = 4
    };

    template<>
    struct Jerboa::enum_operator_enabler<BufferClearBits> {
        static constexpr bool enableBitWiseOperators = true;
    };
    

    enum class CompareFunction
    {
        Never, 
        Less, 
        Equal, 
        LessOrEqual, 
        Greater, 
        NotEqual, 
        GreaterOrEqual, 
        Always
    };

    enum class StencilOperation
    {
        Keep, 
        Zero, 
        Replace, 
        Increment, 
        IncrementWrap, 
        Decrement, 
        DecrementWrap, 
        Invert
    };

    enum class FaceCullingMode
    {
        None, 
        Back, 
        Front
    };

    enum class FrontFaceWinding
    {
        Clockwise, 
        CounterClockwise
    };

    enum class BlendingFactor
    {
        Zero, 
        One, 
        SourceColor, 
        OneMinusSourceColor, 
        DestinationColor, 
        OneMinusDestinationColor, 
        SourceAlpha, 
        OneMinusSourceAlpha,
        DestinationAlpha,
        OneMinusDestinationAlpha,
        BlendColor,
        OneMinusBlendColor,
        BlendAlpha,
        OneMinusBlendAlpha
    };

    enum class TextureSlot
    {
        S0 = 0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15, Count
    };

    class RenderState : Singleton<RenderState>
    {
    public:
        void                ResetStateToDefaultValues();

        // Resource binding interface
        void				BindTexture(Texture2D& texture, TextureSlot slot);
        void				BindShader(Shader& shader);
        void				BindMesh(Mesh& mesh);

        Texture2D*          GetBoundTexture(TextureSlot slot) { return m_BoundTextures[EnumToInt<int>(slot)]; }
        Shader*             GetBoundShader() { return m_BoundShader; }
        Mesh*               GetBoundMesh() { return m_BoundMesh; }

        // Buffer clearing interface
        void                SetClearColor(const glm::vec4& clearColor);
        void                SetClearDepth(float clearDepth);
        void                SetClearStencil(float clearStencil);
        void                SetClearBits(BufferClearBits clearBits);

        glm::vec4           GetClearColor() const { return m_ClearColor; }
        BufferClearBits     GetClearBits() const { return m_ClearBits; }

        // Stencil testing interface
        void                SetStencilParameters(CompareFunction compareFunction, int compareValue, int readMask, int writeMask);
        void                SetStencilTestingEnabled(bool enabled);
        void                SetStencilOperations(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass);

        bool                GetStencilTestingEnabled() const     { return m_StencilTestingEnabled; }
        int                 GetStencilReadMask() const           { return m_StencilReadMask; }
        int                 GetStencilWriteMask() const          { return m_StencilWriteMask; }
        StencilOperation    GetStencilFailOperation() const      { return m_StencilFailOperation; }
        StencilOperation    GetStencilDepthFailOperation() const { return m_StencilDepthFailOperation; }
        StencilOperation    GetStencilPassOperation() const      { return m_StencilPassOperation; }
        CompareFunction     GetStencilCompareFunction() const    { return m_StencilCompareFunction; }

        // Depth testing interface
        void                SetDepthTestingEnabled(bool enabled);
        void                SetDepthWritingEnabled(bool enabled);
        void                SetDepthCompareFunction(CompareFunction compareFunction);

        bool                GetDepthTestingEnabled() const    { return m_DepthTestingEnabled; }
        bool                GetDepthWritingEnabled() const    { return m_DepthWritingEnabled; }
        CompareFunction     GetDepthCompareFunction() const   { return m_DepthCompareFunction; }

        // Face culling interface
        void                SetFaceCullingMode(FaceCullingMode mode);
        void                SetFrontFaceWinding(FrontFaceWinding winding);

        FaceCullingMode     GetFaceCullingMode() const   { return m_FaceCullingMode; }
        FrontFaceWinding    GetFrontFaceWinding() const  { return m_FrontFaceWinding; }

        // Color blending interface
        void                SetBlendingEnabled(bool enabled);
        void                SetBlendingColor(glm::vec4 color);
        void                SetBlendingFactor(BlendingFactor source, BlendingFactor destination);

        bool                GetBlendingEnabled() const   { return m_BlendingEnabled; }
        glm::vec4           GetBlendingColor() const     { return m_BlendingColor; }
        BlendingFactor      GetBlendingFactorSource() const    { return m_BlendingFactorSource; }
        BlendingFactor      GetBlendingFactorDestination() const { return m_BlendingFactorDestination; }

    protected:
        // Resource binding virtual interface
        virtual void	    BindTextureImpl(Texture2D& texture, TextureSlot slot) = 0;
        virtual void	    BindShaderImpl(Shader& shader) = 0;
        virtual void	    BindMeshImpl(Mesh& mesh) = 0;

        // Buffer clearing virtual interface
        virtual void        SetClearColorImpl(const glm::vec4& clearColor) = 0;
        virtual void        SetClearDepthImpl(float clearDepth) = 0;
        virtual void        SetClearStencilImpl(float clearStencil) = 0;
        virtual void        SetClearBitsImpl(BufferClearBits clearBits) = 0;

        // Stencil testing virtual interface
        virtual void        SetStencilParametersImpl(CompareFunction compareFunction, int compareValue, int readMask, int writeMask) = 0;
        virtual void        SetStencilTestingEnabledImpl(bool enabled) = 0;
        virtual void        SetStencilOperationsImpl(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass) = 0;

        // Depth testing virtual interface
        virtual void        SetDepthTestingEnabledImpl(bool enabled) = 0;
        virtual void        SetDepthWritingEnabledImpl(bool enabled) = 0;
        virtual void        SetDepthCompareFunctionImpl(CompareFunction compareFunction) = 0;

        // Face culling virtual interface
        virtual void        SetFaceCullingModeImpl(FaceCullingMode mode) = 0;
        virtual void        SetFrontFaceWindingImpl(FrontFaceWinding winding) = 0;

        // Color blending virtual interface
        virtual void        SetBlendingEnabledImpl(bool enabled) = 0;
        virtual void        SetBlendingColorImpl(glm::vec4 color) = 0;
        virtual void        SetBlendingFactorImpl(BlendingFactor source, BlendingFactor destination) = 0;

        // Resource binding variables
        // TODO: This can lead to dangling pointer if the resource is deallocated. Find a better solution
        std::array<Texture2D*, EnumToInt<int>(TextureSlot::Count)> m_BoundTextures; // TODO: Replace magic number for array size
        Shader*                     m_BoundShader = nullptr;
        Mesh*                       m_BoundMesh = nullptr;

        // Buffer clearing variables
        glm::vec4                   m_ClearColor;
        float                       m_ClearDepth;
        float                       m_ClearStencil;
        BufferClearBits             m_ClearBits;

        // Stencil testing variables
        bool                        m_StencilTestingEnabled;
        int                         m_StencilReadMask;
        int                         m_StencilWriteMask;
        StencilOperation            m_StencilFailOperation;
        StencilOperation            m_StencilDepthFailOperation;
        StencilOperation            m_StencilPassOperation;
        CompareFunction             m_StencilCompareFunction;
        int                         m_StencilCompareValue;

        // Depth testing variables
        bool                        m_DepthTestingEnabled;
        bool                        m_DepthWritingEnabled;
        CompareFunction             m_DepthCompareFunction;

        // Face culling variables
        FaceCullingMode             m_FaceCullingMode;
        FrontFaceWinding            m_FrontFaceWinding;

        // Color blending variables
        bool                        m_BlendingEnabled;
        glm::vec4                   m_BlendingColor;
        BlendingFactor              m_BlendingFactorSource;
        BlendingFactor              m_BlendingFactorDestination;
    };
}