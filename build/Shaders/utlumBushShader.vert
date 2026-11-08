#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 wPosition;
out vec3 wNormal;
out vec3 fColor;

void main()
{	

	
	fColor = color;
	fColor = vec3(92/255.0f, 169/255.0f, 4/255.0f);
	wPosition = vec3(modelMatrix * vec4(position, 1.0));
	mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
	wNormal = normalize(normalMatrix * normal);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}