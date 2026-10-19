#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec3 inColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;


out vec3 worldPos;
out vec3 worldNorm;
out vec3 vertexColor;
out vec3 viewDir;
out vec3 reflectDir;

void main(void){

    worldPos = vec3(modelMatrix * vec4(vp,1.0));  
    worldNorm = vn; //problem

    vertexColor = inColor;
    viewDir = normalize(cameraPosition - worldPos);
    reflectDir = normalize(reflect(-viewDir, worldNorm));

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp,1.0);
}