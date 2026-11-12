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
    DELETE_OBJECT
};

class Controller {
private:
    double lastX = 0.0;
    double lastY = 0.0;
    bool firstMouse = true;

    bool xKeyPressed = false;
    bool qKeyPressed = false;
    bool leftMousePressed = false;

    int modeIndex = 0;
    ControlMode modes[3] = { ControlMode::INFO, ControlMode::INSERT_POINTS, ControlMode::DELETE_OBJECT };

    bool hasPointA = false;
    glm::vec3 pointA = glm::vec3(0.0f);

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
