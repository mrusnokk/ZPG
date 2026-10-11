/**@file SolarScene.h
 * @brief Class representing a 3D solar system scene.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "Scene.h"
#include "sun.h"
#include "moon.h"
#include "earth.h"
#include <iostream>

class SolarScene : public Scene {
private:
	Rotate* rEarth;
	Rotate* rMoon;
	Rotate* rDayCycleEarth;
	Rotate* rDayCycleMoon;

	float earthAngle = 0.0f;
	float moonAngle = 0.0f;
	float earthDayCycleAngle = 0.0f;
	float moonDayCycleAngle = 0.0f;

public:
	SolarScene() {
		ShaderProgram* shader = new ShaderProgram("Shaders/color.vert", "Shaders/color.frag");
		this->addShader(shader);

		Model* sunModel = new Model(sun, sizeof(sun), 11520, 9);
		Model* moonModel = new Model(moon, sizeof(moon), 11520, 9);
		Model* earthModel = new Model(earth, sizeof(earth), 11520, 9);

		this->addModel(sunModel);
		this->addModel(moonModel);
		this->addModel(earthModel);

		DrawableObject* sunOb = new DrawableObject(sunModel, shader);
		TransformComposite* sunTc = new TransformComposite();

		sunTc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
		sunOb->setTransformation(sunTc);
		this->addObject(sunOb);

		TransformComposite* earthOrbit = new TransformComposite();
		this->rEarth = new Rotate(0.0f, 0.0f, 0.0f, 1.0f);
		earthOrbit->addTransformation(this->rEarth);
		earthOrbit->addTransformation(new Translate(0.6f, 0.0, 0.0f));

		DrawableObject* earthOb = new DrawableObject(earthModel, shader);
		TransformComposite* earthTc = new TransformComposite();

		earthTc->addTransformation(earthOrbit);
		this->rDayCycleEarth = new Rotate(0.0f, 0.0f, 0.0f, 1.0f);
		earthTc->addTransformation(this->rDayCycleEarth);
		earthTc->addTransformation(new Scale(0.1f, 0.1f, 0.1f));
		earthOb->setTransformation(earthTc);
		this->addObject(earthOb);

		DrawableObject* moonOb = new DrawableObject(moonModel, shader);
		TransformComposite* moonTc = new TransformComposite();

		moonTc->addTransformation(earthOrbit);
		this->rMoon = new Rotate(0.0f, 0.0f, 0.0f, 1.0f);
		moonTc->addTransformation(this->rMoon);
		moonTc->addTransformation(new Translate(0.15f, 0.0f, 0.0f));
		this->rDayCycleMoon = new Rotate(0.0f, 0.0f, 0.0f, 1.0f);
		moonTc->addTransformation(rDayCycleMoon);
		moonTc->addTransformation(new Scale(0.03f, 0.03f, 0.03f));
		moonOb->setTransformation(moonTc);
		this->addObject(moonOb);

	}
	void update() override {
		earthAngle += 0.025f;
		if (earthAngle >= 360.0f)
			earthAngle -= 360.0f;
		rEarth->setAngle(earthAngle);

		earthDayCycleAngle += 0.03;
		if (earthDayCycleAngle >= 360.0f)
			earthDayCycleAngle -= 360.0f;
		rDayCycleEarth->setAngle(earthDayCycleAngle);

		moonAngle += 0.05f;
		if (moonAngle >= 360.0f)
			moonAngle -= 360.0f;
		rMoon->setAngle(moonAngle);

		moonDayCycleAngle += 0.09;
		if (moonDayCycleAngle >= 360.0f)
			moonDayCycleAngle -= 360.0f;
		rDayCycleMoon->setAngle(moonDayCycleAngle);
	}
};