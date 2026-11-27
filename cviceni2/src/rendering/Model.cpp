#include "rendering/Model.h"

Model::Model(const float* vertices, size_t size, int count, int floatsPerVertex) {
	vertexCount = count;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	int stride = floatsPerVertex * sizeof(float);
	if (floatsPerVertex == 3) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	else if (floatsPerVertex == 6) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	else if (floatsPerVertex == 8) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	else if (floatsPerVertex == 9) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	glBindVertexArray(0);
}

void Model::setInstanceMatrices(const std::vector<glm::mat4>& matrices) {
	instanceCount = static_cast<int>(matrices.size());
	if (instanceVBO == 0) {
		glGenBuffers(1, &instanceVBO);
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), matrices.data(), GL_STATIC_DRAW);

	std::size_t vec4Size = sizeof(glm::vec4);
	for (int i = 0; i < 4; i++) {
		glEnableVertexAttribArray(3 + i);
		glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
		glVertexAttribDivisor(3 + i, 1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::draw() {
	glBindVertexArray(VAO);
	if (instanceCount > 0) {
		glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, instanceCount);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}
	glBindVertexArray(0);
}

Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	if (instanceVBO != 0) {
		glDeleteBuffers(1, &instanceVBO);
	}
}
