#include "EditorLayer.h"
#include "imgui.h"

#include "Jerboa/UI/ImGui/ImGuiApp.h"

#include "Jerboa/Core/Input.h"
#include "Jerboa/Core/Time.h"

#include "Jerboa/Rendering/Renderer.h"

#include <random>

namespace JerboaClient {
	EditorLayer::EditorLayer()
		: mWindowResizeObserver(Jerboa::EventObserver::Create(GetSharedEventBus(), this, &EditorLayer::OnWindowResize)),
        mCamera(Jerboa::Camera(glm::vec3(-1, 0, 5), Jerboa::CameraType::Perspective, glm::radians(60.0)))
	{
    }

	void EditorLayer::OnImGuiRender()
	{
		ImGui::ShowDemoWindow();

		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGui::Begin("Window 1");
		ImGui::Button("Hello");
		ImGui::End();

		ImGui::Begin("Window 2");
		ImGui::Button("Hello");
		ImGui::End();
	}

	void EditorLayer::OnUpdate()
	{
        auto& trans = mCamera.GetTransform();

        auto mouseMovement = Jerboa::Input::GetMouseMovement();
        auto rotation = -mouseMovement * Jerboa::Time::GetDeltaTime() * 100.0f;
        auto ori = glm::quat(Jerboa::Transform::GetWorldUp() * rotation.x) * trans.GetOrientation();
        ori = ori * glm::quat(Jerboa::Transform::GetWorldRight() * rotation.y);

        auto pitch = glm::atan(2 * ori.x * ori.w - 2 * ori.y * ori.z, 1 - 2 * ori.x * ori.x - 2 * ori.z * ori.z);
        auto pitchLimit = glm::radians(89.0);
        if (pitch > pitchLimit) {
            float pitchDiff = pitch - pitchLimit;
            ori = ori * glm::quat(Jerboa::Transform::GetWorldRight() * -pitchDiff);
        }
        else if (pitch < -pitchLimit) {
            float pitchDiff = pitch - (-pitchLimit);
            ori = ori * glm::quat(Jerboa::Transform::GetWorldRight() * -pitchDiff);
        }

        trans.SetOrientation(ori);

        float moveSpeed = 0.1;
        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::W)) 
            trans.SetPosition(trans.GetPosition() + trans.GetForward() * moveSpeed);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::S))
            trans.SetPosition(trans.GetPosition() - trans.GetForward() * moveSpeed);

        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::D))
            trans.SetPosition(trans.GetPosition() + trans.GetRight() * moveSpeed);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::A))
            trans.SetPosition(trans.GetPosition() - trans.GetRight() * moveSpeed);

        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::E))
            trans.SetPosition(trans.GetPosition() + trans.GetUp() * moveSpeed);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::Q))
            trans.SetPosition(trans.GetPosition() - trans.GetUp() * moveSpeed);

        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::_1))
            Jerboa::Window::Get()->SetCursorMode(Jerboa::CursorMode::Disabled);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::_2))
            Jerboa::Window::Get()->SetCursorMode(Jerboa::CursorMode::Normal);

        mTestShader->Bind();
        mTestShader->SetMat4("mat_view", mCamera.GetViewMatrix());
        mTestShader->SetMat4("mat_projection", mCamera.GetProjectionMatrix());
        mTestShader->SetMat4("mat_VP", mCamera.GetProjectionMatrix() * mCamera.GetViewMatrix());
        mTestShader->SetInt("texture_diffuse", 0);
        mBoxTexture->Bind(0);

        glBindVertexArray(mBoxVao);
        for (auto bt : mBoxTransforms) {
            auto modelMatrix = glm::translate(glm::mat4(1.0), bt.GetPosition());
            modelMatrix = modelMatrix * glm::toMat4(bt.GetOrientation());
            mTestShader->SetMat4("mat_model", modelMatrix);
            Jerboa::Renderer::Draw(mBoxIndexBuffer->GetCount());
        }
	}

	void EditorLayer::OnAttach() {
		JERBOA_LOG_INFO("EditorLayer attached");

        Jerboa::Window::Get()->SetCursorMode(Jerboa::CursorMode::Disabled);
        
        const int nBoxes = 10;
        mBoxTransforms.reserve(nBoxes);
        
        for (int i = 0; i < nBoxes; i++) {
            std::random_device rand;
            std::uniform_real_distribution<float> dist(-5, 5);
            auto position = glm::vec3(dist(rand), dist(rand), dist(rand));
            auto rotation = glm::vec3(dist(rand), dist(rand), dist(rand));
            mBoxTransforms.emplace_back(position, rotation);
        }

        // TODO: Remove explicit OpenGL calls
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glBindVertexArray(mBoxVao);

        float vertices[] = {
            // pos                  // tex coords

                // front
            -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,     // 0 left bottom  
             0.5f, -0.5f, 0.5f,     1.0f, 0.0f,     // 1 right bottom
             0.5f,  0.5f, 0.5f,     1.0f, 1.0f,     // 2 right top
            -0.5f,  0.5f, 0.5f,     0.0f, 1.0f,     // 3 left top

                // back
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,     // 4 left bottom  
             0.5f, -0.5f, -0.5f,     1.0f, 0.0f,     // 5 right bottom
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     // 6 right top
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     // 7 left top

                // right
            0.5f, -0.5f, -0.5f,     0.0f, 0.0f,     // 8 left bottom  
            0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     // 9 right bottom
            0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     // 10 right top
            0.5f,  0.5f, -0.5f,     0.0f, 1.0f,      // 11 left top

                // left
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,     // 12 left bottom  
            -0.5f, -0.5f,  0.5f,     1.0f, 0.0f,     // 13 right bottom
            -0.5f,  0.5f,  0.5f,     1.0f, 1.0f,     // 14 right top
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,      // 15 left top

               // top
           -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,     // 16 left bottom
            0.5f,  0.5f,  0.5f,     1.0f, 0.0f,     // 17 right bottom
           -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,     // 18 left top
            0.5f,  0.5f, -0.5f,     1.0f, 1.0f,     // 19 right top

                // bottom
           -0.5f,  -0.5f,  0.5f,     0.0f, 0.0f,     // 20 left bottom
            0.5f,  -0.5f,  0.5f,     1.0f, 0.0f,     // 21 right bottom
           -0.5f,  -0.5f, -0.5f,     0.0f, 1.0f,     // 22 left top
            0.5f,  -0.5f, -0.5f,     1.0f, 1.0f,     // 23 right top
        };

        mBoxVertexBuffer = Jerboa::VertexBuffer::Create(vertices, sizeof(vertices), Jerboa::VertexBufferUsage::Static,
        {
            { Jerboa::ShaderDataType::Float3 },
            { Jerboa::ShaderDataType::Float2 }
        });

        uint32_t indices[] = {
            0, 1, 2, /**/ 2, 3, 0, // front
            4, 6, 5, /**/ 6, 4, 7,   // back,
            8, 10, 9, /**/ 10, 8, 11,  // right
            12, 13, 14, /**/ 14, 15, 12,   // left
            16, 19, 18 /**/, 16, 17, 19, // top
            20, 22, 23, /**/ 20, 23, 21 // bottom
        };
        mBoxIndexBuffer = Jerboa::IndexBuffer::Create(indices, sizeof(indices));

        mTestShader = Jerboa::Shader::Create("assets/shaders/Test.glsl");
        mBoxTexture = Jerboa::Texture2D::Create("assets/textures/steel-wooden-container/diffuse.png", Jerboa::TextureType::Diffuse);
	}

	void EditorLayer::OnDetach() {
		JERBOA_LOG_INFO("EditorLayer deattached");
	}
	
	void EditorLayer::OnWindowResize(const Jerboa::WindowResizeEvent& evnt)
	{
		JERBOA_LOG_TRACE("window resized to {}x{}", evnt.width, evnt.height);
	}
}