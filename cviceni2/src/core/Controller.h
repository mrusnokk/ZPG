/**@file Controller.h
 * @brief Class responsible for handling keyboard and mouse inputs to control the camera.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "camera/Camera.h"
#include "scenes/Scene.h"

class Model;
class ShaderProgram;
class Texture;
class DrawableObject;
class Translate;

enum class ControlMode {
    INFO,
    INSERT_POINTS,
    INSERT_CUBIC,
    INSERT_SPLINE,
    DELETE_OBJECT
};

struct ControlPoint {
    int id;
    DrawableObject* obj;
    Translate* tr;
};

class Controller {
private:
    double lastX = 0.0;
    double lastY = 0.0;
    bool firstMouse = true;

    bool xKeyPressed = false;
    bool qKeyPressed = false;
    bool fKeyPressed = false;
    bool enterKeyPressed = false;
    bool leftMousePressed = false;

    int modeIndex = 0;
    ControlMode modes[5] = {
        ControlMode::INFO,
        ControlMode::INSERT_POINTS,
        ControlMode::INSERT_CUBIC,
        ControlMode::INSERT_SPLINE,
        ControlMode::DELETE_OBJECT
    };

    glm::vec3 pointA = glm::vec3(0.0f);
    glm::vec3 pointB = glm::vec3(0.0f);
    glm::vec3 pointC = glm::vec3(0.0f);
    bool hasPointA = false;
    bool hasPointB = false;
    bool hasPointC = false;

    std::vector<Translate*> splinePoints;
    std::vector<ControlPoint> controlPoints;
    int selectedPointIndex = -1;

    int nextSpawnedObjectId = 200;

    Model* sphereModel = nullptr;
    ShaderProgram* sphereShader = nullptr;
    Texture* sphereTexture = nullptr;
    Model* pointModel = nullptr;
    ShaderProgram* pointShader = nullptr;
    ShaderProgram* selectedPointShader = nullptr;
    Camera* registeredCamera = nullptr;

    void syncCamera(Camera* camera);
    bool unprojectPixel(GLint x, GLint newy, Camera* camera, glm::vec3& outWorldPos);
    void ensureSphereResources(Camera* camera);
    int allocateObjectId();
    void clearSelection();
    Translate* spawnControlPoint(Scene* scene, Camera* camera, const glm::vec3& pos);
    int spawnSmiley(Scene* scene, Camera* camera, Transformation* movement);
    void spawnSpline(Scene* scene, Camera* camera);

public:
    Controller();
    ~Controller();
    void processInput(GLFWwindow* window, Scene* scene);
    void processInput(GLFWwindow* window, Camera* camera);
};
