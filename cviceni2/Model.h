/**
 * @file Model.h
 *
 * @brief Class representing 3D model geometry and managing OpenGL vertex arrays and buffers.
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once

#include <glad/gl.h>

class Model {
private:
	GLuint VAO, VBO;
	int vertexCount;
public:
	Model(const float* vertices, size_t size, int count) {
		vertexCount = count;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
	void draw() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		glBindVertexArray(0);
	}
	~Model() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
};