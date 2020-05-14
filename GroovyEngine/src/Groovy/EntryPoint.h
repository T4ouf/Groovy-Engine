#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GroovyEngine::Application* GroovyEngine::CreateApplication();

int main(int argc, char** argv) {
	auto app = GroovyEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif