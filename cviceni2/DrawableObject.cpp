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

void DrawableObject::draw(Camera* cam) {
	shader->use();
	//glm::mat4 currentMatrix = this->transform->getMatrix();
	if (transform != nullptr) {
		shader->setMatrix("modelMatrix", transform->getMatrix());
	}
	if (cam != nullptr) {
		shader->setMatrix("viewMatrix", cam->getViewMatrix());
		shader->setMatrix("projectionMatrix", cam->getProjectionMatrix());
	}
	model->draw();
}