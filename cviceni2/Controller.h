/**@file Controller.h
 * @brief Class responsible for handling keyboard and mouse inputs to control the camera.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

class Controller {
private:
	double lastX = 0.0f, lastY=0.0f;
	bool firstMouse = true;
public:
	Controller() = default;
	void processInput(GLFWwindow* window, Camera* camera);
};