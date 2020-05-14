#pragma once

#include "Core.h"

namespace GroovyEngine {


	class GE_API Application{
	
	public:
		Application();
		virtual ~Application();
		
		void Run();

	};

	//To be defined in the client application
	Application* CreateApplication();


}