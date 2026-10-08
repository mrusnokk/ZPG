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
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject {
	Model* model;
	ShaderProgram* shader;
	Transformation transform;

public:
	DrawableObject(Model* m, ShaderProgram* s);

	void setPosition(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float angle, float axisX, float axisY, float axisZ);
	
	void draw();
};