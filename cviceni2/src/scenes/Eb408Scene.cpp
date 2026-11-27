#include "scenes/Eb408Scene.h"
#include "lighting/PointLight.h"
#include "lighting/DirectionalLight.h"
#include "lighting/SpotLight.h"
#include "models/eb408.h"
#include "models/door.h"
#include "models/Whiteboard.h"
#include "models/chair.h"
#include "models/table.h"
#include "models/rus0130.h"
#include <cstdlib>
#include <ctime>

Eb408Scene::Eb408Scene(int w, int h, int lightCount) {
	this->cam = new Camera(glm::vec3(0.0f, 1.0f, 1.0f), w, h);
	this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

	srand(static_cast<unsigned int>(time(nullptr)));

	for (int i = 0; i < lightCount; i++) {
		glm::vec3 col;
		if (i % 3 == 0) {
			col = glm::vec3(1.0f, 0.0f, 0.0f);
		}
		else if (i % 3 == 1) {
			col = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else {
			col = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		float rX = ((rand() % 600) - 300) / 100.0f;
		float rY = ((rand() % 180) + 70) / 100.0f;
		float rZ = ((rand() % 650) + 50) / 100.0f;

		this->addLight(new PointLight(i, glm::vec3(rX, rY, rZ), col, 5.0f));
	}

	this->addLight(new DirectionalLight(lightCount, glm::vec3(0.3f, -1.0f, -0.2f), glm::vec3(1.0f, 0.95f, 0.85f), 0.4f));
	this->addLight(new SpotLight(lightCount + 1, glm::vec3(0.0f, 3.2f, 3.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 6.0f, 25.0f, 35.0f));

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
	Model* ebWboard = new Model(WhiteboardModel, sizeof(WhiteboardModel), WhiteboardVertexCount, 8);
	Model* ebTable = new Model(TableModel, sizeof(TableModel), TableVertexCount, 8);
	Model* ebChair = new Model(ChairModel, sizeof(ChairModel), ChairVertexCount, 8);
	Model* login = new Model(login_model, sizeof(login_model), 6996);

	ShaderProgram* ebShader = new ShaderProgram("Shaders/multiLightTexture.vert", "Shaders/multiLightTexture.frag");
	ShaderProgram* basic = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");

	Texture* ebTexture = new Texture("src/textures/T_EB408.png");
	Texture* doorTexture = new Texture("src/textures/door.png");
	Texture* whiteBoardTexture = new Texture("src/textures/texture_zpg.jpeg");
	Texture* tableTexture = new Texture("src/textures/table.png");
	Texture* chairTexure = new Texture("src/textures/chair.png");

	DrawableObject* ebObject = new DrawableObject(eb408, ebShader, ebTexture, 100);
	DrawableObject* doorObject = new DrawableObject(ebDoor, ebShader, doorTexture, 101);
	DrawableObject* wBoardObject = new DrawableObject(ebWboard, ebShader, whiteBoardTexture, 102);
	DrawableObject* rusLogin = new DrawableObject(login, basic);

	TransformComposite* ebTc = new TransformComposite();
	TransformComposite* doorTc = new TransformComposite();
	TransformComposite* boardTc = new TransformComposite();
	TransformComposite* loginTc = new TransformComposite();

	this->addModel(eb408);
	this->addModel(ebDoor);
	this->addModel(ebWboard);
	this->addModel(ebTable);
	this->addModel(ebChair);
	this->addModel(login);

	this->addShader(ebShader);
	this->addShader(basic);

	this->addTexture(ebTexture);
	this->addTexture(doorTexture);
	this->addTexture(whiteBoardTexture);
	this->addTexture(tableTexture);
	this->addTexture(chairTexure);

	ebTc->addTransformation(new Translate(0.0f, 0.0f, 0.0f));

	doorTc->addTransformation(new Translate(-2.415f, 0.0f, 7.75f));
	doorTc->addTransformation(new Scale(0.0106f, 0.0106f, 0.0106f));

	boardTc->addTransformation(new Translate(-3.8f, 0.5f, 3.0f));

	loginTc->addTransformation(new Translate(3.0f, 2.0f, 4.0f));
	loginTc->addTransformation(new Rotate(270.0f, 0.0f, 1.0f, 0.0f));

	ebObject->setTransformation(ebTc);
	doorObject->setTransformation(doorTc);
	wBoardObject->setTransformation(boardTc);
	rusLogin->setTransformation(loginTc);

	Material* boardMaterial = new Material(glm::vec3(0.15f), glm::vec3(0.9f), glm::vec3(0.9f), 64.0f);
	Material* tableMaterial = new Material(glm::vec3(0.1f), glm::vec3(0.85f), glm::vec3(0.3f), 16.0f);
	Material* chairMaterial = new Material(glm::vec3(0.05f), glm::vec3(0.5f), glm::vec3(0.7f), 10.0f);
	this->addMaterial(boardMaterial);
	this->addMaterial(tableMaterial);
	this->addMaterial(chairMaterial);

	wBoardObject->setMaterial(boardMaterial);

	this->addObject(ebObject);
	this->addObject(doorObject);
	this->addObject(wBoardObject);
	this->addObject(rusLogin);

	int obIndex = 1;
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			DrawableObject* t = new DrawableObject(ebTable, ebShader, tableMaterial, tableTexture, obIndex++);
			TransformComposite* tTc = new TransformComposite();
			tTc->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0f));
			tTc->addTransformation(new Translate((-2.0f * i) + 0.7f, 0.0f, (1.7f * j) - 2.9f));
			t->setTransformation(tTc);
			this->addObject(t);

			DrawableObject* c1 = new DrawableObject(ebChair, ebShader, chairMaterial, chairTexure, obIndex++);
			TransformComposite* cTc1 = new TransformComposite();
			cTc1->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0f));
			cTc1->addTransformation(new Translate((-2.0f * i) + 0.7f - 0.4f, 0.0f, (1.7f * j) - 2.9f + 0.5f));
			cTc1->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
			c1->setTransformation(cTc1);
			this->addObject(c1);

			DrawableObject* c2 = new DrawableObject(ebChair, ebShader, chairMaterial, chairTexure, obIndex++);
			TransformComposite* cTc2 = new TransformComposite();
			cTc2->addTransformation(new Rotate(90.0f, 0.0f, 1.0f, 0.0f));
			cTc2->addTransformation(new Translate((-2.0f * i) + 0.7f + 0.4f, 0.0f, (1.7f * j) - 2.9f + 0.5f));
			cTc2->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
			c2->setTransformation(cTc2);
			this->addObject(c2);
		}
	}
}
