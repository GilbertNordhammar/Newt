#pragma once

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Layer.h"
 
#include "Jerboa/Core/EventBus.h"

#include "Jerboa/Core/Events/MouseMovedEvent.h"
#include "Jerboa/Core/Events/WindowResizeEvent.h"
#include "Jerboa/Core/Window.h"
#include "Jerboa/Rendering/Camera.h"
#include "Jerboa/Rendering/Resource/FrameBuffer.h"
#include "Jerboa/Rendering/Resource/VertexBuffer.h"
#include "Jerboa/Rendering/Resource/IndexBuffer.h"
#include "Jerboa/Rendering/Resource/Shader.h"
#include "Jerboa/Rendering/Resource/Texture.h"
#include "Jerboa/Rendering/lights/PointLight.h"
#include "Jerboa/Scene/Transform.h"

#include "Jerboa/Rendering/Resource/Mesh.h"
#include "Jerboa/Rendering/Renderer.h"
#include "Jerboa/Rendering/Renderer2D.h"

#include <memory>
#include <vector>

namespace JerboaClient {
	class EditorLayer : public Jerboa::Layer
	{
	public:
		EditorLayer(Jerboa::Window& window, Jerboa::Renderer& renderer);

		virtual void OnUpdate() override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	private:
		void CreateFramebuffers();

		void OnWindowResize(const Jerboa::WindowResizeEvent& evnt);

		Jerboa::Window& m_Window;
		Jerboa::Renderer& m_Renderer;
		Jerboa::RenderState& m_RenderState;
		Jerboa::ShaderState& m_ShaderState;
		Jerboa::GPUResourceAllocator& m_ResourceAllocator;
		Jerboa::Renderer2D m_Renderer2D;

		Jerboa::Camera m_Camera;
		Jerboa::Shader m_PBRShader;
		Jerboa::Shader m_PointLightShader;
		Jerboa::Shader m_PassthroughPP;
		Jerboa::Shader m_ShowDepthPP;

		std::vector<Jerboa::Transform> mTransforms;

		Jerboa::Mesh m_SphereMesh;
		Jerboa::FrameBuffer m_FrameBuffer1;
		Jerboa::FrameBuffer m_FrameBuffer2;

		Jerboa::Texture2D m_AlbedoTexture;
		Jerboa::Texture2D m_AmbientOcclusionTexture;
		Jerboa::Texture2D m_NormalTexture;
		Jerboa::Texture2D m_MetallicTexture;
		Jerboa::Texture2D m_RoughnessTexture;

		float m_NormalMapMult = 5.0f;

		std::vector<Jerboa::PointLight> mPointLights;

		Jerboa::EventObserver m_EventObserver;
		
		// For debugging
		bool m_ShowColorBuffer = true;
		bool m_ShowDepthBuffer = false;
	};
}

