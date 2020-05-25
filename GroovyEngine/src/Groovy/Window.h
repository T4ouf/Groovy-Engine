#pragma once

#include "gepch.h"

#include "Groovy/Core.h"
#include "Groovy/Events/Event.h"

namespace GroovyEngine {

	//Struct representing all the properties of a window
	struct WindowProps {

		std::string Title;
		unsigned int Width, Height;
		
		//constructor
		WindowProps(const std::string& title = "Groovy Engine", unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height){}
	};

	//Interface representing a desktop system-based window
	class GE_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		//Virtual destructor
		virtual ~Window() {};
		
		virtual void OnUpdate() = 0;

		//Getter
		virtual unsigned int GetWidth() const  = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallBack(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		//Window creation 
		static Window* Create(const WindowProps& props = WindowProps());

	};

}