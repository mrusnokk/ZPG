#include "core/Controller.h"
#include "models/uv_sphere.h"
#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Texture.h"
#include "rendering/DrawableObject.h"
#include "transform/TransformComposite.h"
#include "transform/Translate.h"
#include "transform/Rotate.h"
#include "transform/Scale.h"
#include "transform/LineMovement.h"
#include <cstdio>

Controller::Controller() {}

Controller::~Controller() {
    delete sphereModel;
    delete sphereShader;
    delete sphereTexture;
}

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

void Controller::processInput(GLFWwindow* window, Scene* scene) {
    if (scene == nullptr || window == nullptr) {
        return;
    }
    Camera* camera = scene->getCam();

    processInput(window, camera);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (!qKeyPressed) {
            qKeyPressed = true;
            modeIndex = (modeIndex + 1) % 3;
            hasPointA = false;

            if (modes[modeIndex] == ControlMode::INFO)
                printf("Mod: INFO\n");
            else if (modes[modeIndex] == ControlMode::INSERT_POINTS)
                printf("Mod: VKLADANI\n");
            else if (modes[modeIndex] == ControlMode::DELETE_OBJECT)
                printf("Mod: MAZANI\n");
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
        qKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        if (!xKeyPressed) {
            xKeyPressed = true;

            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            GLint x = (GLint)mouseX;
            GLint y = (GLint)mouseY;
            GLint newy = (GLint)camera->getResolution().y - y;

            GLfloat depth = 1.0f;
            glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

            if (depth < 1.0f && camera != nullptr) {
                glm::vec3 screenX = glm::vec3(x, newy, depth);
                glm::mat4 view = camera->getViewMatrix();
                glm::mat4 projection = camera->getProjectionMatrix();
                glm::vec4 viewPort = glm::vec4(0, 0, camera->getResolution().x, camera->getResolution().y);

                glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

                if (sphereModel == nullptr) {
                    sphereModel = new Model(UVSphereModel, sizeof(UVSphereModel), UVSphereVertexCount, 8);
                    sphereShader = new ShaderProgram("shaders/TextureShader.vert", "shaders/TextureShader.frag");
                    sphereTexture = new Texture("src/textures/smiley.png");
                }

                if (registeredCamera != camera) {
                    camera->obs_register(sphereShader);
                    registeredCamera = camera;
                }

                int objId = nextSpawnedObjectId++;
                DrawableObject* sphereObj = new DrawableObject(sphereModel, sphereShader, sphereTexture, objId);
                TransformComposite* tc = new TransformComposite();
                tc->addTransformation(new Translate(pos.x, pos.y + 0.2f, pos.z));
                tc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
                tc->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0f));
                sphereObj->setTransformation(tc);

                scene->addObject(sphereObj);
                printf("Vlozena kulicka na pozici: [%.2f, %.2f, %.2f]\n", pos.x, pos.y + 0.2f, pos.z);
            }
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
        xKeyPressed = false;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!leftMousePressed) {
            leftMousePressed = true;

            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            GLint x = (GLint)mouseX;
            GLint y = (GLint)mouseY;
            GLint newy = (GLint)camera->getResolution().y - y;

            if (modes[modeIndex] == ControlMode::INFO) {
                GLubyte color[4] = {};
                GLfloat depth = 1.0f;
                GLuint index = 0;

                glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
                glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
                glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

                printf("Clicked on pixel %d, %d, color %02x%02x%02x%02x, depth %f, stencil index %u\n",
                    x, newy, color[0], color[1], color[2], color[3], depth, index);

                if (camera != nullptr) {
                    glm::vec3 screenX = glm::vec3(x, newy, depth);
                    glm::mat4 view = camera->getViewMatrix();
                    glm::mat4 projection = camera->getProjectionMatrix();
                    glm::vec4 viewPort = glm::vec4(0, 0, camera->getResolution().x, camera->getResolution().y);

                    glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
                    printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
                }
            }
            else if (modes[modeIndex] == ControlMode::INSERT_POINTS) {
                GLfloat depth = 1.0f;
                glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

                if (depth < 1.0f && camera != nullptr) {
                    glm::vec3 screenCoord = glm::vec3(x, newy, depth);
                    glm::mat4 view = camera->getViewMatrix();
                    glm::mat4 projection = camera->getProjectionMatrix();
                    glm::vec4 viewPort = glm::vec4(0, 0, camera->getResolution().x, camera->getResolution().y);

                    glm::vec3 worldPos = glm::unProject(screenCoord, view, projection, viewPort);

                    if (!hasPointA) {
                        pointA = worldPos;
                        hasPointA = true;
                        printf("Bod A: [%.2f, %.2f, %.2f]\n", pointA.x, pointA.y, pointA.z);
                    }
                    else {
                        glm::vec3 pointB = worldPos;
                        hasPointA = false;
                        printf("Bod B: [%.2f, %.2f, %.2f]\n", pointB.x, pointB.y, pointB.z);

                        if (sphereModel == nullptr) {
                            sphereModel = new Model(UVSphereModel, sizeof(UVSphereModel), UVSphereVertexCount, 8);
                            sphereShader = new ShaderProgram("shaders/TextureShader.vert", "shaders/TextureShader.frag");
                            sphereTexture = new Texture("src/textures/smiley.png");
                        }

                        if (registeredCamera != camera) {
                            camera->obs_register(sphereShader);
                            registeredCamera = camera;
                        }

                        int objId = nextSpawnedObjectId++;
                        DrawableObject* movingObj = new DrawableObject(sphereModel, sphereShader, sphereTexture, objId);
                        TransformComposite* tc = new TransformComposite();
                        tc->addTransformation(new LineMovement(pointA, pointB, 0.4f));
                        tc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
                        tc->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0f));
                        movingObj->setTransformation(tc);

                        scene->addObject(movingObj);
                        printf("Vlozen pohybujici se model (ID %d)\n", objId);
                    }
                }
            }
            else if (modes[modeIndex] == ControlMode::DELETE_OBJECT) {
                GLuint stencilId = 0;
                glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &stencilId);

                if (stencilId > 0 && stencilId != 100) {
                    scene->removeObject(stencilId);
                    printf("Smazan objekt ID %u\n", stencilId);
                }
            }
        }
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        leftMousePressed = false;
    }
}
