#include "transform/TransformComposite.h"

void TransformComposite::addTransformation(Transformation* t) {
    if (t != nullptr) {
        t->addRef();
        children.push_back(t);
    }
}

TransformComposite::~TransformComposite() {
    for (Transformation* t : children) {
        if (t != nullptr) {
            t->release();
        }
    }
}

glm::mat4 TransformComposite::getMatrix() {
    glm::mat4 result = glm::mat4(1.0f);
    for (Transformation* t : children) {
        result *= t->getMatrix();
    }
    return result;
}
