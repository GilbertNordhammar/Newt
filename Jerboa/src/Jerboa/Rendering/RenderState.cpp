#include "jerboa-pch.h"
#include "RenderState.h"

#include "Jerboa/Rendering/Texture.h"
#include "Jerboa/Rendering/Shader.h"
#include "Jerboa/Rendering/Mesh.h"

namespace Jerboa
{
	void RenderState::ResetStateToDefaultValues()
	{
		// Resource binding
		m_BoundTextures.fill(nullptr);
		m_BoundShader = nullptr;
		m_BoundMesh = nullptr;

		// Buffer clearing
		SetClearColor(glm::vec4(0, 0, 0, 0));
		SetClearDepth(1);
		SetClearStencil(0);
		SetClearBits(BufferClearBits::None);

		// Stencil testing
		SetStencilParameters(CompareFunction::Never, 0, 0xFF, 0);
		SetStencilTestingEnabled(false);
		SetStencilOperations(StencilOperation::Keep, StencilOperation::Keep, StencilOperation::Keep);

		// Depth testing
		SetDepthTestingEnabled(true);
		SetDepthWritingEnabled(true);
		SetDepthCompareFunction(CompareFunction::Less);

		// Face culling
		SetFaceCullingMode(FaceCullingMode::Back);
		SetFrontFaceWinding(FrontFaceWinding::CounterClockwise);

		// Color blending 
		SetBlendingEnabled(false);
		SetBlendingColor(glm::vec4(0, 0, 0, 0));
		SetBlendingFactor(BlendingFactor::One, BlendingFactor::One);
	}

	void RenderState::BindTexture(Texture2D& texture, TextureSlot slot)
	{
		BindTextureImpl(texture, slot);
		m_BoundTextures[EnumToInt<int>(slot)] = &texture;
	}

	void RenderState::BindShader(Shader& shader)
	{
		BindShaderImpl(shader);
		m_BoundShader = &shader;
	}

	void RenderState::BindMesh(Mesh& mesh)
	{
		BindMeshImpl(mesh);
		m_BoundMesh = &mesh;
	}

	void RenderState::SetClearColor(const glm::vec4& clearColor)
	{
		SetClearColorImpl(clearColor);
		m_ClearColor = clearColor;
	}

	void RenderState::SetClearDepth(float clearDepth)
	{
		SetClearDepthImpl(clearDepth);
		m_ClearDepth = clearDepth;
	}

	void RenderState::SetClearStencil(float clearStencil)
	{
		SetClearStencilImpl(clearStencil);
		m_ClearStencil = clearStencil;
	}

	void RenderState::SetClearBits(BufferClearBits clearBits)
	{
		SetClearBitsImpl(clearBits);
		m_ClearBits = clearBits;
	}

	void RenderState::SetStencilParameters(CompareFunction compareFunction, int compareValue, int readMask, int writeMask)
	{
		JERBOA_ASSERT(compareValue >= 0, "Compare value must be greater than 0");
		JERBOA_ASSERT(readMask >= 0 && readMask < 256, "Mask needs must be greater than 0");
		JERBOA_ASSERT(writeMask >= 0 && writeMask < 256, "Mask needs to be in range 0 to 255/0xFF");
		
		compareValue = std::max(0, compareValue);
		readMask = std::max(0, readMask);
		writeMask = std::max(0, writeMask);

		SetStencilParametersImpl(compareFunction, compareValue, readMask, writeMask);
		m_StencilCompareFunction = compareFunction;
		m_StencilCompareValue = compareValue;
		m_StencilReadMask = readMask;
		m_StencilWriteMask = writeMask;
	}

	void RenderState::SetStencilTestingEnabled(bool enabled)
	{
		SetStencilTestingEnabledImpl(enabled);
		m_StencilTestingEnabled = enabled;
	}

	void RenderState::SetStencilOperations(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass)
	{
		SetStencilOperationsImpl(stencilFail, depthFail, pass);
		m_StencilFailOperation = stencilFail;
		m_StencilDepthFailOperation = depthFail;
		m_StencilPassOperation = pass;
	}

	void RenderState::SetDepthTestingEnabled(bool enabled)
	{
		SetDepthTestingEnabledImpl(enabled);
		m_DepthTestingEnabled = enabled;
	}

	void RenderState::SetDepthWritingEnabled(bool enabled)
	{
		SetDepthWritingEnabledImpl(enabled);
		m_DepthWritingEnabled = enabled;
	}

	void RenderState::SetDepthCompareFunction(CompareFunction compareFunction)
	{
		SetDepthCompareFunctionImpl(compareFunction);
		m_DepthCompareFunction = compareFunction;
	}

	void RenderState::SetFaceCullingMode(FaceCullingMode mode)
	{
		SetFaceCullingModeImpl(mode);
		m_FaceCullingMode = mode;
	}

	void RenderState::SetFrontFaceWinding(FrontFaceWinding winding)
	{
		SetFrontFaceWindingImpl(winding);
		m_FrontFaceWinding = winding;
	}

	void RenderState::SetBlendingEnabled(bool enabled)
	{
		SetBlendingEnabledImpl(enabled);
		m_BlendingEnabled = enabled;
	}

	void RenderState::SetBlendingColor(glm::vec4 color)
	{
		SetBlendingColorImpl(color);
		m_BlendingColor = color;
	}

	void RenderState::SetBlendingFactor(BlendingFactor source, BlendingFactor destination)
	{
		SetBlendingFactorImpl(source, destination);
		m_BlendingFactorSource = source;
		m_BlendingFactorDestination = destination;
	}
}