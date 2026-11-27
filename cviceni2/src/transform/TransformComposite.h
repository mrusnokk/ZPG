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
    ~TransformComposite() override;
    void addTransformation(Transformation* t);
    glm::mat4 getMatrix() override;
};
