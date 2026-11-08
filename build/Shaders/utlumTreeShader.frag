#version 330 core

in vec3 wPosition;
in vec3 wNormal;
in vec3 fColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 fragColor;

float att(float d, float c, float l, float q)
{
    return clamp(1.0 / (c + l * d + q * d * d), 0.0, 1.0);
}

void main(void)
{
    vec3 lightVec = lightPosition - wPosition;
    float dist = length(lightVec);
    vec3 L = lightVec / dist;
    vec3 N = normalize(wNormal);

    float diff = max(dot(L, N), 0.0);
    float attenuation = att(dist, 1.0, 0.7, 3.8);

    vec3 ambient = fColor * lightColor * lightIntensity * 0.1;
    vec3 diffuse = diff * fColor * lightColor * lightIntensity * attenuation;

    fragColor = vec4(ambient + diffuse, 1.0);
}