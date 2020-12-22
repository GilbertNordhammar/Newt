#pragma once

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Layer.h"

namespace JerboaClient {
	class EditorLayer : public Jerboa::Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
	};
}

