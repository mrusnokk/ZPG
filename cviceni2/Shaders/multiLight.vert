#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 objectColor;

out vec3 worldPos;
out vec3 worldNorm;
out vec3 vertexColor;

void main() {  
    worldPos = vec3(modelMatrix * vec4(vp, 1.0));  
    worldNorm = mat3(transpose(inverse(modelMatrix))) * vn;

    if (length(objectColor) > 0.001) {
        vertexColor = objectColor;
    } else {
        if (gl_VertexID < 36443) {
            vertexColor = vec3(186.0 / 255.0, 140.0 / 255.0, 99.0 / 255.0);
        } else {
            vertexColor = vec3(92.0 / 255.0, 169.0 / 255.0, 4.0 / 255.0);
        }
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}