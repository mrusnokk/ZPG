/**
 * @file ClockScene.h
 * @brief Scene class rendering a real-time analog clock.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "scenes/Scene.h"

class ClockScene : public Scene {
private:
	ShaderProgram* shader;

public:
	ClockScene();
	void update() override;
};
