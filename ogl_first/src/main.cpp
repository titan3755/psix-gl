#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// function prototypes

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
	std::cout << "Initializing OpenGL application ..." << std::endl;
	glfwInit();
	// set OpenGL version to 3.3 and window metadata
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "OGL First Program", NULL, NULL);
	// check if window is created successfully
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// make the window's context current
	glfwMakeContextCurrent(window);
	// load GLAD to manage function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// set the viewport size
	glViewport(0, 0, 800, 600);
	// set the window resize callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// print OpenGL version and renderer
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "\nOpenGL application initialized successfully!" << std::endl;
	// render loop
	while (!glfwWindowShouldClose(window)) {
		// inputs
		processInput(window);
		// rendering
		glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// clear all the resources and exit program
	glfwTerminate();
	return 0;
}

// callback function for window resize

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// process input function

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}