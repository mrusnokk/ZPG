#pragma once
#include "scenes/Scene.h"
#include "models/sphere.h"
#include "models/rus0130.h"
class BallsScene : public Scene {
public:
	BallsScene(int w, int h) {
		this->cam = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
		this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

		Model* ball = new Model(sphere, sizeof(sphere), 17280);
		Model* loginModel = new Model(login_model, sizeof(login_model), 6996);

		ShaderProgram* basic = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
		ShaderProgram* b1Shader = new ShaderProgram("Shaders/phongLight.vert", "Shaders/phongLight.frag");
		ShaderProgram* b2Shader = new ShaderProgram("Shaders/phongLight.vert", "Shaders/phongLight.frag");
		ShaderProgram* b3Shader = new ShaderProgram("Shaders/phongLight.vert", "Shaders/phongLight.frag");
		ShaderProgram* b4Shader = new ShaderProgram("Shaders/phongLight.vert", "Shaders/phongLight.frag");


		this->addModel(ball);
		this->addModel(loginModel);
		this->addShader(basic);
		this->addShader(b1Shader);
		this->addShader(b2Shader);
		this->addShader(b3Shader);
		this->addShader(b4Shader);

		DrawableObject* loginObj = new DrawableObject(loginModel, basic);
		DrawableObject* ballObj1 = new DrawableObject(ball, b1Shader);
		DrawableObject* ballObj2 = new DrawableObject(ball, b2Shader);
		DrawableObject* ballObj3 = new DrawableObject(ball, b3Shader);
		DrawableObject* ballObj4 = new DrawableObject(ball, b4Shader);

		TransformComposite* composite1 = new TransformComposite();
		TransformComposite* composite2 = new TransformComposite();
		TransformComposite* composite3 = new TransformComposite();
		TransformComposite* composite4 = new TransformComposite();

		composite1->addTransformation(new Translate(-3.0f, 0.0f, 0.0f));
		//composite1->addTransformation(new Scale(1.5f, 0.5f, 1.0f));
		composite2->addTransformation(new Translate(3.0f, 0.0f, 0.0f));
		//composite2->addTransformation(new Scale(1.5f, 0.5f, 1.0f));
		composite3->addTransformation(new Translate(0.0f, 3.0f, 0.0f));
		//composite3->addTransformation(new Scale(1.5f, 0.5f, 1.0f));
		composite4->addTransformation(new Translate(0.0f, -3.0f, 0.0f));
		//composite4->addTransformation(new Scale(1.5f, 0.5f, 1.0f));

		ballObj1->setTransformation(composite1);
		ballObj2->setTransformation(composite2);
		ballObj3->setTransformation(composite3);
		ballObj4->setTransformation(composite4);

		this->addObject(loginObj);
		this->addObject(ballObj1);
		this->addObject(ballObj2);
		this->addObject(ballObj3);
		this->addObject(ballObj4);
	}
};