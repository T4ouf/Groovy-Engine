#pragma once

#include "Core.h"
#include "Window.h"

namespace GroovyEngine {


	class GE_API Application{
	private:

		std::unique_ptr<Window> m_Window; //application's window

		bool m_Running = true; //is the application running ?

	public:
		Application();
		virtual ~Application();
		
		void Run();

	};

	//To be defined in the client application
	Application* CreateApplication();


}