/**
 * @file TransformComposite.h
 * @brief Composite implementation for stacking multiple transformations.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "transform/Transformation.h"
#include <vector>

class TransformComposite : public Transformation {
private:
    std::vector<Transformation*> children;

public:
    void addTransformation(Transformation* t) {
        if (t != nullptr) {
            t->addRef();
            children.push_back(t);
        }
    }

    ~TransformComposite() override {
        for (Transformation* t : children) {
            if (t != nullptr) {
                t->release();
            }
        }
    }

    glm::mat4 getMatrix() override {
        glm::mat4 result = glm::mat4(1.0f);
        for (Transformation* t : children) {
            result *= t->getMatrix();
        }
        return result;
    }
};
