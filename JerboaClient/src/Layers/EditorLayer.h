#pragma once

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Layer.h"
 
#include "Jerboa/Core/Events/MouseMovedEvent.h"
#include "Jerboa/Core/Events/WindowResizeEvent.h"
#include "Jerboa/Rendering/Camera.h"
#include "Jerboa/Rendering/VertexBuffer.h"
#include "Jerboa/Rendering/IndexBuffer.h"
#include "Jerboa/Rendering/Shader.h"
#include "Jerboa/Rendering/Texture.h"
#include "Jerboa/Rendering/lights/PointLight.h"
#include "Jerboa/Scene/Transform.h"

#include "Jerboa/Platform/OpenGL/OpenGL_VertexArray.h"

#include <memory>
#include <vector>

namespace JerboaClient {
	class EditorLayer : public Jerboa::Layer
	{
	public:
		EditorLayer();

		virtual void OnUpdate() override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	private:
		void OnWindowResize(const Jerboa::WindowResizeEvent& evnt);

		Jerboa::Camera mCamera;
		std::shared_ptr<Jerboa::Shader> mPBRShader;
		std::shared_ptr<Jerboa::Shader> mPointLightShader;

		std::vector<Jerboa::Transform> mTransforms;

		std::shared_ptr<Jerboa::VertexBuffer> mSphereVertexBuffer;
		std::shared_ptr<Jerboa::IndexBuffer> mSphereIndexBuffer;
		Jerboa::OpenGL_VertexArray mSphereVao;

		std::shared_ptr<Jerboa::Texture2D> mAlbedoTexture;
		std::shared_ptr<Jerboa::Texture2D> mAmbientOcclusionTexture;
		std::shared_ptr<Jerboa::Texture2D> mNormalTexture;
		std::shared_ptr<Jerboa::Texture2D> mMetallicTexture;
		std::shared_ptr<Jerboa::Texture2D> mRoughnessTexture;

		std::vector<Jerboa::PointLight> mPointLights;

		Jerboa::EventObserver mWindowResizeObserver;
	};
}

