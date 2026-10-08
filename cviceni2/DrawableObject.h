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
#include <vector>

class DrawableObject {
	Model* model;
	ShaderProgram* shader;
	std::vector<Transformation*> transformations;

public:
	DrawableObject(Model* m, ShaderProgram* s);
	
	void addTransformation(Transformation* t);
	void draw();
};