#pragma once
#include "Scene.h"
#include "models/eb408.h"
#include "models/door.h"

class Eb408Scene : public Scene {
public:
	Eb408Scene(int w, int h) {
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

		Model* eb408 = new Model(EB408Model, sizeof(EB408Model), EB408VertexCount, 8);
		Model* ebDoor = new Model(DoorModel, sizeof(DoorModel), DoorVertexCount, 8);

		ShaderProgram* ebShader = new ShaderProgram("Shaders/TextureShader.vert","Shaders/TextureShader.frag");

		Texture* ebTexture = new Texture("src/textures/T_EB408.png");
		Texture* doorTexture = new Texture("src/textures/door.png");

		DrawableObject* ebObject = new DrawableObject(eb408,ebShader,ebTexture);
		DrawableObject* doorObject = new DrawableObject(ebDoor, ebShader, doorTexture);

		TransformComposite* ebTc = new TransformComposite();
		TransformComposite* doorTc = new TransformComposite();

		
		this->addModel(eb408);
		this->addModel(ebDoor);

		this->addShader(ebShader);

		ebTc->addTransformation(new Translate(0.0f, 0.0f, 0.0f));
		doorTc->addTransformation(new Translate(-2.415f, 0.0f, 7.75f));
		doorTc->addTransformation(new Scale(0.0105f, 0.0105f, 0.0105f));

		ebObject->setTransformation(ebTc);
		doorObject->setTransformation(doorTc);

		this->addObject(ebObject);
		this->addObject(doorObject);
	}
};