#pragma once
#include "Event.h"

namespace GroovyEngine {

	// --- Window Resize Event ---
	class GE_API WindowResizeEvent : public Event {
	private:
		unsigned int m_Width, m_Height;

	public:
		//Constructor
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent : " << m_Width << "," << m_Height;
			return ss.str();
		}
	
		EVENT_CLASS_TYPE(WindowResize)					//We define the type of this event
		EVENT_CLASS_CATEGORY(EventCategoryApplication)  //We define the category of this event class	
	};
	// ---------------------

	// --- Window Close Event ---
	class GE_API WindowCloseEvent : public Event {
	public:
		//Constructor
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)					//We define the type of this event
		EVENT_CLASS_CATEGORY(EventCategoryApplication)  //We define the category of this event class	
	};
	// ---------------------


	// Not sure if the following events will be useful... Just in case, we have them... 

	// --- Application Tick Event ---
	class GE_API AppTickEvent : public Event {
	public:
		//Constructor
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)						//We define the type of this event
		EVENT_CLASS_CATEGORY(EventCategoryApplication)  //We define the category of this event class	
	};
	// ---------------------

	// --- Application Update Event ---
	class GE_API AppUpdateEvent : public Event {
	public:
		//Constructor
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)						//We define the type of this event
		EVENT_CLASS_CATEGORY(EventCategoryApplication)  //We define the category of this event class	
	};
	// ---------------------

	// --- Application Render Event ---
	class GE_API AppRenderEvent : public Event {
	public:
		//Constructor
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)						//We define the type of this event
		EVENT_CLASS_CATEGORY(EventCategoryApplication)  //We define the category of this event class	
	};
	// ---------------------
}