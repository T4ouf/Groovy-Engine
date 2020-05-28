#include "gepch.h"
#include "LayerStack.h"
namespace GroovyEngine {

	LayerStack::LayerStack() {
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack() {

		//We delete all the layers of the stack (we get ownership when the layer get in the stack)
		for (Layer* layer : m_Layers) {
			delete layer;
		}

	}

	//Insertion on the top of the stack
	void LayerStack::PushLayer(Layer* layer) {
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	//Insertion at the end of the stack (Overlays need to be rendered last to be in front)
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	//NOTE : layer removal does give the ownership back => layers aren't deleted !

	void LayerStack::PopLayer(Layer* layer) {
		//We search the layer to check if it is in the stack
		auto iterator = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (iterator != m_Layers.end()) {
			m_Layers.erase(iterator);
			m_LayerInsert--;
		}

	}

	void LayerStack::PopOverlay(Layer* overlay) {
		
		//We search the layer to check if it is in the stack
		auto iterator = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		
		if (iterator != m_Layers.end()) {
			m_Layers.erase(iterator);
		}
	
	}

}