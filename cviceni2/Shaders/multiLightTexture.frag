#version 330 core

#define MAX_LIGHTS 100

struct light
{
    vec4 position;
    vec4 diffuse;
};

in vec3 worldPos;
in vec3 worldNorm;
in vec2 TexCoords;

uniform vec3 cameraPosition;
uniform light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform sampler2D textureUnitID;

out vec4 fragColor;

float calculateDiffuse(vec3 lightDir, vec3 normal)
{
    float dotLN = dot(normalize(lightDir), normalize(normal));
    return max(dotLN, 0.0);
}

float att(float d, float c, float l, float q)
{
    return clamp(1.0 / (c + l * d + q * d * d), 0.0, 1.0);
}

void main() {
    vec3 normWorldNorm = normalize(worldNorm);
    vec3 normViewDir = normalize(cameraPosition - worldPos);

    float diff = 0.0;
    float spec = 0.0;

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    int count = (numberOfLights > 0) ? min(numberOfLights, MAX_LIGHTS) : MAX_LIGHTS;

    for (int i = 0; i < count; i++) {
        vec3 lightVec = lights[i].position.xyz - worldPos;
        float dist = length(lightVec);
        if (dist > 0.0001) {
            vec3 normLightDir = lightVec / dist;
            vec3 halfwayDir = normalize(normLightDir + normViewDir);

            diff = calculateDiffuse(normLightDir, normWorldNorm);
            spec = pow(max(dot(normWorldNorm, halfwayDir), 0.0), 32.0);

            if (diff <= 0.0) {
                spec = 0.0;
            }

            float attenuation = att(dist, 1.0, 0.7, 3.8);

            totalDiffuse += diff * lights[i].diffuse.xyz * attenuation;
            totalSpecular += spec * lights[i].diffuse.xyz * attenuation;
        }
    }

    vec4 texColor = texture(textureUnitID, TexCoords);
    vec3 ambient = vec3(0.1, 0.1, 0.1) * texColor.rgb;

    vec3 resultColor = ambient + (totalDiffuse * texColor.rgb) + totalSpecular;

    fragColor = vec4(resultColor, 1.0);
}
