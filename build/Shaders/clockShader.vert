#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;


out vec3 vertexColor;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform float hourAngle;
uniform float minuteAngle;
uniform float secondAngle;

vec3 rot(vec3 p,float a) {
    float c = cos(a), s = sin(a);
    return vec3(p.x * c - p.y * s, p.x * s + p.y * c, p.z);
}

void main() {
    vec3 finalPosition = position;
    if      (color.r == 1.0 && color.g == 0.0 && color.b == 0.0) finalPosition = rot(position,secondAngle);
    else if (color.g == 1.0 && color.r == 0.0 && color.b == 0.0) finalPosition = rot(position,minuteAngle);
    else if (color.b == 1.0 && color.r == 0.0 && color.g == 0.0) finalPosition = rot(position,hourAngle);
    vertexColor = color;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(finalPosition, 1.0);
}