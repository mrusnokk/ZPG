#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec3 inColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


out vec3 worldPos;
out vec3 worldNorm;
out vec3 vertexColor;

void main(void){
    
    worldPos = vec3(modelMatrix * vec4(vp,1.0));  
    //worldNorm = mat3(transpose(inverse(modelMatrix))) * vn;
    worldNorm = mat3(modelMatrix)* vn;

    vertexColor = vec3 (0.385f, 0.647f, 0.812f);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp,1.0);
}