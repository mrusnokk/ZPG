/**
 * @file Scene.h
 *
 * @brief Class for managing and rendering a collection of drawable objects.
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once
#include <vector>
#include "rendering/DrawableObject.h"
#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"
#include "transform/TransformComposite.h"
#include "transform/Translate.h"
#include "transform/Rotate.h"
#include "transform/Scale.h"
#include "camera/Camera.h"
#include "lighting/Light.h"

class Scene {
private:
	std::vector<DrawableObject*> objects;
	std::vector<Model*> models;
	std::vector<ShaderProgram*> shaders;
protected:
	Camera* cam = nullptr;
	Light* light = nullptr;

public:
	Scene();
	~Scene();
	void addObject(DrawableObject* object);
	void addModel(Model* model);
	void addShader(ShaderProgram* shader);
	void setLight(Light* light) { this->light = light; }	
	virtual void update() {}
	virtual void draw();
	Camera* getCam();
};