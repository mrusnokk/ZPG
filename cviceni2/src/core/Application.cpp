#include "core/Application.h"
#include <iostream>

Application::Application(int width, int height, const std::string& title)
	: width(width), height(height), title(title), window(nullptr), activeSceneIndex(0){
	this->controller = new Controller();
}

Application::~Application() {
	
	for (Scene* s : scenes) {
		delete s;
	}
	delete this->controller;
	if (window) {
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

void Application::initialization() {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
		exit(EXIT_FAILURE);
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

	glEnable(GL_DEPTH_TEST);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
}

void Application::addScene(Scene* scene) {
	scenes.push_back(scene);
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int w, int h) {
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) app->onResize(w, h);
}

void Application::onResize(int w, int h) {
	if (w == 0 || h == 0) return;
	glViewport(0, 0, w, h);
	float aspect = w / static_cast<float>(h);
	for (Scene* s : scenes)
		s->getCam()->setAspectRatio(aspect);
}

void Application::run() {

	glEnable(GL_DEPTH_TEST);

	int fbW, fbH;
	glfwGetFramebufferSize(window, &fbW, &fbH);
	onResize(fbW, fbH);

	while (!glfwWindowShouldClose(window)) {

		//glClearColor(130/255.0f, 200 / 255.0f, 229 / 255.0f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && scenes.size() > 0) activeSceneIndex = 0;
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && scenes.size() > 1) activeSceneIndex = 1;
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && scenes.size() > 2) activeSceneIndex = 2;
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && scenes.size() > 3) activeSceneIndex = 3;

		
		if (!scenes.empty()) {
			controller->processInput(window, scenes[activeSceneIndex]->getCam());
			scenes[activeSceneIndex]->draw();
			scenes[activeSceneIndex]->update();
		}
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}