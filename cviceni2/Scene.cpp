#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {
	for (DrawableObject* obj : objects)
	{
		delete obj;
	}
	for (Model* model : models)
	{
		delete model;
	}
	for (ShaderProgram* shader : shaders)
	{ 
		delete shader;
	}
	delete cam;
	delete light;
}

void Scene::addObject(DrawableObject* object) 
{ 
	objects.push_back(object);
}
void Scene::addModel(Model* model)
{
	models.push_back(model);
}
void Scene::addShader(ShaderProgram* shader) 
{ 
	shaders.push_back(shader);
	if (this->cam != nullptr) {
		this->cam->obs_register(shader);
	}
	if(this->light != nullptr) {
		this->light->registerObserver(shader);
	}
}

void Scene::draw() {
	for (DrawableObject* obj : objects) {
		obj->draw();
	}
}
Camera* Scene::getCam() {
	return this->cam;
}