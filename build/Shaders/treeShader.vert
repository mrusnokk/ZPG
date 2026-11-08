#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 inColor;

out vec3 vertexColor;
out vec3 fragNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    vec3 color;
    
    if (gl_VertexID > 36443) {
        color = vec3(92/255.0f, 169/255.0f, 4/255.0f);
    } else {
        color = vec3(186/255.0f, 140/255.0f, 99/255.0f);
    }

    vertexColor = color;
    fragNormal = normal;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}