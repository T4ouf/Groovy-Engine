#include "gepch.h"	//PCH must be included first in every .cpp file
#include "Application.h"

namespace GroovyEngine {
	
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		//ensure Application is a singleton
		GE_CORE_ASSERT(s_Instance == nullptr, "Application already exists !")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		//We bind the OnEvent() function to the window callback
		m_Window->SetEventCallBack(GE_BIND_EVENT_FN(Application::OnEvent));
	}
	
	Application::~Application() {}

	void Application::OnEvent(Event& e) {

		EventDispatcher eventDispatcher = EventDispatcher(e);

		eventDispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClosed));	//We bind "WindowCloseEvent" to the OnWindowClosed function

		//reversed-iteration of the layer stack
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			
			(*--it)->OnEvent(e);	//propagate the event to the next layer
			if (e.Handled) break;	//if the event is handled => we don't need to propagate it to the other layers
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run() {

		while (m_Running) {

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}

	}

}