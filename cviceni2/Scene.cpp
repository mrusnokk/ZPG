#include "Scene.h"


void Scene::addObject(DrawableObject* obj) {
	objects.push_back(obj);
}

void Scene::draw() {
	for (DrawableObject* obj : objects) {
		obj->draw();
	}
}