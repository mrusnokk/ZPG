#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* m, ShaderProgram* s){
	this->model = model;
	this->shader = shader;
}
void DrawableObject::setPosition(float x, float y, float z) {
	transform.setPosition(x, y, z);
}
void DrawableObject::setScale(float x, float y, float z) {
	transform.setScale(x, y, z);
}

void DrawableObject::setRoation(float angle, float axisX, float axisY, float axisZ ) {
	transform.setRotation(angle, axisX, axisY, axisZ);
}
void DrawableObject::draw() {
	shader->use();
	glm::mat4 matrix = transform.getMatrix();
	GLint modelLoc = glGetUniformLocation(shader->id, "modelMatrix");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &matrix[0][0]);
	model->draw();
}