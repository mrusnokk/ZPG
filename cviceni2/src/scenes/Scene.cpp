#include "scenes/Scene.h"

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
	delete skybox;
}

void Scene::addObject(DrawableObject* object) 
{ 
	objects.push_back(object);
}

bool Scene::removeObject(int id)
{
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		if ((*it)->getId() == id) {
			delete *it;
			objects.erase(it);
			return true;
		}
	}
	return false;
}

DrawableObject* Scene::getObject(int id)
{
	for (DrawableObject* obj : objects) {
		if (obj->getId() == id) {
			return obj;
		}
	}
	return nullptr;
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
	
	if (skybox != nullptr) {
		skybox->draw();
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	for (DrawableObject* obj : objects) {
		glStencilFunc(GL_ALWAYS, obj->getId(), 0xFF);
		obj->draw();
	}
}
Camera* Scene::getCam() {
	return this->cam;
}

void Scene::setSkybox(Skybox* s) {
	this->skybox = s;
	if (this->cam != nullptr) {
		this->cam->obs_register(s->getShader());
	}
}
void Scene::addObject() {

}
