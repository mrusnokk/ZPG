/**
 * @file ShaderProgram.h
 *
 * @brief Class handling the compilation, linking, and usage of OpenGL shader programs.
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once
#include <glad/gl.h>
#include "glm-master/glm/glm.hpp"
#include <string>
#include "camera/ICameraObserver.h"
#include "lighting/ILightObserver.h"
#include "lighting/Light.h"

class ShaderProgram :public ICameraObserver, public ILightObserver {

public:
	ShaderProgram(const char* vertexPaht, const char* fragmentPath);
	~ShaderProgram();

	void use();
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float x, float y, float z);
	bool hasUniform(const char* name) const;
	GLuint getId() { return id; }
	void setMatrix(const char* name, glm::mat4 matrix);
	void onCameraChange(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPosition) override;
	void onLightChange(const Light& light) override;
	private:
		GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);
		GLuint id;
};