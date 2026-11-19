#include "rendering/DrawableObject.h"
#include <iostream>

DrawableObject::DrawableObject(Model* m, ShaderProgram* s, Texture* t, int id) {
	this->model = m;
	this->shader = s;
	this->texture = t;
	this->material = nullptr;
	this->transform = nullptr;
	this->id = id;
}

DrawableObject::DrawableObject(Model* m, ShaderProgram* s, int id) {
	this->model = m;
	this->shader = s;
	this->texture = nullptr;
	this->material = nullptr;
	this->transform = nullptr;
	this->id = id;
}

DrawableObject::DrawableObject(Model* m, ShaderProgram* s, Material* mat, int id) {
	this->model = m;
	this->shader = s;
	this->texture = nullptr;
	this->material = mat;
	this->transform = nullptr;
	this->id = id;
}

DrawableObject::DrawableObject(Model* m, ShaderProgram* s, Material* mat, Texture* t, int id) {
	this->model = m;
	this->shader = s;
	this->texture = t;
	this->material = mat;
	this->transform = nullptr;
	this->id = id;
}

DrawableObject::~DrawableObject() {
	if (this->transform != nullptr) {
		this->transform->release();
		this->transform = nullptr;
	}
}

void DrawableObject::setTransformation(Transformation* t) {
	if (this->transform != t) {
		if (this->transform != nullptr) {
			this->transform->release();
		}
		this->transform = t;
		if (this->transform != nullptr) {
			this->transform->addRef();
		}
	}
}

void DrawableObject::setTexture(Texture* tex) {
	this->texture = tex;
}

void DrawableObject::setMaterial(Material* mat) {
	this->material = mat;
}

Material* DrawableObject::getMaterial() const {
	return this->material;
}

void DrawableObject::draw() {
	shader->use();
	if (transform != nullptr) {
		shader->setMatrix("modelMatrix", transform->getMatrix());
	}
	shader->setMaterial(this->material);
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
