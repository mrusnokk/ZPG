/**
 * @file Scene.h
 *
 * @brief Class for managing and rendering a collection of drawable objects.
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once
#include <vector>
#include "rendering/DrawableObject.h"
#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Texture.h"
#include "lighting/Material.h"
#include "transform/TransformComposite.h"
#include "transform/Translate.h"
#include "transform/Rotate.h"
#include "transform/Scale.h"
#include "camera/Camera.h"
#include "lighting/Light.h"
#include "lighting/SpotLight.h"
#include "lighting/Flashlight.h"
#include "rendering/Skybox.h"

class Scene {
private:
	std::vector<DrawableObject*> objects;
	std::vector<Model*> models;
	std::vector<ShaderProgram*> shaders;
	std::vector<Texture*> textures;
	std::vector<Material*> materials;
protected:
	Camera* cam = nullptr;
	std::vector<Light*> lights;
	Skybox* skybox = nullptr;
	Flashlight* flashlight = nullptr;

public:
	Scene();
	virtual ~Scene();
	void addObject(DrawableObject* object);
	bool removeObject(int id);
	DrawableObject* getObject(int id);
	void addModel(Model* model);
	void addShader(ShaderProgram* shader);
	void addLight(Light* light);
	void addTexture(Texture* texture);
	void addMaterial(Material* material);
	void setSkybox(Skybox* s);
	virtual void update() {}
	virtual void draw();
	virtual void onObjectClick(int id) {}
	Camera* getCam();

	Flashlight* getOrCreateFlashlight();
	void toggleFlashlight();
	bool isFlashlightOn() const;
	Flashlight* getFlashlight() const;
	void setFlashlight(Flashlight* fl);
};
