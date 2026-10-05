#include "Application.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/triangle.h"
#include "Models/sphere.h"
#include "Models/rus0130.h"
#include <iostream>

Application::Application(int width, int height, const std::string& title)
	: width(width), height(height), title(title), window(nullptr), activeSceneIndex(0), shaderProgram(nullptr),shaderProgram2(nullptr),
	treeModel(nullptr), bushModel(nullptr), sphereModel(nullptr), triangleModel(nullptr), loginModel(nullptr){	
}

Application::~Application() {
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
}

void Application::createShaders() {
	shaderProgram = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
	shaderProgram2 = new ShaderProgram("Shaders/basic.vert", "Shaders/basic2.frag");
}

void Application::addScene(Scene* scene) {
	scenes.push_back(scene);
}
void Application::run() {

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && scenes.size() > 0) activeSceneIndex = 0;
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && scenes.size() > 1) activeSceneIndex = 1;
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && scenes.size() > 2) activeSceneIndex = 2;
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && scenes.size() > 3) activeSceneIndex = 3;

		if (!scenes.empty()) {
			scenes[activeSceneIndex]->draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::createModels() {
	bushModel = new Model(bushes, sizeof(bushes), 8730);
	treeModel = new Model(tree, sizeof(tree), 92814);
	sphereModel = new Model(sphere, sizeof(sphere), 17280);
	triangleModel = new Model(triangle, sizeof(triangle), 3);
	loginModel = new Model(login_model, sizeof(login_model), 6996);
}

void Application::createScenes() {

	Scene* triangleScene = new Scene();
	Scene* sphereScene = new Scene();
	Scene* forestScene = new Scene();
	Scene* loginScene = new Scene();

	DrawableObject* login = new DrawableObject(loginModel, shaderProgram);
	login->setScale(0.5f, 0.5f, -1.0f);
	loginScene->addObject(login);

	DrawableObject* mySignature = new DrawableObject(loginModel, shaderProgram);
	mySignature->setPosition(-0.8f, 0.8f, 0.0f);
	mySignature->setScale(0.1f, 0.1f, -1.0f);

	DrawableObject* triangle = new DrawableObject(triangleModel, shaderProgram);
	triangleScene->addObject(triangle);
	triangleScene->addObject(mySignature);

	DrawableObject* sphere = new DrawableObject(sphereModel, shaderProgram);
	sphereScene->addObject(sphere);
	sphereScene->addObject(mySignature);

	for (size_t i = 0; i < 12; i++) {
		DrawableObject* tree = new DrawableObject(treeModel, shaderProgram);
		tree->setPosition(-1.0f + (i * 0.15f), -1.0f, 0.0f);
		tree->setScale(0.1f, 0.1f, 1.0f);
		forestScene->addObject(tree);
	}

	for (size_t i = 0; i < 12; i++) {
		DrawableObject* bush = new DrawableObject(bushModel, shaderProgram);
		bush->setPosition(-0.9f + (i * 0.15f), -1.0f, 0.0f);
		bush->setScale(0.3f, 0.3f, 1.0f);
		forestScene->addObject(bush);
	}

	DrawableObject* sun = new DrawableObject(sphereModel, shaderProgram2);
	sun->setPosition(0.8f, 0.8f, 1.0f);
	sun->setScale(0.1f, 0.1f, 1.0f);
	
	forestScene->addObject(sun);
	forestScene->addObject(mySignature);

	scenes.push_back(triangleScene);
	scenes.push_back(sphereScene);
	scenes.push_back(forestScene);
	scenes.push_back(loginScene);
}