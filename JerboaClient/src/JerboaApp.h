#include "Jerboa/Core/Application.h"
#include "Layers/EditorLayer.h"

namespace JerboaClient {
	class JerboaApp : public Jerboa::Application
	{
	public:
		virtual void OnStart() {
			PushLayer(new EditorLayer());
		}
	};
}
