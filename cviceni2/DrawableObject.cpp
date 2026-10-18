#include "DrawableObject.h"
#include <iostream>
DrawableObject::DrawableObject(Model* m, ShaderProgram* s){
	this->model = m;
	this->shader = s;
	transform = nullptr;
}

void DrawableObject::setTransformation(Transformation* t) {
	this->transform = t;
}

void DrawableObject::draw() {
	shader->use();
	if (transform != nullptr) {
		shader->setMatrix("modelMatrix", transform->getMatrix());
	}
	model->draw();
}