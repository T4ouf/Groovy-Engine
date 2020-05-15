#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GroovyEngine::Application* GroovyEngine::CreateApplication();

int main(int argc, char** argv) {

	GroovyEngine::Log::Init();

	GE_CORE_WARN("Initialized log !");
	GE_INFO("Initialized log !");

	auto app = GroovyEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif