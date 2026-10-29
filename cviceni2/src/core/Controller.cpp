#include "core/Controller.h"

void Controller::processInput(GLFWwindow* window, Camera* camera) {
	if (camera == nullptr || window == nullptr) {
		return;
	}
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->toFront();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->toBack();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->toLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->toRight();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        if (firstMouse) {
            lastX = mouseX;
            lastY = mouseY;
            firstMouse = false;
        }
        float x = static_cast<float>(mouseX - lastX);
        float y = static_cast<float>(lastY - mouseY);

        lastX = mouseX;
        lastY = mouseY;

        camera->processMouseMovement(x, y);
    }
    else {
        firstMouse = true;
    }
}