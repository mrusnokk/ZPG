/**
 * @file Application.h
 *
 * @brief Core application class managing the GLFW window and the main rendering loop.
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "Scene.h"
#include "Model.h"

class Application {
private:
	GLFWwindow* window;
	int width;
	int height;
	std::string title;
	std::vector<Scene*> scenes;
	int activeSceneIndex;

	ShaderProgram* shaderProgram;
	ShaderProgram* shaderProgram2;

	Model* bushModel;
	Model* treeModel;
	Model* sphereModel;
	Model* triangleModel;
	Model* loginModel;


public:
	Application(int width, int height, const std::string& title);
	~Application();

	void initialization();
	void createShaders();
	void addScene(Scene* scene);
	void run();
	void createModels();
	void createScenes();
};