/**
 * @file SolarScene.h
 * @brief Scene class simulating a solar system with orbiting planets and a Cybertruck.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "scenes/Scene.h"

class SolarScene : public Scene {
private:
	Rotate* rSun;
	Rotate* rEarth;
	Rotate* rMoon;
	Rotate* rDayCycleEarth;
	Rotate* rDayCycleMoon;
	Rotate* rCyberTruckOrbit;
	Rotate* rCyberTruckSpin;

	float sunAngle = 0.0f;
	float earthAngle = 0.0f;
	float moonAngle = 0.0f;
	float earthDayCycleAngle = 0.0f;
	float moonDayCycleAngle = 0.0f;
	float cyberTruckOrbitAngle = 0.0f;
	float cyberTruckSpinAngle = 0.0f;

public:
	SolarScene(int w, int h);
	void update() override;
};
