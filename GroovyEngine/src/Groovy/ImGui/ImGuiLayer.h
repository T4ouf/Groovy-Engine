#pragma once
#include "Groovy/Layer.h"
#include "Groovy/Events/ApplicationEvent.h"
#include "Groovy/Events/KeyEvent.h"
#include "Groovy/Events/MouseEvent.h"

namespace GroovyEngine {

	/**
	 * ImGuiLayer class :
	 * Debug Layer that will allow us to display & tweek easily variables
	 */
	class GE_API ImGuiLayer : public Layer {
	private:

		float m_Time = 0.0f;

		// --- Mouse events ---
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		// --- Key events ---
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		// --- Window events ---
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	
	public:
	
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	};

}

