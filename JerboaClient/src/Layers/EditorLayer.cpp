#include "EditorLayer.h"

namespace JerboaClient {
	void EditorLayer::OnAttach() {
		JERBOA_LOG_INFO("EditorLayer attached");
	}

	void EditorLayer::OnDetach() {
		JERBOA_LOG_INFO("EditorLayer deattached");
	}
}