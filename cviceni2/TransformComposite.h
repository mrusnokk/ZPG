#pragma once
#include "Transformation.h"
#include <vector>

class TransformComposite : public Transformation {
private:
    std::vector<Transformation*> children;

public:
    void addTransformation(Transformation* t) {
        children.push_back(t);
    }

    glm::mat4 getMatrix() override {
        glm::mat4 result = glm::mat4(1.0f);
        for (Transformation* t : children) {
            result *= t->getMatrix();
        }
        return result;
    }
};