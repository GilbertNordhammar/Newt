#include "EditorLayer.h"
#include "imgui.h"
#include "Jerboa/UI/ImGui/ImGuiApp.h"

namespace JerboaClient {
	EditorLayer::EditorLayer()
		: mWindowResizeObserver(Jerboa::EventObserver::Create(GetSharedEventBus(), this, &EditorLayer::OnWindowResize))
	{}


	void EditorLayer::OnUpdate()
	{
		Jerboa::UI::ImGuiApp::BeginFrame();

		ImGui::ShowDemoWindow();

		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		ImGui::Begin("Window 1");
		ImGui::Button("Hello");
		ImGui::End();

		ImGui::Begin("Window 2");
		ImGui::Button("Hello");
		ImGui::End();
		
		Jerboa::UI::ImGuiApp::EndFrame();
	}

	void EditorLayer::OnAttach() {
		JERBOA_LOG_INFO("EditorLayer attached");
	}

	void EditorLayer::OnDetach() {
		JERBOA_LOG_INFO("EditorLayer deattached");
	}
	void EditorLayer::OnWindowResize(const Jerboa::WindowResizeEvent& evnt)
	{
		JERBOA_LOG_TRACE("window resized to {}x{}", evnt.width, evnt.height);
	}
}