// Github Repo: https://github.com/titan3755/psix-gl
// Author: titan3755
// Source code of psix-gl -->

// necessary includes

#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// constants

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 720;
constexpr auto TITLE = "OGL First Program";
constexpr auto SHADER_FILE_DIRECTORY = "C:\\Users\\mahmu\\Desktop\\codez\\vs\\cpp\\ogl_first\\ogl_first\\src\\shaders\\";

// vertex and fragment shader source code

const char* vertexShaderSource;
const char* fragmentShaderSource;

// function prototypes

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void calculateFPS(GLFWwindow* window);
const char* readShaderFileGLSL(const char* shaderFile);


int main() {
	// ---------------------------------------- start window initialization ----------------------------------------
	std::cout << "Initializing OpenGL application ..." << std::endl;
	glfwInit();
	// set OpenGL version to 3.3 and window metadata
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	// check if window is created successfully
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// make the window's context current
	glfwMakeContextCurrent(window);
	//// disable window resize (disabled)
	//glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
	// load GLAD to manage function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// set the viewport size
	glViewport(0, 0, WIDTH, HEIGHT);
	// set the window resize callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// ---------------------------------------- end window initialization ----------------------------------------
	// ---------------------------------------- start vertex shader initialization ----------------------------------------
	vertexShaderSource = readShaderFileGLSL((SHADER_FILE_DIRECTORY + std::string("vrtxone.vert")).c_str());
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	} else {
		std::cout << "Vertex shader compiled successfully!" << std::endl;
	}
	// ---------------------------------------- end vertex shader initialization ----------------------------------------
	// ---------------------------------------- start fragment shader initialization ----------------------------------------
	fragmentShaderSource = readShaderFileGLSL((SHADER_FILE_DIRECTORY + std::string("frgone.frag")).c_str());
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	else {
		std::cout << "Fragment shader compiled successfully!" << std::endl;
	}
	// ---------------------------------------- end fragment shader initialization ----------------------------------------
	// ---------------------------------------- start shader program initialization ----------------------------------------
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	else {
		std::cout << "Shader program linked successfully!" << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// ---------------------------------------- end shader program initialization ----------------------------------------
	// ---------------------------------------- start render initialization ----------------------------------------
	float vertices[] = {
		// positions
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // bottom left
	};
	// vertex buffer object
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 1. bind the vertex array object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 *sizeof(float)));
	glEnableVertexAttribArray(1);
	// ---------------------------------------- end render initialization ----------------------------------------
	// ---------------------------------------- start render loop and print status logs ----------------------------------------
	// print OpenGL version and renderer
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "\nOpenGL application initialized successfully!" << std::endl;
	// render loop
	float timeValue = glfwGetTime();
	float ofStValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ofstclr");
	while (!glfwWindowShouldClose(window)) {
		// calculate FPS
		calculateFPS(window);
		// inputs
		processInput(window);
		// rendering
		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		timeValue = glfwGetTime();
		ofStValue = (sin(timeValue) / 2.0f) + 0.5f;
		vertexColorLocation = glGetUniformLocation(shaderProgram, "ofstclr");
		glUniform3f(vertexColorLocation, ofStValue, ofStValue, ofStValue);
		// render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// clear all the resources and exit program
	glfwTerminate();
	return 0;
	// ---------------------------------------- terminate glfw and end program ----------------------------------------
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

// calculate FPS

void calculateFPS(GLFWwindow* window) {
	static double previousSeconds = glfwGetTime();
	static int frameCount;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime();
	elapsedSeconds = currentSeconds - previousSeconds;
	if (elapsedSeconds > 0.25) {
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;
		char title[256];
		sprintf_s(title, "OpenGL Application [FPS: %.2f] [ms/frame: %.2f]", fps, msPerFrame);
		glfwSetWindowTitle(window, title);
		frameCount = 0;
	}
	frameCount++;
}

// read shader file

const char* readShaderFileGLSL(const char* shaderFile) {
    std::ifstream file(shaderFile);
    std::string shaderCode = "";
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            shaderCode += line + "\n";
        }
        file.close();
		std::cout << "Shader file read successfully!" << std::endl;
    } else {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    // Allocate memory for the shader code and copy the string content
    char* code = new char[shaderCode.size() + 1];
	code = (char*)shaderCode.c_str();
    return code;
}