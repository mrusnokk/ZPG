#pragma once
#include "Scene.h"
#include "models/eb408.h"
#include "models/door.h"
#include "models/Whiteboard.h"
#include "models/chair.h"
#include "models/table.h"

class Eb408Scene : public Scene
{
public:
	Eb408Scene(int w, int h)
	{
		this->cam = new Camera(glm::vec3(0.0f, 1.0f, 1.0f),w,h);
		this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

		this->light = new Light(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

		std::vector<std::string> faces = {
			"src/textures/cubemap/posx.jpg",
			"src/textures/cubemap/negx.jpg",
			"src/textures/cubemap/posy.jpg",
			"src/textures/cubemap/negy.jpg",
			"src/textures/cubemap/posz.jpg",
			"src/textures/cubemap/negz.jpg"};
		this->setSkybox(new Skybox(faces));

		Model *eb408 = new Model(EB408Model, sizeof(EB408Model), EB408VertexCount, 8);
		Model *ebDoor = new Model(DoorModel, sizeof(DoorModel), DoorVertexCount, 8);
		Model *ebWboard = new Model(WhiteboardModel, sizeof(WhiteboardModel), WhiteboardVertexCount, 8);
		Model* ebTable = new Model(TableModel, sizeof(TableModel), TableVertexCount, 8);
		Model* ebChair = new Model(ChairModel, sizeof(ChairModel), ChairVertexCount, 8);

		ShaderProgram *ebShader = new ShaderProgram("Shaders/TextureShader.vert", "Shaders/TextureShader.frag");

		Texture *ebTexture = new Texture("src/textures/T_EB408.png");
		Texture *doorTexture = new Texture("src/textures/door.png");
		Texture *whiteBoardTexture = new Texture("src/textures/texture_zpg.jpeg");
		Texture* tableTexture = new Texture("src/textures/table.png");
		Texture* chairTexure = new Texture("src/textures/chair.png");

		DrawableObject *ebObject = new DrawableObject(eb408, ebShader, ebTexture,100);
		DrawableObject *doorObject = new DrawableObject(ebDoor, ebShader, doorTexture,101);
		DrawableObject *wBoardObject = new DrawableObject(ebWboard, ebShader, whiteBoardTexture,102);

		TransformComposite *ebTc = new TransformComposite();
		TransformComposite *doorTc = new TransformComposite();
		TransformComposite *boardTc = new TransformComposite();
		
		this->addModel(eb408);
		this->addModel(ebDoor);
		this->addModel(ebWboard);
		this->addModel(ebTable);
		this->addModel(ebChair);

		this->addShader(ebShader);

		ebTc->addTransformation(new Translate(0.0f, 0.0f, 0.0f));

		doorTc->addTransformation(new Translate(-2.415f, 0.0f, 7.75f));
		doorTc->addTransformation(new Scale(0.0106f, 0.0106f, 0.0106f));

		boardTc->addTransformation(new Translate(-3.8f, 0.5f, 3.0f));

		ebObject->setTransformation(ebTc);
		doorObject->setTransformation(doorTc);
		wBoardObject->setTransformation(boardTc);

		this->addObject(ebObject);
		this->addObject(doorObject);
		this->addObject(wBoardObject);

		int obIndex = 1;
		for (int i = 1; i < 4; i++) {
			for (int j = 1; j < 4; j++) {
				DrawableObject* t = new DrawableObject(ebTable, ebShader, tableTexture, obIndex++);
				TransformComposite* tTc = new TransformComposite();
				tTc->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0));
				tTc->addTransformation(new Translate((-2.0f * i) + 0.7f, 0.0f, (1.7f * j) - 2.9f));
				t->setTransformation(tTc);
				this->addObject(t);

				DrawableObject* c1 = new DrawableObject(ebChair, ebShader, chairTexure,obIndex++);
				TransformComposite* cTc1 = new TransformComposite();
				cTc1->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0));
				cTc1->addTransformation(new Translate((-2.0f * i) + 0.7f - 0.4f, 0.0f, (1.7f * j) - 2.9f + 0.5f));
				cTc1->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0));
				c1->setTransformation(cTc1);
				this->addObject(c1);

				DrawableObject* c2 = new DrawableObject(ebChair, ebShader, chairTexure,obIndex++);
				TransformComposite* cTc2 = new TransformComposite();
				cTc2->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0));
				cTc2->addTransformation(new Translate((-2.0f * i) + 0.7f + 0.4f, 0.0f, (1.7f * j) - 2.9f + 0.5f));
				cTc2->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0));
				c2->setTransformation(cTc2);
				this->addObject(c2);
			}
		}

	}
};
