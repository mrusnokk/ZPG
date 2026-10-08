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
#include "glm-master/glm/glm.hpp";
#include <string>

class ShaderProgram {

public:
	ShaderProgram(const char* vertexPaht, const char* fragmentPath);
	~ShaderProgram();

	void use();
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, float x, float y, float z);
	GLuint getId() { return id; }
	void setMatrix(const char* name, glm::mat4 matrix);

	private:
		void checkCompileErrors(GLuint shader, std::string type) const;
		GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);
		GLuint id;
};