/**
 * @file DrawableObject.h
 *
 * @brief Class encapsulating a 3D model, its shader program, and spatial transformations.
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once
#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"
#include "transform/Transformation.h"
#include "camera/Camera.h"
#include "rendering/Texture.h"

class DrawableObject {
	int id;
	Model* model;
	ShaderProgram* shader;
	Texture* texture;
	Transformation* transform;
	
public:
	DrawableObject(Model* m, ShaderProgram* s, Texture* t = nullptr,int id = NULL);
	~DrawableObject() {
		delete transform;
	}
	void setTexture(Texture* tex);
	void setTransformation(Transformation* t);
	void draw();
	int getId() { return id; }
};