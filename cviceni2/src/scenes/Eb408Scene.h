/**
 * @file Eb408Scene.h
 * @brief Scene class representing classroom EB408 with desks, chairs, whiteboard, and multiple light sources.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "scenes/Scene.h"

class Eb408Scene : public Scene {
public:
	Eb408Scene(int w, int h, int lightCount = 12);
};
