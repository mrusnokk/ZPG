#include "DrawableObject.h"
#include <iostream>
DrawableObject::DrawableObject(Model* m, ShaderProgram* s){
	this->model = m;
	this->shader = s;
}

void DrawableObject::addTransformation(const Transformation& t) {
	transformations.push_back(t);
}

void DrawableObject::draw() {
	shader->use();

	glm::mat4 m(1.0f);
	for (Transformation& t : transformations) {
		m = m * t.getMatrix();
	}
	shader->setMatrix("modelMatrix", m);
	model->draw();
}