#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec2 tex_cord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float uvScale;

out vec3 worldPos;
out vec3 worldNorm;
out vec2 TexCoords;

void main() {
    worldPos = vec3(modelMatrix * vec4(vp, 1.0));
    worldNorm = mat3(transpose(inverse(modelMatrix))) * vn;
    float scale = (uvScale > 0.0) ? uvScale : 1.0;
    TexCoords = tex_cord * scale;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}
