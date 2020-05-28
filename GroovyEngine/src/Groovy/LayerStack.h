#pragma once

#include "Core.h"
#include "Layer.h"

namespace GroovyEngine {

	/**
	 * LayerStack class :
	 * Class that represents a "stack" of layers. (It is not a stack because we need to be able to reverse-iterate it for event propagation)
	 * (It acts essentially as a wrapper around the vector<Layer*> member that it has)
	 */
	class GE_API LayerStack {
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;

	public:

		//constructor/destructor
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		//iterators
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end()   { return m_Layers.end(); }

	};

}