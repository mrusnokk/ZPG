#pragma once

#include "Scene.h"
#include "sun.h"
#include "moon.h"
#include "earth.h"
#include "Models/cybertruck.h"

class SolarScene : public Scene {
private:
	Rotate* rSystem;
	Rotate* rEarth;
	Rotate* rMoon;
	Rotate* rDayCycleEarth;
	Rotate* rDayCycleMoon;
	Rotate* rCyberTruckOrbit;
	Rotate* rCyberTruckSpin;

	float systemAngle = 0.0f;
	float earthAngle = 0.0f;
	float moonAngle = 0.0f;
	float earthDayCycleAngle = 0.0f;
	float moonDayCycleAngle = 0.0f;
	float cyberTruckOrbitAngle = 0.0f;
	float cyberTruckSpinAngle = 0.0f;

public:
	SolarScene(int w, int h) {
		cam = new Camera(glm::vec3(0.0f, 1.0f, 3.0f));
		cam->setProjection(90, w / static_cast<float>(h), 0.1f, 100.0f);

		ShaderProgram* shader = new ShaderProgram("Shaders/phongLight.vert", "Shaders/phongLight.frag");
		ShaderProgram* shader2 = new ShaderProgram("Shaders/color.vert", "Shaders/color.frag");
		addShader(shader);
		addShader(shader2);

		Model* sunModel = new Model(sun, sizeof(sun), 11520, 9);
		Model* moonModel = new Model(moon, sizeof(moon), 11520, 9);
		Model* earthModel = new Model(earth, sizeof(earth), 11520, 9);
		Model* cyberTruckModel = new Model(cybertruck, sizeof(cybertruck),
			CYBERTRUCK_VERTEX_COUNT, CYBERTRUCK_FLOATS_PER_VERTEX);

		addModel(sunModel);
		addModel(moonModel);
		addModel(earthModel);
		addModel(cyberTruckModel);

		TransformComposite* systemTc = new TransformComposite();
		rSystem = new Rotate(0.0f, 0.0f, 1.0f, 0.0f);
		systemTc->addTransformation(rSystem);
		systemTc->addTransformation(new Scale(2.0f, 2.0f, 2.0f));

		DrawableObject* sunOb = new DrawableObject(sunModel, shader2);
		TransformComposite* sunTc = new TransformComposite();
		sunTc->addTransformation(systemTc);
		sunOb->setTransformation(sunTc);
		addObject(sunOb);

		TransformComposite* earthOrbit = new TransformComposite();
		rEarth = new Rotate(0.0f, 0.0f, 1.0f, 0.0f);
		earthOrbit->addTransformation(rEarth);
		earthOrbit->addTransformation(new Translate(5.0f, 0.0f, 0.0f));

		DrawableObject* earthOb = new DrawableObject(earthModel, shader);
		TransformComposite* earthTc = new TransformComposite();
		earthTc->addTransformation(systemTc);
		earthTc->addTransformation(earthOrbit);
		rDayCycleEarth = new Rotate(0.0f, 0.0f, 1.0f, 0.0f);
		earthTc->addTransformation(rDayCycleEarth);
		earthTc->addTransformation(new Scale(1.0f, 1.0f, 1.0f));
		earthOb->setTransformation(earthTc);
		addObject(earthOb);

		DrawableObject* moonOb = new DrawableObject(moonModel, shader);
		TransformComposite* moonTc = new TransformComposite();
		moonTc->addTransformation(systemTc);
		moonTc->addTransformation(earthOrbit);
		rMoon = new Rotate(0.0f, 0.0f, 1.0f, 0.0f);
		moonTc->addTransformation(rMoon);
		moonTc->addTransformation(new Translate(2.0f, 0.0f, 0.0f));
		rDayCycleMoon = new Rotate(0.0f, 0.0f, 1.0f, 0.0f);
		moonTc->addTransformation(rDayCycleMoon);
		moonTc->addTransformation(new Scale(0.5f, 0.5f, 0.5f));
		moonOb->setTransformation(moonTc);
		addObject(moonOb);

		DrawableObject* cyberTruckOb = new DrawableObject(cyberTruckModel, shader);
		TransformComposite* cbTruckTc = new TransformComposite();
		cbTruckTc->addTransformation(systemTc);
		rCyberTruckOrbit = new Rotate(0.0f, 0.0f, 1.0f, 0.0f);
		cbTruckTc->addTransformation(rCyberTruckOrbit);
		cbTruckTc->addTransformation(new Translate(3.0f, 0.0f, 0.0f));
		rCyberTruckSpin = new Rotate(0.0f, 0.0f, 0.0f, 1.0f);
		cbTruckTc->addTransformation(rCyberTruckSpin);
		cbTruckTc->addTransformation(new Scale(0.1f, 0.1f, 0.1f));
		cyberTruckOb->setTransformation(cbTruckTc);
		addObject(cyberTruckOb);
	}

	void update() override {
		auto advance = [](float& angle, float step) {
			angle += step;
			if (angle >= 360.0f)
				angle -= 360.0f;
			};

		advance(systemAngle, 0.01f);
		rSystem->setAngle(systemAngle);

		advance(earthAngle, 0.025f);
		rEarth->setAngle(earthAngle);

		advance(earthDayCycleAngle, 0.03f);
		rDayCycleEarth->setAngle(earthDayCycleAngle);

		advance(moonAngle, 0.05f);
		rMoon->setAngle(moonAngle);

		advance(moonDayCycleAngle, 0.09f);
		rDayCycleMoon->setAngle(moonDayCycleAngle);

		advance(cyberTruckOrbitAngle, 0.02f);
		rCyberTruckOrbit->setAngle(cyberTruckOrbitAngle);

		advance(cyberTruckSpinAngle, 0.005f);
		rCyberTruckSpin->setAngle(cyberTruckSpinAngle);
	}
};