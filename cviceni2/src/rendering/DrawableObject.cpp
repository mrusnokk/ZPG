#include "rendering/DrawableObject.h"
#include <iostream>
DrawableObject::DrawableObject(Model* m, ShaderProgram* s, Texture* t) {
	this->model = m;
	this->shader = s;
	this->texture = t;
	transform = nullptr;
}

void DrawableObject::setTransformation(Transformation* t) {
	this->transform = t;
}

void DrawableObject::setTexture(Texture* tex) {
	this->texture = tex;
}

void DrawableObject::draw() {
	shader->use();
	if (transform != nullptr) {
		shader->setMatrix("modelMatrix", transform->getMatrix());
	}
	if (texture != nullptr) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getID());

		GLint texLoc = glGetUniformLocation(shader->getId(), "textureUnitID");
		if (texLoc != -1) {
			glUniform1i(texLoc, 0);
		}
	}

	model->draw();

	if (texture != nullptr) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}