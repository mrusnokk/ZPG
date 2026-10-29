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
#include "scenes/Scene.h"
#include "core/Controller.h"

class Application {
private:
	GLFWwindow* window;
	int width;
	int height;
	std::string title;
	std::vector<Scene*> scenes;
	int activeSceneIndex;
	Controller* controller = nullptr;
	static void frameBufferSizeCallback(GLFWwindow* window, int w, int h);
	void onResize(int w, int h);

public:
	Application(int width, int height, const std::string& title);
	~Application();

	void initialization();
	void addScene(Scene* scene);
	void run();
};