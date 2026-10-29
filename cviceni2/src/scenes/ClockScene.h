#pragma once
#include "scenes/Scene.h"
#include "models/clock.h"
#include <ctime>
#include <numbers>

class ClockScene : public Scene {
private:
	ShaderProgram* shader;
public:
	ClockScene() {
		this->cam = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		this->cam->setProjection(60.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);

		Model* m = new Model(clockModel, sizeof(clockModel), 44826, 9);
		this->addModel(m);
		shader = new ShaderProgram("Shaders/clockShader.vert", "Shaders/clockShader.frag");
		this->addShader(shader);
		DrawableObject* hod = new DrawableObject(m, shader);

		TransformComposite* tc = new TransformComposite();
		tc->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
		tc->addTransformation(new Scale(-1.0f, 1.0f, 1.0f));
		hod->setTransformation(tc);

		this->addObject(hod);
	}

	void update() override {
		std::time_t t = std::time(nullptr);
		std::tm lt;
		localtime_s(&lt, &t);

		const float TWO_PI = std::numbers::pi * 2;
		float seconds = static_cast<float>(lt.tm_sec);
		float minutes = lt.tm_min + seconds / 60.0f;
		float hours = (lt.tm_hour % 12) + minutes / 60.0f;

		shader->use();
		shader->setUniform("secondAngle", -(seconds / 60.0f * TWO_PI));
		shader->setUniform("minuteAngle", -(minutes / 60.0f * TWO_PI));
		shader->setUniform("hourAngle", -(hours / 12.0f * TWO_PI));
	}
};