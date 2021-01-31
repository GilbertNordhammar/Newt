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

#include "Jerboa/Platform/OpenGL/OpenGL_VertexArray.h"

#include <memory>

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
		Jerboa::OpenGL_VertexArray mVao;
		std::shared_ptr<Jerboa::VertexBuffer> mVertexBuffer;
		std::shared_ptr<Jerboa::IndexBuffer> mIndexBuffer;
		std::shared_ptr<Jerboa::Shader> mTestShader;
		std::shared_ptr<Jerboa::Texture2D> mTestTexture;

		Jerboa::EventObserver mWindowResizeObserver;
	};
}

