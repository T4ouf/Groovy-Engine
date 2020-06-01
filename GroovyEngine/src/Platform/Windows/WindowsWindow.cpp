#include "gepch.h"
#include "WindowsWindow.h"

#include "glad/glad.h"

//include events
#include "Groovy/Events/ApplicationEvent.h"
#include "Groovy/Events/KeyEvent.h"
#include "Groovy/Events/MouseEvent.h"


namespace GroovyEngine {

	static bool s_GLFWInitialized = false;

	//Function that handles GLFW errors and log them (debugging purposes)
	static void GLFWErrorCallback(int errorCode, const char* description) {
		GE_CORE_ERROR("GLFW ERROR {0} : {1}", errorCode, description);
	}

	Window* Window::Create(const WindowProps& props) { return new WindowsWindow(props); }

	WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }

	WindowsWindow::~WindowsWindow() { Shutdown(); };

	//Main init function => initialize the newly created window + GLFW if it was not initialized
	void WindowsWindow::Init(const WindowProps& props) {

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		GE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		//We check if GLFW is already init
		if (!s_GLFWInitialized) {
			//TODO : glfwtermite on system shutdown
			int success = glfwInit();
			GE_CORE_ASSERT(success, "Could not initialize GLFW !");
			glfwSetErrorCallback(GLFWErrorCallback); //Set a debug callback for GLFW errors
			s_GLFWInitialized = true;
		}

		//We create the window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		//Load OpenGL functions from Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//ASSERT Successful loading
		GE_CORE_ASSERT(status, "Failed to initialize Glad !");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// --- set GLFW callbacks ---

		//Window resize
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int height) {
				
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //We retrieve the data tha we attached to our window (m_data)
				
				//resize the window
				data.Width = width;
				data.Height = height;
			
				
				WindowResizeEvent event(width, height);	//Create the appropriate groovy engine event
				data.EventCallback(event); //Dispatch the event
				
			}
		);

		//Window close
		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window) {

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //We retrieve the data tha we attached to our window (m_data)
				WindowCloseEvent event = WindowCloseEvent();	//Create the appropriate groovy engine event
				data.EventCallback(event); //Dispatch the event

			}
		);

		//Key callbacks
		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods) {

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //We retrieve the data tha we attached to our window (m_data)
				
				//Switch on the type of key Event
				switch (action) {
					case GLFW_PRESS: {
				
						KeyPressedEvent event(key, 0); 	//Create the appropriate groovy engine event
						data.EventCallback(event); //Dispatch the event
						break;
					}
					case GLFW_RELEASE:{
						KeyReleasedEvent event(key); 	//Create the appropriate groovy engine event
						data.EventCallback(event); //Dispatch the event
						break;
					}
					case GLFW_REPEAT:{
						KeyPressedEvent event(key, 1); 	//Create the appropriate groovy engine event (Note : GLFW does not count => we set to one)
						data.EventCallback(event); //Dispatch the event
						break;
					}
				}
				
			}
		);

		// Char callback
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //We retrieve the data tha we attached to our window (m_data)
			KeyTypedEvent event(keycode);
			data.EventCallback(event); //Dispatch the event

		});


		//Mouse button callbacks
		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int button, int action, int mods) {

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //We retrieve the data tha we attached to our window (m_data)

				//Switch on the type of Mouse Button Event
				switch (action) {
					case GLFW_PRESS: {

						MouseButtonPressedEvent event(button); 	//Create the appropriate groovy engine event
						data.EventCallback(event); //Dispatch the event
						break;
					}
					case GLFW_RELEASE: {
						MouseButtonReleasedEvent event(button); 	//Create the appropriate groovy engine event
						data.EventCallback(event); //Dispatch the event
						break;
					}
				}
			}
		);

		//Mouse Scroll callback
		glfwSetScrollCallback(m_Window,
			[](GLFWwindow* window, double xOffset, double yOffset) {

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //We retrieve the data tha we attached to our window (m_data)

				MouseScrolledEvent event = MouseScrolledEvent(float(xOffset), float(yOffset)); 	//Create the appropriate groovy engine event
				data.EventCallback(event); //Dispatch the event
			}
		);

		//Mouse Move callback
		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double x, double y) {

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //We retrieve the data tha we attached to our window (m_data)

				MouseMovedEvent event = MouseMovedEvent(float(x), float(y)); 	//Create the appropriate groovy engine event
				data.EventCallback(event); //Dispatch the event
			}
		);
		// -------- 

	}
	
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		
		glfwPollEvents();
		glfwSwapBuffers(m_Window);

	};

	//Setup vsync
	void WindowsWindow::SetVSync(bool enabled) {

		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;

	}
	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}

}
