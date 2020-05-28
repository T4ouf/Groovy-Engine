#pragma once

#include "Groovy/Window.h"
#include "GLFW/glfw3.h"

namespace GroovyEngine {

	/**
	 * Windows implementation of a window for the Groovy Engine
	 * Implementation based on GLFW library
	 */
	class WindowsWindow : public Window {
	private:
		GLFWwindow* m_Window;
		
		//Storing a struct that we will directly pass to GLFW 
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		//Getter
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallBack(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	};




}