#include "EditorLayer.h"

#include "Jerboa/Core/Input.h"
#include "Jerboa/Core/Time.h"
#include "Jerboa/Rendering/PrimitiveFactory.h"
#include "Jerboa/Resource/Loaders/MeshLoader.h"
#include "Jerboa/Resource/Loaders/ShaderLoaderGLSL.h"
#include "Jerboa/Resource/Loaders/TextureLoader.h"
#include "Jerboa/UI/ImGui/ImGuiApp.h"

#include "imgui.h"
#include "optick.h"
#include <random>


using namespace Jerboa;

namespace JerboaClient {
	EditorLayer::EditorLayer(Jerboa::Window& window, Jerboa::Renderer& renderer)
		: m_Window(window),
        m_Renderer(renderer),
        m_RenderState(renderer.GetState()),
        m_ShaderState(renderer.GetShaderState()),
        m_ResourceAllocator(renderer.GetAllocator()),
        m_Camera(Jerboa::Camera(glm::vec3(-1, 0, 5), Jerboa::CameraType::Perspective, glm::radians(60.0))),
        m_Renderer2D(renderer)
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

        ImGui::SliderFloat("Normal Map Mult", &m_NormalMapMult, 0.0f, 10.0f);
        ImGui::Checkbox("Show color", &m_ShowColorBuffer);
        ImGui::Checkbox("Show depth", &m_ShowDepthBuffer);
		ImGui::End();
	}

	void EditorLayer::OnUpdate()
	{
        OPTICK_EVENT("EditorLayer::OnUpdate()");

        using namespace Jerboa;

        m_RenderState.SetClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
        m_RenderState.SetClearBits(BufferClearBits::Color | BufferClearBits::Depth | BufferClearBits::Stencil);

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

        // TODO: Uncomment this once stuff work
        m_RenderState.BeginRenderPass(m_FrameBuffer1); 

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
        m_RenderState.BindTexture(m_AlbedoTexture, Jerboa::TextureSlot::_0);
        
        m_ShaderState.SetInt("material.ao", 1);
        m_RenderState.BindTexture(m_AmbientOcclusionTexture, Jerboa::TextureSlot::_1);

        m_ShaderState.SetInt("material.normal", 2);
        m_RenderState.BindTexture(m_NormalTexture, Jerboa::TextureSlot::_2);

        m_ShaderState.SetInt("material.metallic", 3);
        m_RenderState.BindTexture(m_MetallicTexture, Jerboa::TextureSlot::_3);

        m_ShaderState.SetInt("material.roughness", 4);
        m_RenderState.BindTexture(m_RoughnessTexture, Jerboa::TextureSlot::_4);

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
        m_ShaderState.SetFloat("normalMapMult", m_NormalMapMult);
 

        m_RenderState.SetStencilTestingEnabled(true);
        m_RenderState.SetStencilParameters(CompareFunction::Always, 255, 0xFF, 0xFF);
        m_RenderState.SetStencilOperations(StencilOperation::Replace, StencilOperation::Replace, StencilOperation::Replace);

        static const float rotationSpeed = 0.2;
        float rotation = 0;
        if(!Jerboa::Input::IsKeyHeldDown(Jerboa::KeyCode::R))
            rotation += Jerboa::Time::GetDeltaTime() * rotationSpeed;
        for (auto& trans : mTransforms) {
            auto modelMatrix = glm::translate(glm::mat4(1.0), trans.GetPosition());
            trans.Rotate(rotation, trans.GetUp());
            modelMatrix = modelMatrix * glm::toMat4(trans.GetOrientation());
            m_ShaderState.SetMat4("mat_model", modelMatrix);

            m_Renderer.Draw(*m_TestMesh);
            //m_Renderer.Draw(m_SphereMesh);
        }

        m_RenderState.SetStencilTestingEnabled(false);
    
        if (m_ShowColorBuffer && m_ShowDepthBuffer)
        {
            // Draw color buffer
            m_RenderState.SetViewport(0, 0, m_Window.GetWidth() / 2, m_Window.GetHeight() / 2);
            m_Renderer2D.DrawFullscreenPostEffect(m_PassthroughPP, m_FrameBuffer1);

            // Draw depth buffer
            m_RenderState.SetViewport(m_Window.GetWidth() / 2, 0, m_Window.GetWidth() / 2, m_Window.GetHeight() / 2);
            m_Renderer2D.DrawFullscreenPostEffect(m_ShowDepthPP, m_FrameBuffer1);

            m_RenderState.SetViewport(0, 0, m_Window.GetWidth(), m_Window.GetHeight()); // restore viewport
        }
        else
        {
            Shader& shaderPP = m_ShowDepthBuffer ? m_ShowDepthPP : m_PassthroughPP;
            m_Renderer2D.DrawFullscreenPostEffect(shaderPP, m_FrameBuffer1);
        }
	}

	void EditorLayer::OnAttach() 
    {
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

        /*std::vector<float> sphereVertices;
        std::vector<uint32> sphereIndices;*/
        //Jerboa::PrimitiveFactory::GenerateUVSphere(32, 16, 1.0f, glm::vec2(1.0), sphereVertices, sphereIndices);
       
        auto sphereVertexData = Jerboa::VertexBufferData(
            {
                Jerboa::VertexAttributeType::Position,
                Jerboa::VertexAttributeType::TextureCoordinates1,
                Jerboa::VertexAttributeType::Normal,
                Jerboa::VertexAttributeType::Tangent
            }
        );
        Jerboa::IndexBufferData sphereIndexData;

        Jerboa::PrimitiveFactory::GenerateUVSphere(32, 16, 1.0f, glm::vec2(1.0), sphereVertexData.m_Data, sphereIndexData.m_Data);

        // Create meshes
        Jerboa::MeshLoader meshLoader(m_ResourceAllocator);
        m_TestMesh = std::unique_ptr<Jerboa::Mesh>(meshLoader.Load("assets/meshes/monkey.fbx", Jerboa::MeshLoader::LoadConfig::CalculateTangents));
        m_SphereMesh.AddSubMesh(sphereVertexData, &sphereIndexData, Jerboa::PrimitiveType::Triangle, m_Renderer.GetAllocator());

        // Create shaders
        m_PBRShader.Create(ShaderLoaderGLSL::Load("assets/shaders/pbr/Standard.glsl"), m_ResourceAllocator);
        m_PointLightShader.Create(ShaderLoaderGLSL::Load("assets/shaders/pbr/PointLight.glsl"), m_ResourceAllocator);

        ShaderDataGLSL dataPassthroughPP = ShaderLoaderGLSL::Load("assets/shaders/PostProcessing/default.vert", "assets/shaders/PostProcessing/Passthrough.frag");
        m_PassthroughPP.Create(dataPassthroughPP, m_Renderer.GetAllocator());

        ShaderDataGLSL dataShowDepthPP = ShaderLoaderGLSL::Load("assets/shaders/PostProcessing/default.vert", "assets/shaders/PostProcessing/ShowDepth.frag");
        m_ShowDepthPP.Create(dataShowDepthPP, m_Renderer.GetAllocator());

        // Create read-only textures
        m_AlbedoTexture.CreateFromTextureData(Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/albedo.png"), TextureUsage::Read, m_ResourceAllocator);
        m_AmbientOcclusionTexture.CreateFromTextureData(Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/ao.png"), TextureUsage::Read, m_ResourceAllocator);
        m_NormalTexture.CreateFromTextureData(Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/normal-ogl.png"), TextureUsage::Read, m_ResourceAllocator);
        m_MetallicTexture.CreateFromTextureData(Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/metallic.png"), TextureUsage::Read, m_ResourceAllocator);
        m_RoughnessTexture.CreateFromTextureData(Jerboa::TextureLoader::LoadTexture("assets/textures/pbr/beaten-up-metal/roughness.png"), TextureUsage::Read, m_ResourceAllocator);

        // Create framebuffers
        CreateFramebuffers();
	}

    void EditorLayer::CreateFramebuffers()
    {
        std::shared_ptr<Texture2D> colorAttachment1 = std::make_shared<Texture2D>();
        TextureConfig textureConfig;
        textureConfig.m_Width = m_Window.GetWidth();
        textureConfig.m_Height = m_Window.GetHeight();
        textureConfig.m_MipMapInterpolationFilter = Jerboa::MipmapInterpolationFilter::None;
        textureConfig.m_SamplerWrappingMode = Jerboa::TextureSamplingWrapMode::ClampToEdge;
        textureConfig.m_SamplingFilter = Jerboa::TextureSamplingFilter::Linear;
        textureConfig.m_Usage = Jerboa::TextureUsage::Read | Jerboa::TextureUsage::Write;
        textureConfig.m_PixelFormat = Jerboa::PixelFormat::RGBA;
        colorAttachment1->Create(textureConfig, m_ResourceAllocator);

        textureConfig.m_PixelFormat = PixelFormat::Depth;
        std::shared_ptr<Texture2D> depthStencilAttachment = std::make_shared<Texture2D>();
        depthStencilAttachment->Create(textureConfig, m_ResourceAllocator);

        FrameBufferConfig fbConfig1;
        fbConfig1.m_ColorAttachments[0].Set(colorAttachment1, RenderPassBeginAction::Clear);
        fbConfig1.m_DepthStencilAttachment.Set(depthStencilAttachment, RenderPassBeginAction::Clear);
        m_FrameBuffer1.Create(fbConfig1, m_ResourceAllocator);
    }

	void EditorLayer::OnDetach() {
		JERBOA_LOG_INFO("EditorLayer deattached");
	}
	
	void EditorLayer::OnWindowResize(const Jerboa::WindowResizeEvent& evnt)
	{
		JERBOA_LOG_TRACE("window resized to {}x{}", evnt.width, evnt.height);
        CreateFramebuffers();
	}
}