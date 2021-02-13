#include "EditorLayer.h"
#include "imgui.h"

#include "Jerboa/UI/ImGui/ImGuiApp.h"

#include "Jerboa/Core/Input.h"
#include "Jerboa/Core/Time.h"

#include "Jerboa/Rendering/Renderer.h"
#include "Jerboa/Rendering/PrimitiveFactory.h"

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
        
        if (Jerboa::Window::Get()->GetCursorMode() == Jerboa::CursorMode::Disabled) {
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
        }

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
        mAlbedoTexture->Bind(0);

        for (auto bt : mTransforms) {
            auto modelMatrix = glm::translate(glm::mat4(1.0), bt.GetPosition());
            modelMatrix = modelMatrix * glm::toMat4(bt.GetOrientation());
            mTestShader->SetMat4("mat_model", modelMatrix);

            glBindVertexArray(mSphereVao);
            Jerboa::Renderer::Draw(mSphereIndexBuffer->GetCount());
        }
	}

	void EditorLayer::OnAttach() {
		JERBOA_LOG_INFO("EditorLayer attached");

        Jerboa::Window::Get()->SetCursorMode(Jerboa::CursorMode::Disabled);
        
        const int nSpheres = 10;
        mTransforms.reserve(nSpheres);
        for (int i = 0; i < nSpheres; i++) {
            std::random_device rand;
            std::uniform_real_distribution<float> dist(-5, 5);
            auto position = glm::vec3(dist(rand), dist(rand), dist(rand) - 5);
            auto rotation = glm::vec3(dist(rand), dist(rand), dist(rand));
            mTransforms.emplace_back(position, rotation);
        }

        // TODO: Remove explicit OpenGL calls
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glBindVertexArray(mSphereVao);

        std::vector<float> sphereVertices;
        std::vector<uint32_t> sphereIndices;
        Jerboa::PrimitiveFactory::GenerateUVSphere(16, 16, sphereVertices, sphereIndices);
       
        int verticesSize = sphereVertices.size() * sizeof(sphereVertices[0]);
        mSphereVertexBuffer = Jerboa::VertexBuffer::Create(sphereVertices.data(), verticesSize, Jerboa::VertexBufferUsage::Static,
        {
            { Jerboa::ShaderDataType::Float3 }, // pos
            { Jerboa::ShaderDataType::Float2 }, // UV
            { Jerboa::ShaderDataType::Float3 }, // normal
        });

        int indicesSize = sphereIndices.size() * sizeof(sphereIndices[0]);
        mSphereIndexBuffer = Jerboa::IndexBuffer::Create(sphereIndices.data(), indicesSize);

        mTestShader = Jerboa::Shader::Create("assets/shaders/Test.glsl");
        mAlbedoTexture = Jerboa::Texture2D::Create("assets/textures/pbr/stone-wall-1k/diffuse.png", Jerboa::TextureType::Diffuse);
	}

	void EditorLayer::OnDetach() {
		JERBOA_LOG_INFO("EditorLayer deattached");
	}
	
	void EditorLayer::OnWindowResize(const Jerboa::WindowResizeEvent& evnt)
	{
		JERBOA_LOG_TRACE("window resized to {}x{}", evnt.width, evnt.height);
	}
}