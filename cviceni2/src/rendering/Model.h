/**
 * @file Model.h
 * @brief Class representing 3D model geometry and managing OpenGL vertex arrays and buffers.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <cstddef>
#include <vector>

class Model {
private:
	GLuint VAO, VBO;
	GLuint instanceVBO = 0;
	int vertexCount;
	int instanceCount = 0;

public:
	Model(const float* vertices, size_t size, int count, int floatsPerVertex = 6);
	~Model();

	void setInstanceMatrices(const std::vector<glm::mat4>& matrices);
	void draw();
};
