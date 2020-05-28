#include "gepch.h"	//PCH must be included first in every .cpp file
#include "Application.h"

namespace GroovyEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)



	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());

		//We bind the OnEvent() function to the window callback
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
	}
	
	Application::~Application() {}

	void Application::OnEvent(Event& e) {

		EventDispatcher eventDispatcher = EventDispatcher(e);

		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));	//We bind "WindowCloseEvent" to the OnWindowClosed function

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
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
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