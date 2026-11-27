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
#include "lighting/Material.h"

class DrawableObject {
	int id;
	Model* model;
	ShaderProgram* shader;
	Texture* texture;
	Material* material;
	Transformation* transform;
	
public:
	DrawableObject(Model* m, ShaderProgram* s, Texture* t = nullptr, int id = 0);
	DrawableObject(Model* m, ShaderProgram* s, int id);
	DrawableObject(Model* m, ShaderProgram* s, Material* mat, int id = 0);
	DrawableObject(Model* m, ShaderProgram* s, Material* mat, Texture* t, int id = 0);
	~DrawableObject();
	void setTexture(Texture* tex);
	void setShader(ShaderProgram* s);
	void setMaterial(Material* mat);
	Material* getMaterial() const;
	void setTransformation(Transformation* t);
	void draw();
	int getId() { return id; }
};
