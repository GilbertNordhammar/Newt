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
		std::shared_ptr<Jerboa::Shader> mTestShader;

		std::vector<Jerboa::Transform> mBoxTransforms;
		Jerboa::OpenGL_VertexArray mBoxVao;
		std::shared_ptr<Jerboa::VertexBuffer> mBoxVertexBuffer;
		std::shared_ptr<Jerboa::IndexBuffer> mBoxIndexBuffer;
		std::shared_ptr<Jerboa::Texture2D> mBoxTexture;

		Jerboa::EventObserver mWindowResizeObserver;
	};
}

