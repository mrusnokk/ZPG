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
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        
        GLubyte color[4] = {};
        GLfloat depth = 1.0f;
        GLuint index = 0;

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        int windowWidth, windowHeight;
        int framebufferWidth, framebufferHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

        GLint x = static_cast<GLint>(mouseX * framebufferWidth / windowWidth);
        GLint y = static_cast<GLint>(mouseY * framebufferHeight / windowHeight);
        GLint newy = framebufferHeight - 1 - y;

        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        printf("Clicked on pixel %d, %d, color %02x%02x%02x%02x, depth %f, stencil index %u\n",
            x, newy, color[0], color[1], color[2], color[3], depth, index);

        glm::vec3 screenX = glm::vec3(x, newy, depth);
        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 projection = camera->getProjectionMatrix();
        glm::vec4 viewPort = glm::vec4(0, 0, framebufferWidth, framebufferHeight);

        glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

        printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

    }
}