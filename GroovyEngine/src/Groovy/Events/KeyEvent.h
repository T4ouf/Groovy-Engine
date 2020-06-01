#pragma once

#include "Event.h"


namespace GroovyEngine {

	//Abstract key event
	class GE_API KeyEvent : public Event {
	protected:
		int m_KeyCode; //Key code of the key event

		//constructor
		KeyEvent(int keyCode) : m_KeyCode(keyCode){}
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput); //We define the categories of this event class
	};

	//Key pressed event
	class GE_API KeyPressedEvent : public KeyEvent {
	
	private:
		int m_RepeatCount;

	public:

		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent : " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		//We define what type of event this is
		EVENT_CLASS_TYPE(KeyPressed);
	};

	//Key released event
	class GE_API KeyReleasedEvent : public KeyEvent {
	public:

		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode){}
		
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent : " << m_KeyCode;
			return ss.str();
		}

		//We define what type of event this is
		EVENT_CLASS_TYPE(KeyReleased);
	};

	// Key typed Event
	class GE_API KeyTypedEvent : public KeyEvent {
	public:

		KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent : " << m_KeyCode;
			return ss.str();
		}

		//We define what type of event this is
		EVENT_CLASS_TYPE(KeyTyped);


	};

}