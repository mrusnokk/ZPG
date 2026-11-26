#include "core/Controller.h"
#include "models/uv_sphere.h"
#include "models/sphere.h"
#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Texture.h"
#include "rendering/DrawableObject.h"
#include "transform/TransformComposite.h"
#include "transform/Translate.h"
#include "transform/Rotate.h"
#include "transform/Scale.h"
#include "transform/LineMovement.h"
#include "transform/CubicMovement.h"
#include "transform/BezierSplineMovement.h"
#include <cstdio>

Controller::Controller() {}

Controller::~Controller() {
    if (registeredCamera != nullptr) {
        if (sphereShader != nullptr) {
            registeredCamera->obs_remove(sphereShader);
        }
        if (pointShader != nullptr) {
            registeredCamera->obs_remove(pointShader);
        }
        registeredCamera = nullptr;
    }
    delete sphereModel;
    delete sphereShader;
    delete sphereTexture;
    delete pointModel;
    delete pointShader;
}

void Controller::syncCamera(Camera* camera) {
    if (camera == nullptr) return;
    if (registeredCamera != camera) {
        if (registeredCamera != nullptr) {
            if (sphereShader != nullptr) registeredCamera->obs_remove(sphereShader);
            if (pointShader != nullptr) registeredCamera->obs_remove(pointShader);
        }
        registeredCamera = camera;
        if (sphereShader != nullptr) camera->obs_register(sphereShader);
        if (pointShader != nullptr) camera->obs_register(pointShader);
    }
}

bool Controller::unprojectPixel(GLint x, GLint newy, Camera* camera, glm::vec3& outWorldPos) {
    if (camera == nullptr) return false;
    GLfloat depth = 1.0f;
    glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    if (depth >= 1.0f) return false;

    glm::vec3 screenCoord(x, newy, depth);
    glm::vec4 viewPort(0, 0, camera->getResolution().x, camera->getResolution().y);
    outWorldPos = glm::unProject(screenCoord, camera->getViewMatrix(), camera->getProjectionMatrix(), viewPort);
    return true;
}

void Controller::ensureSphereResources(Camera* camera) {
    if (sphereModel == nullptr) {
        sphereModel = new Model(UVSphereModel, sizeof(UVSphereModel), UVSphereVertexCount, 8);
        sphereShader = new ShaderProgram("shaders/TextureShader.vert", "shaders/TextureShader.frag");
        sphereTexture = new Texture("src/textures/smiley.png");
        if (camera != nullptr) camera->obs_register(sphereShader);
    }
}

void Controller::spawnControlPoint(Scene* scene, Camera* camera, const glm::vec3& pos) {
    if (pointModel == nullptr) {
        pointModel = new Model(sphere, sizeof(sphere), 2880, 6);
        pointShader = new ShaderProgram("shaders/basic.vert", "shaders/lightRed.frag");
        if (camera != nullptr) camera->obs_register(pointShader);
    }

    DrawableObject* pointObj = new DrawableObject(pointModel, pointShader);
    TransformComposite* pointTc = new TransformComposite();
    pointTc->addTransformation(new Translate(pos.x, pos.y, pos.z));
    pointTc->addTransformation(new Scale(0.05f, 0.05f, 0.05f));
    pointObj->setTransformation(pointTc);
    scene->addObject(pointObj);
}

int Controller::spawnSmiley(Scene* scene, Camera* camera, Transformation* movement) {
    ensureSphereResources(camera);
    int objId = nextSpawnedObjectId++;
    DrawableObject* obj = new DrawableObject(sphereModel, sphereShader, sphereTexture, objId);
    TransformComposite* tc = new TransformComposite();
    tc->addTransformation(movement);
    tc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    tc->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0f));
    obj->setTransformation(tc);
    scene->addObject(obj);
    return objId;
}

