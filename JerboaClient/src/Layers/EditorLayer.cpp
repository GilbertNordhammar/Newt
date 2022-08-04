#include "EditorLayer.h"

#include "Jerboa/Core/Input.h"
#include "Jerboa/Core/Time.h"
#include "Jerboa/Rendering/PrimitiveFactory.h"
#include "Jerboa/Resource/Loaders/ShaderLoaderGLSL.h"
#include "Jerboa/Resource/Loaders/TextureLoader.h"
#include "Jerboa/UI/ImGui/ImGuiApp.h"

#include "imgui.h"
#include "optick.h"
#include <random>


using namespace Jerboa;

namespace JerboaClient {
	EditorLayer::EditorLayer(Jerboa::Renderer& renderer)
		: m_Renderer(renderer),
        m_RenderState(renderer.GetState()),
        m_ShaderState(renderer.GetShaderState()),
        m_ResourceAllocator(renderer.GetAllocator()),
        m_Camera(Jerboa::Camera(glm::vec3(-1, 0, 5), Jerboa::CameraType::Perspective, glm::radians(60.0)))
	{
        m_EventObserver.Subscribe(this, &EditorLayer::OnWindowResize);
    }

	void EditorLayer::OnImGuiRender()
	{
		//ImGui::ShowDemoWindow();

		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGui::Begin("Shader properties");

        static ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        static ImGuiColorEditFlags flags;
        flags |= ImGuiColorEditFlags_DisplayRGB;
        ImGui::ColorPicker3("Light Color", (float*)& color, flags);

        static float power = 0.3;
        //ImGui::InputFloat("Power", &power);
        ImGui::SliderFloat("Light Power", &power, 0.0f, 2.0f);
        
        for (auto& pl : mPointLights) {
            pl.SetColor(glm::vec3(color.x, color.y, color.z));
            pl.SetPower(power);
        }

        ImGui::SliderFloat("Normal Map Mult", &mNormalMapMult, 0.0f, 10.0f);
		ImGui::End();
	}

