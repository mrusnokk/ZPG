#version 330 core

in vec2 TexCoords;

uniform sampler2D textureUnitID;

out vec4 fragColor;

void main(void) {
    fragColor = texture(textureUnitID, TexCoords);
    //fragColor = vec4(1.0, 0.0, 1.0, 1.0);
}