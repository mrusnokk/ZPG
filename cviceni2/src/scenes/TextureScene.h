#pragma once
#include "scenes/Scene.h"
#include "models/tplain.h"
#include "models/rus0130.h"
#include "models/shrek.h"
class TextureScene : public Scene {
public:
	TextureScene(int w, int h) {
		this->cam = new Camera(glm::vec3(0.0f, 1.0f, 1.0f));
		this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

		this->light = new Light(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

		std::vector<std::string> faces = {
			"src/textures/cubemap/posx.jpg",
			"src/textures/cubemap/negx.jpg",
			"src/textures/cubemap/posy.jpg",
			"src/textures/cubemap/negy.jpg",
			"src/textures/cubemap/posz.jpg",
			"src/textures/cubemap/negz.jpg"
		};
		this->setSkybox(new Skybox(faces));

		Model* plainModel = new Model(tplain,sizeof(tplain),6,8);
		Model* shrekModel = new Model(ShrekModel, sizeof(ShrekModel), ShrekVertexCount, 8);

		ShaderProgram* tShader = new ShaderProgram("shaders/TextureShader.vert", "shaders/TextureShader.frag");

		Texture* plainTexture = new Texture("src/textures/grass.jpg");
		Texture* shrekTexture = new Texture("src/textures/shrek.png");

		DrawableObject* plain = new DrawableObject(plainModel, tShader, plainTexture);
		DrawableObject* shrekObject = new DrawableObject(shrekModel, tShader, shrekTexture);

		TransformComposite* tc = new TransformComposite();
		tc->addTransformation(new Translate(0.0f, 0.0f, 0.0f));

		TransformComposite* sTc = new TransformComposite();
		sTc->addTransformation(new Translate(0.0f, 0.0f, 0.0f));
		sTc->addTransformation(new Rotate(90.0f, 1.0f, 0.0f, 0.0f));

		plain->setTransformation(tc);
		shrekObject->setTransformation(sTc);

		this->addModel(plainModel);
		this->addModel(shrekModel);
		
		this->addShader(tShader);

		this->addObject(plain);
		this->addObject(shrekObject);

	}	
};