#include "jerboa-pch.h"
#include "RenderState.h"

namespace Jerboa
{
	BufferClearBits operator|(BufferClearBits lhs, BufferClearBits rhs);

	void RenderState::ResetStateToDefaultValues()
	{
		// Buffer clearing
		SetClearColor(glm::vec4(0, 0, 0, 0));
		SetClearDepth(1);
		SetClearStencil(0);
		SetClearBits(BufferClearBits::None);

		// Stencil testing
		SetStencilCompareFunction(CompareFunction::Equal, 1);
		SetStencilTestingEnabled(false);
		//SetStencilOperations(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass);
		//SetStencilReadMask(int readMask);
		//SetStencilWriteMask(int writeMask);

		// Depth testing
		//SetDepthTestingEnabled(bool enabled);
		//SetDepthWritingEnabled(bool enabled);
		//SetDepthCompareFunction(CompareFunction compareFunction);

		// Face culling
		//SetFaceCullingMode(FaceCullingMode mode);
		//SetFrontFaceWinding(FrontFaceWinding winding);

		// Color blending 
		//SetBlendingEnabled(bool enabled);
		//SetBlendingColor(glm::vec4 color);
		//SetBlendingFactor(BlendingFactor factor);
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
		SetClearStencil(clearStencil);
		m_ClearStencil = clearStencil;
	}

	void RenderState::SetClearBits(BufferClearBits clearBits)
	{
		SetClearBitsImpl(clearBits);
		m_ClearBits = clearBits;
	}

	void RenderState::SetStencilCompareFunction(CompareFunction compareFunction, int compareValue)
	{
		JERBOA_ASSERT(compareValue > 0, "Compare value must be greater than 0")
		compareValue = std::max(0, compareValue);
		SetStencilCompareFunctionImpl(compareFunction, compareValue);
		m_StencilCompareFunction = compareFunction;
		m_StencilCompareValue = compareValue;
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

	void RenderState::SetStencilReadMask(int readMask)
	{
		JERBOA_ASSERT(readMask > 0 && readMask < 256, "Mask needs must be greater than 0")
		readMask = std::max(0, readMask);
		SetStencilReadMaskImpl(readMask);
		m_StencilReadMask = readMask;
	}

	void RenderState::SetStencilWriteMask(int writeMask)
	{
		JERBOA_ASSERT(writeMask > 0 && writeMask < 256, "Mask needs to be in range 0 to 255/0xFF")
		writeMask = std::max(0, writeMask);
		SetStencilWriteMaskImpl(writeMask);
		m_StencilWriteMask = writeMask;
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
		SetDepthCompareFunction(compareFunction);
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

	void RenderState::SetBlendingFactor(BlendingFactor factor)
	{
		SetBlendingFactorImpl(factor);
		m_BlendingFactor = factor;
	}
}