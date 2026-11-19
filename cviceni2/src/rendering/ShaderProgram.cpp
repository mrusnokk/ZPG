#include "rendering/ShaderProgram.h"
#include "camera/Camera.h"
#include "lighting/Material.h"
#include <iostream>
#include <fstream>
#include <sstream>


ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
	GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertexFile);
	GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragmentFile);

	id = glCreateProgram();

	glAttachShader(id, fragmentShader);
	glAttachShader(id, vertexShader);
	glLinkProgram(id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}
GLuint ShaderProgram::createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
	// Creates an empty shader
	GLuint shaderID = glCreateShader(shaderType);

	if (shaderID == 0)
	{
		std::cout << "Unable to create shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	//Loading the contents of a file into a variable
	std::ifstream file(shaderFile);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << shaderFile << std::endl;
		glDeleteShader(shaderID);
		exit(-1);
	}
	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Set the shader source code
	const char* source = shaderCode.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);

	// Compile the shader source code
	glCompileShader(shaderID);

	// Check specialization/compilation status
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
		std::cout
			<< "Shader failed:\n"
			<< infoLog << std::endl;
		glDeleteShader(shaderID);
		exit(1);
	}
	return shaderID;
}
void ShaderProgram::use() {
	glUseProgram(getId());
}
ShaderProgram::~ShaderProgram() {
	glDeleteProgram(id);
}
void ShaderProgram::setUniform(const char* name, float value){
	GLint location = glGetUniformLocation(id, name);
	if (location == -1) {
		std::cerr << "Uniform variable '" << name << "' does not exist or is not used in shader!" << std::endl;
	}
	else {
		glUniform1f(location, value);
	}
}
void ShaderProgram::setUniform(const char* name, int value){
	GLint location = glGetUniformLocation(id, name);
	if (location == -1) {
		std::cerr << "Uniform variable '" << name << "' does not exist or is not used in shader!" << std::endl;
	}
	else {
		glUniform1i(location, value);
	}
}
void ShaderProgram::setUniform(const char* name, float x, float y, float z) {
	GLint location = glGetUniformLocation(id, name);
	if (location == -1) {
		std::cerr << "Uniform variable '" << name << "' does not exist or is not used in shader!" << std::endl;
	}
	else {
		glUniform3f(location, x, y, z);
	}
}
void ShaderProgram::setUniform(const char* name, const glm::vec3& value) {
	this->setUniform(name, value.x, value.y, value.z);
}
void ShaderProgram::setUniform(const char* name, float x, float y, float z, float a) {
	GLint location = glGetUniformLocation(id, name);
	if (location == -1) {
		std::cerr << "Uniform variable '" << name << "' does not exist or is not used in shader!" << std::endl;
	}
	else {
		glUniform4f(location, x, y, z,a);
	}
}
bool ShaderProgram::hasUniform(const char* name)const{
	return glGetUniformLocation(id, name) != -1;
}
void ShaderProgram::setMatrix(const char* name, glm::mat4 matrix) {
	GLuint location = glGetUniformLocation(id, name);

	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}
	else {
		std::cerr << "Warning! : variable '" << name << "' does not exist or is not used in shader!" << std::endl;
	}
}
void ShaderProgram::onCameraChange(Camera* camera) {
	this->use();
	if (hasUniform("viewMatrix"))
		this->setMatrix("viewMatrix", camera->getViewMatrix());
	if (hasUniform("projectionMatrix"))
		this->setMatrix("projectionMatrix", camera->getProjectionMatrix());
	if (hasUniform("cameraPosition")) {
		glm::vec3 pos = camera->getPosition();
		this->setUniform("cameraPosition", pos.x, pos.y, pos.z);
	}
}
void ShaderProgram::onLightChange(const Light& light) {
	this->use();
	int i = light.getIndex();

	std::string base = "lights[" + std::to_string(i) + "].";

	glm::vec3 pos = light.getPosition();
	glm::vec3 diff = light.getDiffuse();
	glm::vec3 dir = light.getDirection();

	if (hasUniform((base + "position").c_str()))
		this->setUniform((base + "position").c_str(), pos.x, pos.y, pos.z, 1.0f);
	if (hasUniform((base + "diffuse").c_str()))
		this->setUniform((base + "diffuse").c_str(), diff.r, diff.g, diff.b, 1.0f);
	if (hasUniform((base + "direction").c_str()))
		this->setUniform((base + "direction").c_str(), dir.x, dir.y, dir.z);
	if (hasUniform((base + "type").c_str()))
		this->setUniform((base + "type").c_str(), static_cast<int>(light.getType()));
	if (hasUniform((base + "cutOff").c_str()))
		this->setUniform((base + "cutOff").c_str(), light.getCutOff());
	if (hasUniform((base + "outerCutOff").c_str()))
		this->setUniform((base + "outerCutOff").c_str(), light.getOuterCutOff());
	if (hasUniform((base + "constant").c_str()))
		this->setUniform((base + "constant").c_str(), light.getConstant());
	if (hasUniform((base + "linear").c_str()))
		this->setUniform((base + "linear").c_str(), light.getLinear());
	if (hasUniform((base + "quadratic").c_str()))
		this->setUniform((base + "quadratic").c_str(), light.getQuadratic());
}

void ShaderProgram::setMaterial(const Material* material) {
	if (material != nullptr) {
		if (hasUniform("material.ambient"))
			setUniform("material.ambient", material->getAmbient());
		if (hasUniform("material.diffuse"))
			setUniform("material.diffuse", material->getDiffuse());
		if (hasUniform("material.specular"))
			setUniform("material.specular", material->getSpecular());
		if (hasUniform("material.shininess"))
			setUniform("material.shininess", material->getShininess());
	}
	else {
		if (hasUniform("material.ambient"))
			setUniform("material.ambient", 0.1f, 0.1f, 0.1f);
		if (hasUniform("material.diffuse"))
			setUniform("material.diffuse", 1.0f, 1.0f, 1.0f);
		if (hasUniform("material.specular"))
			setUniform("material.specular", 1.0f, 1.0f, 1.0f);
		if (hasUniform("material.shininess"))
			setUniform("material.shininess", 32.0f);
	}
}
