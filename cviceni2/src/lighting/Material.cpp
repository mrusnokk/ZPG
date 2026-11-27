#include "lighting/Material.h"

Material::Material()
	: ambient(glm::vec3(0.1f)),
	  diffuse(glm::vec3(1.0f)),
	  specular(glm::vec3(1.0f)),
	  shininess(32.0f) {}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
	: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

void Material::setAmbient(const glm::vec3& a) { this->ambient = a; }
void Material::setDiffuse(const glm::vec3& d) { this->diffuse = d; }
void Material::setSpecular(const glm::vec3& s) { this->specular = s; }
void Material::setShininess(float s) { this->shininess = s; }

glm::vec3 Material::getAmbient() const { return this->ambient; }
glm::vec3 Material::getDiffuse() const { return this->diffuse; }
glm::vec3 Material::getSpecular() const { return this->specular; }
float Material::getShininess() const { return this->shininess; }
