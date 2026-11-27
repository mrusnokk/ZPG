/**
 * @file Material.h
 * @brief Class representing material optical properties (ambient, diffuse, specular, shininess).
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <glm/glm.hpp>

class Material {
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

public:
	Material();
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	~Material() = default;

	void setAmbient(const glm::vec3& a);
	void setDiffuse(const glm::vec3& d);
	void setSpecular(const glm::vec3& s);
	void setShininess(float s);

	glm::vec3 getAmbient() const;
	glm::vec3 getDiffuse() const;
	glm::vec3 getSpecular() const;
	float getShininess() const;
};