	void EditorLayer::OnUpdate()
	{
        OPTICK_EVENT("EditorLayer::OnUpdate()");
        auto& camTrans = m_Camera.GetTransform();
        
        if (Jerboa::Window::Get()->GetCursorMode() == Jerboa::CursorMode::Disabled) {
            auto mouseMovement = Jerboa::Input::GetMouseMovement();
            auto rotation = -mouseMovement * Jerboa::Time::GetDeltaTime() * 100.0f;
            auto ori = glm::quat(Jerboa::Transform::GetWorldUp() * rotation.x) * camTrans.GetOrientation();
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

            camTrans.SetOrientation(ori);
        }

        float moveSpeed = 0.1;
        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::W)) 
            camTrans.SetPosition(camTrans.GetPosition() + camTrans.GetForward() * moveSpeed);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::S))
            camTrans.SetPosition(camTrans.GetPosition() - camTrans.GetForward() * moveSpeed);

        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::D))
            camTrans.SetPosition(camTrans.GetPosition() + camTrans.GetRight() * moveSpeed);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::A))
            camTrans.SetPosition(camTrans.GetPosition() - camTrans.GetRight() * moveSpeed);

        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::E))
            camTrans.SetPosition(camTrans.GetPosition() + camTrans.GetUp() * moveSpeed);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::Q))
            camTrans.SetPosition(camTrans.GetPosition() - camTrans.GetUp() * moveSpeed);

        if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::_1))
            Jerboa::Window::Get()->SetCursorMode(Jerboa::CursorMode::Disabled);
        else if (Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::_2))
            Jerboa::Window::Get()->SetCursorMode(Jerboa::CursorMode::Normal);

        // Drawing point light represenations
     
        m_RenderState.BindShader(m_PointLightShader);
        m_ShaderState.SetMat4("mat_VP", m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix());
        for (auto& pointLight : mPointLights) {
            auto modelMatrix = glm::translate(glm::mat4(1.0), pointLight.Position);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1));
            m_ShaderState.SetMat4("mat_model", modelMatrix);
            m_ShaderState.SetVec3("color", pointLight.GetColor());

            m_Renderer.Draw(m_SphereMesh);
        }

        m_RenderState.BindShader(m_PBRShader);
        
        // MVP
        m_ShaderState.SetMat4("mat_view", m_Camera.GetViewMatrix());
        m_ShaderState.SetMat4("mat_projection", m_Camera.GetProjectionMatrix());
        m_ShaderState.SetMat4("mat_VP", m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix());
        
        // Textures
        m_ShaderState.SetInt("material.albedo", 0);
        m_RenderState.BindTexture(m_AlbedoTexture, Jerboa::TextureSlot::S0);
        
        m_ShaderState.SetInt("material.ao", 1);
        m_RenderState.BindTexture(m_AmbientOcclusionTexture, Jerboa::TextureSlot::S1);

        m_ShaderState.SetInt("material.normal", 2);
        m_RenderState.BindTexture(m_NormalTexture, Jerboa::TextureSlot::S2);

        m_ShaderState.SetInt("material.metallic", 3);
        m_RenderState.BindTexture(m_MetallicTexture, Jerboa::TextureSlot::S3);

        m_ShaderState.SetInt("material.roughness", 4);
        m_RenderState.BindTexture(m_RoughnessTexture, Jerboa::TextureSlot::S4);

        // Camera & Lights
        m_ShaderState.SetVec3("cameraWorldPos", m_Camera.GetTransform().GetPosition());
        m_ShaderState.SetInt("nPointLights", mPointLights.size());
        
        for (int i = 0; i < mPointLights.size(); i++) {
            std::string pl = "pointLights[" + std::to_string(i) + "]";
            
            m_ShaderState.SetVec3(pl + ".color", mPointLights[i].GetColor());
            m_ShaderState.SetFloat(pl + ".power", mPointLights[i].GetPower());
            m_ShaderState.SetVec3(pl + ".position", mPointLights[i].Position);
        }

        // Misc
        m_ShaderState.SetBool("useGamma", !Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::G));
        m_ShaderState.SetBool("useNormalMap", !Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::N));
        m_ShaderState.SetBool("reorthogonalize", !Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::B));
        m_ShaderState.SetBool("toggle", Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::T));
        m_ShaderState.SetFloat("normalMapMult", mNormalMapMult);
 
        static const float rotationSpeed = 0.2;
        float rotation = 0;
        if(!Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::R))
            rotation += Jerboa::Time::GetDeltaTime() * rotationSpeed;
        for (auto& trans : mTransforms) {
            auto modelMatrix = glm::translate(glm::mat4(1.0), trans.GetPosition());
            trans.Rotate(rotation, trans.GetUp());
            modelMatrix = modelMatrix * glm::toMat4(trans.GetOrientation());
            m_ShaderState.SetMat4("mat_model", modelMatrix);

            m_Renderer.Draw(m_SphereMesh);
        }
	}

	void EditorLayer::OnAttach() {
		JERBOA_LOG_INFO("EditorLayer attached");

        Jerboa::Window::Get()->SetCursorMode(Jerboa::CursorMode::Disabled);
        
        const int nSpheres = 10;
        mTransforms.reserve(nSpheres);
        mPointLights.reserve(nSpheres);
        for (int i = 0; i < nSpheres; i++) {
            std::random_device rand;
            std::uniform_real_distribution<float> dist(-7, 7);
            auto position = glm::vec3(dist(rand), dist(rand), dist(rand) - 5);
            auto rotation = glm::vec3(dist(rand), dist(rand), dist(rand));
            mTransforms.emplace_back(position, rotation);

            dist = std::uniform_real_distribution<float>(1.0, 1.5);
            auto posPointLight = position + glm::vec3(dist(rand), dist(rand), dist(rand));
            mPointLights.push_back(Jerboa::PointLight(glm::vec3(1.0f), 1.0f, posPointLight));
        }

        std::vector<float> sphereVertices;
        std::vector<uint32_t> sphereIndices;
        Jerboa::PrimitiveFactory::GenerateUVSphere(32, 16, 1.0f, glm::vec2(1.0), sphereVertices, sphereIndices);
       
        int verticesSize = sphereVertices.size() * sizeof(sphereVertices[0]);
        
        auto sphereVertexData = Jerboa::VertexBufferData(sphereVertices.data(), verticesSize, Jerboa::VertexBufferUsage::Static,
        {
            { Jerboa::ShaderDataType::Float3 }, // pos
            { Jerboa::ShaderDataType::Float2 }, // UV
            { Jerboa::ShaderDataType::Float3 }, // normal
            { Jerboa::ShaderDataType::Float3 }, // tangent
            { Jerboa::ShaderDataType::Float3 }, // bitangent
        });

        int indicesSize = sphereIndices.size() * sizeof(sphereIndices[0]);
        auto sphereIndexData = Jerboa::IndexBufferData(sphereIndices.data(), indicesSize);

        m_SphereMesh.Create(sphereVertexData, &sphereIndexData, Jerboa::PrimitiveType::Triangle, m_Renderer.GetAllocatorPtr());

        m_PBRShader.Create(ShaderLoaderGLSL::Load("assets/shaders/pbr/Standard.glsl"), m_ResourceAllocator);
        m_PointLightShader.Create(ShaderLoaderGLSL::Load("assets/shaders/pbr/PointLight.glsl"), m_ResourceAllocator);


        m_AlbedoTexture.Create( Jerboa::TextureType::Albedo, Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/albedo.png"), m_ResourceAllocator);
        m_AmbientOcclusionTexture.Create(Jerboa::TextureType::AmbientOcclusion, Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/ao.png"), m_ResourceAllocator);
        m_NormalTexture.Create(Jerboa::TextureType::Normal, Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/normal-ogl.png"), m_ResourceAllocator);
        m_MetallicTexture.Create(Jerboa::TextureType::Metallic, Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/metallic.png"), m_ResourceAllocator);
        m_RoughnessTexture.Create(Jerboa::TextureType::Roughness, Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/roughness.png"), m_ResourceAllocator);
	}

	void EditorLayer::OnDetach() {
		JERBOA_LOG_INFO("EditorLayer deattached");
	}
	
	void EditorLayer::OnWindowResize(const Jerboa::WindowResizeEvent& evnt)
	{
		JERBOA_LOG_TRACE("window resized to {}x{}", evnt.width, evnt.height);
	}
}