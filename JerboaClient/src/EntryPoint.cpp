#include "Jerboa/EntryPoint.h"
#include "JerboaApp.h"

Jerboa::Application* Jerboa::CreateApplication() {
	return new JerboaClient::JerboaApp();
}
