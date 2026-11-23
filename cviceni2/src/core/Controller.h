/**@file Controller.h
 * @brief Class responsible for handling keyboard and mouse inputs to control the camera.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "camera/Camera.h"
#include "scenes/Scene.h"

class Model;
class ShaderProgram;
class Texture;

enum class ControlMode {
    INFO,
    INSERT_POINTS,
    INSERT_CUBIC,
    DELETE_OBJECT
};

class Controller {
private:
    double lastX = 0.0;
    double lastY = 0.0;
    bool firstMouse = true;

    bool xKeyPressed = false;
    bool qKeyPressed = false;
    bool fKeyPressed = false;
    bool leftMousePressed = false;

    int modeIndex = 0;
    ControlMode modes[4] = { ControlMode::INFO, ControlMode::INSERT_POINTS, ControlMode::INSERT_CUBIC,ControlMode::DELETE_OBJECT };

    
    glm::vec3 pointA = glm::vec3(0.0f);
	glm::vec3 pointB = glm::vec3(0.0f);
	glm::vec3 pointC = glm::vec3(0.0f);
    bool hasPointA = false;
	bool hasPointB = false;
	bool hasPointC = false;

    int nextSpawnedObjectId = 200;

    Model* sphereModel = nullptr;
    ShaderProgram* sphereShader = nullptr;
    Texture* sphereTexture = nullptr;
    Camera* registeredCamera = nullptr;

public:
    Controller();
    ~Controller();
    void processInput(GLFWwindow* window, Scene* scene);
    void processInput(GLFWwindow* window, Camera* camera);
};
