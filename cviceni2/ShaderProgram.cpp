#include "ShaderProgram.h"
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
	glUseProgram(id);
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