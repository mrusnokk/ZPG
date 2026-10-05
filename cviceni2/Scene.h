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

#include "DrawableObject.h"

class Scene {
private:
	std::vector<DrawableObject*> objects;
public:
	void addObject(DrawableObject* object);
	void draw();

};