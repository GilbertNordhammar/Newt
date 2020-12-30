#include "Jerboa/EntryPoint.h"
#include "JerboaApp.h"

Jerboa::Application* Jerboa::CreateApplication() {
	Jerboa::ApplicationProps props;

	return new JerboaClient::JerboaApp(props);
}
