#include "gepch.h"	//PCH must be included first in every .cpp file
#include "Application.h"

#include "Groovy/Log.h"


namespace GroovyEngine {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	
	
	Application::~Application() {


	}

	void Application::Run() {

		while (m_Running) {
			m_Window->OnUpdate();
		}

	}

}