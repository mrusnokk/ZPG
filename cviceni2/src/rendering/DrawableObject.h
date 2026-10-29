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

class DrawableObject {
	Model* model;
	ShaderProgram* shader;
	Transformation* transform;

public:
	DrawableObject(Model* m, ShaderProgram* s);
	~DrawableObject() {
		delete transform;
	}
	void setTransformation(Transformation* t);
	void draw();
};