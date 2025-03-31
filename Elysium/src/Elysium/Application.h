#pragma once

#include "Core.h"

namespace Elysium {
	class ELYSIUM_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// Defined in CLIENT
	Application* CreateApplication();
}
	