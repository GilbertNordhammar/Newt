#include "Jerboa/Core/Application.h"
#include "Layers/EditorLayer.h"

namespace JerboaClient {
	class JerboaApp : public Jerboa::Application
	{
	public:
		JerboaApp(const Jerboa::ApplicationProps& props)
			: Application(props) {}
	private:
		virtual void OnInit() {
			PushLayer(new EditorLayer());
		}
	};
}
