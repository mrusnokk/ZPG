#pragma once
#include "scenes/Scene.h"
#include "models/tplain.h"
#include "models/rus0130.h"
class TextureScene : public Scene {
public:
	TextureScene(int w, int h) {
		this->cam = new Camera(glm::vec3(0.0f, 1.0f, 1.0f));
		this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

		this->light = new Light(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

		Model* plainModel = new Model(tplain,sizeof(tplain),8);
		ShaderProgram* plainShader = new ShaderProgram("shaders/TextureShader.vert", "shaders/TextureShader.frag");
		Texture* plainTexture = new Texture("src/textures/grass.jpg");
		DrawableObject* plain = new DrawableObject(plainModel, plainShader, plainTexture);

		this->addModel(plainModel);
		this->addShader(plainShader);
		this->addObject(plain);

	}	
};