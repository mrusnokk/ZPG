#pragma once
#include "Scene.h"
#include "clock.h"
#include "Camera.h"

class ClockScene : public Scene {
private:
	Camera* camera;
public:
		ClockScene() {
		this->camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
		this->camera->setProjection(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		Model* m = new Model(clockModel, 44826, 9);
		ShaderProgram* s = new ShaderProgram("Shaders/color.vert", "Shaders/color.frag");
		DrawableObject* hod = new DrawableObject(m, s);

		TransformComposite* tc = new TransformComposite();

		//tc->addTransformation(new Translate(1.0f, 0.0f, 0.0f));
		tc->addTransformation(new Rotate(90.0f, 1.0f, 0.0f, 0.0f));
		tc->addTransformation(new Scale(0.5f, 0.5f, 0.5f));

		hod->setTransformation(tc);

		this->addModel(m);
		this->addShader(s);
		this->addObject(hod);

	}
};