#include "GroovyEngine.h"

class Sandbox : public GroovyEngine::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

GroovyEngine::Application* GroovyEngine::CreateApplication() {
	return new Sandbox();
}