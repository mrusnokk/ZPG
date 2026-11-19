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
	bool flashlightInLights = false;
	for (auto l : this->lights) {
		if (l == flashlight) flashlightInLights = true;
		delete l;
	}
	if (!flashlightInLights && flashlight != nullptr) {
		delete flashlight;
	}
	lights.clear();
	flashlight = nullptr;

	for (Texture* texture : textures)
	{
		delete texture;
	}
	for (Material* material : materials)
	{
		delete material;
	}
	delete cam;
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
	if (!this->lights.empty()) {
		for (auto l : this->lights) {
			l->registerObserver(shader);
		}
		if (shader->hasUniform("numberOfLights")) {
			shader->use();
			shader->setUniform("numberOfLights", static_cast<int>(this->lights.size()));
		}
	}
}

void Scene::addLight(Light* light) {
	this->lights.push_back(light);
	for (ShaderProgram* shader : shaders) {
		light->registerObserver(shader);
		if (shader->hasUniform("numberOfLights")) {
			shader->use();
			shader->setUniform("numberOfLights", static_cast<int>(this->lights.size()));
		}
	}
}

void Scene::addTexture(Texture* texture) {
	if (texture == nullptr) return;
	for (Texture* t : textures) {
		if (t == texture) return;
	}
	textures.push_back(texture);
}

void Scene::addMaterial(Material* material) {
	if (material == nullptr) return;
	for (Material* m : materials) {
		if (m == material) return;
	}
	materials.push_back(material);
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

Flashlight* Scene::getOrCreateFlashlight() {
	if (this->flashlight == nullptr && this->cam != nullptr) {
		int idx = static_cast<int>(this->lights.size());
		this->flashlight = new Flashlight(idx, this->cam, glm::vec3(1.0f, 1.0f, 0.9f), 3.0f, 12.0f, 18.0f);
		this->addLight(this->flashlight);
	}
	return this->flashlight;
}

void Scene::toggleFlashlight() {
	if (this->flashlight == nullptr) {
		getOrCreateFlashlight();
	}
	else {
		this->flashlight->toggle();
	}
}

bool Scene::isFlashlightOn() const {
	return this->flashlight != nullptr && this->flashlight->isEnabled();
}

Flashlight* Scene::getFlashlight() const {
	return this->flashlight;
}

void Scene::setFlashlight(Flashlight* fl) {
	this->flashlight = fl;
}
