#include "GroovyEngine.h"

//Example of a user-defined layer
class ExampleLayer : public GroovyEngine::Layer {
public:
	ExampleLayer() : Layer("Example") {}
	
	void OnUpdate() override{
		GE_INFO("ExampleLayer::Update");
	}
	
	void OnEvent(GroovyEngine::Event& e) override {
	
		GE_TRACE("{0}", e);

	}

};


class Sandbox : public GroovyEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

GroovyEngine::Application* GroovyEngine::CreateApplication() {
	return new Sandbox();
}