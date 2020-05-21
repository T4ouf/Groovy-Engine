#pragma once

#include "Groovy/Core.h"


namespace GroovyEngine {

	// Blocking events for now \\

	//All curent types of events the Groovy Engine can handle
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, 
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//Grouping event types by categories (event filtering by category)
	//We use binary mask to detect each category
	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	// --- We define some useful macro (fulfill the fields from the Event base class) ---
	
	//Automatically handles the class with the right EventType
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

	//Define the categories of the event based on the input
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//Abstract Event class : represents the base of all events in the Groovy Engine
	class GE_API Event {

		friend class EventDispatcher; //The event dispatcher must access event properties
	
	public:
		//Getters
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category; //We check the right bit with a binary AND
		}

	protected:
		//Is the event handled somewhere ?
		bool m_Handled = false;
	};


	class EventDispatcher {

		//T is any EventType
		template<typename T>
		using EventFn = std::function<bool(T&)>; //We define what a event callback is : function that takes in the Event and returns a boolean

	private:
		Event& m_Event;

	public:
		EventDispatcher(Event& event) : m_Event(event){}

		template<typename T>
		bool Dispatch(EventFn<T> f) {

			//If the event we are trying to dispatch has the same type as the callback provided (as a parameter)...
			if (m_Event.GetEventType() == T::GetStaticType()) {
				//then we run the callback
				m_Event.m_Handled = f(*(T*)&m_Event);
				return true;	//and notify that we dispatched the event
			}

			return false;
		}

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}


