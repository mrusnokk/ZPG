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

mat4 rotZ(float a) {
    float c = cos(a), s = sin(a);
    return mat4( c,   s,   0.0, 0.0,
                -s,   c,   0.0, 0.0,
                 0.0, 0.0, 1.0, 0.0,
                 0.0, 0.0, 0.0, 1.0);
}

void main() {
    mat4 hand = mat4(1.0);
    if      (color.r > 0.9 && color.g < 0.1 && color.b < 0.1) hand = rotZ(secondAngle);
    else if (color.g > 0.9 && color.r < 0.1 && color.b < 0.1) hand = rotZ(minuteAngle);
    else if (color.b > 0.9 && color.r < 0.1 && color.g < 0.1) hand = rotZ(hourAngle);

    vertexColor = color;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * hand * vec4(position, 1.0);
}