#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace GroovyEngine {
	
	/**
	 * Abstract Layer class : 
	 * A layer is basically a part of the application that is processed separately
	 * The processing order is determiner by its position in the layer stack
	 * NOTE : this class should be inherited by user's layers (specify the function's behaviour)
	 */
	class GE_API Layer {
	
	protected:
		std::string m_DebugName;

	public:
		
		//Constructor
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(){}
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName() const { return m_DebugName; }

	};


}