void Controller::spawnSpline(Scene* scene, Camera* camera) {
    if (splinePoints.size() < 4) return;
    int objId = spawnSmiley(scene, camera, new BezierSplineMovement(splinePoints, 0.4f, true));
    printf("Vytvorena Bezierova spline krivka (%zu bodu, %zu segmentu) s modelem (ID %d)\n",
        splinePoints.size(), (splinePoints.size() - 1) / 3, objId);
    splinePoints.clear();
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
    syncCamera(camera);

    processInput(window, camera);

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if (!fKeyPressed) {
            fKeyPressed = true;
            scene->toggleFlashlight();
            printf("Baterka: %s\n", scene->isFlashlightOn() ? "ZAPNUTA" : "VYPNUTA");
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
        fKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (!qKeyPressed) {
            qKeyPressed = true;
            modeIndex = (modeIndex + 1) % 5;
            hasPointA = false;
            hasPointB = false;
            hasPointC = false;
            splinePoints.clear();

            if (modes[modeIndex] == ControlMode::INFO)
                printf("Mod: INFO\n");
            else if (modes[modeIndex] == ControlMode::INSERT_POINTS)
                printf("Mod: VKLADANI\n");
            else if (modes[modeIndex] == ControlMode::INSERT_CUBIC)
                printf("Mod: VLOZENI Kubiky\n");
            else if (modes[modeIndex] == ControlMode::INSERT_SPLINE)
                printf("Mod: VLOZENI BEZIEROVY SPLINE KRIVKY (Entrem ukoncite vkladani bodu!)\n");
            else if (modes[modeIndex] == ControlMode::DELETE_OBJECT)
                printf("Mod: MAZANI\n");
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
        qKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        if (!enterKeyPressed) {
            enterKeyPressed = true;
            if (modes[modeIndex] == ControlMode::INSERT_SPLINE) {
                if (splinePoints.size() < 4) {
                    printf("Nedostatek bodu (%zu). Pro prvni segment chybi jeste %zu bod(y).\n",
                        splinePoints.size(), 4 - splinePoints.size());
                }
                else if ((splinePoints.size() - 1) % 3 != 0) {
                    size_t missing = 3 - ((splinePoints.size() - 1) % 3);
                    printf("Nedokonceny segment (%zu bodu). Doklikejte jeste %zu bod(y) pro dokonceni segmentu.\n",
                        splinePoints.size(), missing);
                }
                else {
                    spawnSpline(scene, camera);
                }
            }
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE) {
        enterKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        if (!xKeyPressed) {
            xKeyPressed = true;

            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            GLint x = (GLint)mouseX;
            GLint newy = (GLint)camera->getResolution().y - (GLint)mouseY;
            glm::vec3 pos;

            if (unprojectPixel(x, newy, camera, pos)) {
                spawnSmiley(scene, camera, new Translate(pos.x, pos.y + 0.2f, pos.z));
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
            GLint newy = (GLint)camera->getResolution().y - (GLint)mouseY;

            GLuint clickedStencil = 0;
            glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &clickedStencil);
            if (clickedStencil > 0) {
                scene->onObjectClick(static_cast<int>(clickedStencil));
            }

            if (modes[modeIndex] == ControlMode::INFO) {
                GLubyte color[4] = {};
                GLfloat depth = 1.0f;
                GLuint index = 0;

                glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
                glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
                glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

                printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
                    x, newy, color[0], color[1], color[2], color[3], depth, index);

                if (camera != nullptr) {
                    glm::vec3 screenX(x, newy, depth);
                    glm::vec4 viewPort(0, 0, camera->getResolution().x, camera->getResolution().y);
                    glm::vec3 pos = glm::unProject(screenX, camera->getViewMatrix(), camera->getProjectionMatrix(), viewPort);
                    printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
                }
            }
            else if (modes[modeIndex] == ControlMode::INSERT_POINTS) {
                glm::vec3 worldPos;
                if (unprojectPixel(x, newy, camera, worldPos)) {
                    if (!hasPointA) {
                        pointA = worldPos;
                        hasPointA = true;
                        printf("Bod A: [%.2f, %.2f, %.2f]\n", pointA.x, pointA.y, pointA.z);
                        pointA.y += 0.2f;
                    }
                    else {
                        glm::vec3 pointB = worldPos;
                        hasPointA = false;
                        printf("Bod B: [%.2f, %.2f, %.2f]\n", pointB.x, pointB.y, pointB.z);
                        pointB.y += 0.2f;

                        int objId = spawnSmiley(scene, camera, new LineMovement(pointA, pointB, 0.4f));
                        printf("Vlozen pohybujici se model (ID %d)\n", objId);
                    }
                }
            }
            else if (modes[modeIndex] == ControlMode::INSERT_CUBIC) {
                glm::vec3 worldPos;
                if (unprojectPixel(x, newy, camera, worldPos)) {
                    if (!hasPointA) {
                        pointA = worldPos;
                        hasPointA = true;
                        printf("Bod A: [%.2f, %.2f, %.2f]\n", pointA.x, pointA.y, pointA.z);
                        pointA.y += 0.2f;
                    }
                    else if (!hasPointB) {
                        pointB = worldPos;
                        hasPointB = true;
                        printf("Bod B: [%.2f, %.2f, %.2f]\n", pointB.x, pointB.y, pointB.z);
                        pointB.y += 0.2f;
                    }
                    else if (!hasPointC) {
                        pointC = worldPos;
                        hasPointC = true;
                        printf("Bod C: [%.2f, %.2f, %.2f]\n", pointC.x, pointC.y, pointC.z);
                        pointC.y += 0.2f;
                    }
                    else {
                        glm::vec3 pointD = worldPos;
                        hasPointA = false;
                        hasPointB = false;
                        hasPointC = false;
                        printf("Bod D: [%.2f, %.2f, %.2f]\n", pointD.x, pointD.y, pointD.z);
                        pointD.y += 0.2f;

                        glm::vec3 controlPoints[4] = { pointA, pointB, pointC, pointD };
                        for (int i = 0; i < 4; i++) {
                            spawnControlPoint(scene, camera, controlPoints[i]);
                        }

                        int objId = spawnSmiley(scene, camera, new CubicMovement(pointA, pointB, pointC, pointD, 0.4f));
                        printf("Vlozen pohybujici se model (ID %d)\n", objId);
                    }
                }
            }
            else if (modes[modeIndex] == ControlMode::INSERT_SPLINE) {
                glm::vec3 worldPos;
                if (unprojectPixel(x, newy, camera, worldPos)) {
                    worldPos.y += 0.2f;
                    splinePoints.push_back(worldPos);
                    spawnControlPoint(scene, camera, worldPos);

                    printf("Spline bod c. %zu: [%.2f, %.2f, %.2f]\n", splinePoints.size(), worldPos.x, worldPos.y, worldPos.z);

                    if (splinePoints.size() == 4) {
                        printf("Segment 1 dokoncen (4 body). Dalsi segment potrebuje dalsi 3 body, nebo stisknete ENTER pro dokonceni.\n");
                    }
                    else if (splinePoints.size() >= 7 && (splinePoints.size() - 1) % 3 == 0) {
                        size_t segNum = (splinePoints.size() - 1) / 3;
                        printf("Segment %zu dokoncen (%zu bodu). Dalsi segment potrebuje 3 body, nebo stisknete ENTER pro dokonceni.\n", segNum, splinePoints.size());
                    }
                }
            }
            else if (modes[modeIndex] == ControlMode::DELETE_OBJECT) {
                if (clickedStencil > 0 && clickedStencil != 100) {
                    scene->removeObject(clickedStencil);
                    printf("Smazan objekt ID %u\n", clickedStencil);
                }
            }
        }
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        leftMousePressed = false;
    }
}
