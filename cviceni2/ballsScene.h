#pragma once
#include "Scene.h"
#include "Models/sphere.h"
class BallsScene : public Scene {
public:
	BallsScene(int w, int h) {
		this->cam = new Camera(glm::vec3(0.0f, 0.0f, 5.0f));
		this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

		Model* ball = new Model(sphere, sizeof(sphere), 17280);

		ShaderProgram* bShader = new ShaderProgram("Shaders/BlinnPhong.vert", "Shaders/BlinnPhong.frag");

		this->addModel(ball);
		this->addShader(bShader);

		DrawableObject* ballObj1 = new DrawableObject(ball, bShader);
		DrawableObject* ballObj2 = new DrawableObject(ball, bShader);
		DrawableObject* ballObj3 = new DrawableObject(ball, bShader);
		DrawableObject* ballObj4 = new DrawableObject(ball, bShader);
			
		TransformComposite* composite1 = new TransformComposite();
		TransformComposite* composite2 = new TransformComposite();
		TransformComposite* composite3 = new TransformComposite();
		TransformComposite* composite4 = new TransformComposite();

		composite1->addTransformation(new Translate(-3.0f, 0.0f, 0.0f));
		composite2->addTransformation(new Translate(3.0f, 0.0f, 0.0f));
		composite3->addTransformation(new Translate(0.0f, 3.0f, 0.0f));
		composite4->addTransformation(new Translate(0.0f, -3.0f, 0.0f));

		ballObj1->setTransformation(composite1);
		ballObj2->setTransformation(composite2);
		ballObj3->setTransformation(composite3);
		ballObj4->setTransformation(composite4);

		this->addObject(ballObj1);
		this->addObject(ballObj2);
		this->addObject(ballObj3);
		this->addObject(ballObj4);

		


	}
};