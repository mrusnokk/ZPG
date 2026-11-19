/**
 * @file Material.h
 *
 * @brief Class representing material optical properties (ambient, diffuse, specular, shininess).
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once
#include <glm/glm.hpp>

class Material {
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

public:
	Material() :
		ambient(glm::vec3(0.1f)),
		diffuse(glm::vec3(1.0f)),
		specular(glm::vec3(1.0f)),
		shininess(32.0f) {}

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
		ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

	~Material() = default;

	void setAmbient(const glm::vec3& a) { this->ambient = a; }
	void setDiffuse(const glm::vec3& d) { this->diffuse = d; }
	void setSpecular(const glm::vec3& s) { this->specular = s; }
	void setShininess(float s) { this->shininess = s; }

	glm::vec3 getAmbient() const { return this->ambient; }
	glm::vec3 getDiffuse() const { return this->diffuse; }
	glm::vec3 getSpecular() const { return this->specular; }
	float getShininess() const { return this->shininess; }
};
