#include "DrawableObject.h"
#include <iostream>
DrawableObject::DrawableObject(Model* m, ShaderProgram* s){
	this->model = m;
	this->shader = s;
}
void DrawableObject::setPosition(float x, float y, float z) {
	transform.setPosition(x, y, z);
}
void DrawableObject::setScale(float x, float y, float z) {
	transform.setScale(x, y, z);
}

void DrawableObject::setRotation(float angle, float axisX, float axisY, float axisZ ) {
	transform.setRotation(angle, axisX, axisY, axisZ);
}
void DrawableObject::draw() {
	shader->use();
	shader->setMatrix("modelMatrix", transform.getMatrix());
	model->draw();
}