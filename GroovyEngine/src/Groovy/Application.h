#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace GroovyEngine {


	class GE_API Application{
		
	private:

		std::unique_ptr<Window> m_Window; //application's window

		bool m_Running = true; //is the application running ?
		
		LayerStack m_LayerStack;

		bool OnWindowClosed(WindowCloseEvent& e);

		static Application* s_Instance;

	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Run();


	};

	//To be defined in the client application
	Application* CreateApplication();


}