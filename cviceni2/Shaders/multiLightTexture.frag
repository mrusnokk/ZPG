#version 330 core

#define MAX_LIGHTS 32

struct light
{
    vec4 position;
    vec4 diffuse;
    vec3 direction;
    int type;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 worldPos;
in vec3 worldNorm;
in vec2 TexCoords;

uniform vec3 cameraPosition;
uniform light lights[MAX_LIGHTS];
uniform int numberOfLights;
uniform sampler2D textureUnitID;
uniform Material material;

out vec4 fragColor;

float calculateDiffuse(vec3 lightDir, vec3 normal)
{
    float dotLN = dot(normalize(lightDir), normal);
    return max(dotLN, 0.0);
}

float att(float d, float c, float l, float q)
{
    return clamp(1.0 / (c + l * d + q * d * d), 0.0, 1.0);
}

void main() {
    vec3 normWorldNorm = normalize(worldNorm);
    vec3 normViewDir = normalize(cameraPosition - worldPos);

    vec3 matAmbient = (length(material.ambient) > 0.0001) ? material.ambient : vec3(0.1);
    vec3 matDiffuse = (length(material.diffuse) > 0.0001) ? material.diffuse : vec3(1.0);
    vec3 matSpecular = (length(material.specular) > 0.0001) ? material.specular : vec3(1.0);
    float matShininess = (material.shininess > 0.0) ? material.shininess : 32.0;

    float diff = 0.0;
    float spec = 0.0;

    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    int count = (numberOfLights > 0) ? min(numberOfLights, MAX_LIGHTS) : MAX_LIGHTS;

    for (int i = 0; i < count; i++) {
        vec3 normLightDir;
        float attenuation = 1.0;

        float c = (lights[i].constant > 0.0001 || lights[i].linear > 0.0001 || lights[i].quadratic > 0.0001) ? lights[i].constant : 1.0;
        float l = (lights[i].constant > 0.0001 || lights[i].linear > 0.0001 || lights[i].quadratic > 0.0001) ? lights[i].linear : 0.7;
        float q = (lights[i].constant > 0.0001 || lights[i].linear > 0.0001 || lights[i].quadratic > 0.0001) ? lights[i].quadratic : 3.8;

        if (lights[i].type == 1) {
            normLightDir = normalize(-lights[i].direction);
            attenuation = 1.0;
        } else {
            vec3 lightVec = lights[i].position.xyz - worldPos;
            float dist = length(lightVec);
            if (dist <= 0.0001) {
                continue;
            }
            normLightDir = lightVec / dist;
            attenuation = att(dist, c, l, q);

            if (lights[i].type == 2) {
                vec3 dirFromLight = -normLightDir;
                float dotLF = dot(dirFromLight, normalize(lights[i].direction));
                float cutOff = (lights[i].cutOff > 0.0) ? lights[i].cutOff : cos(radians(15.0));
                float outerCutOff = (lights[i].outerCutOff > 0.0 && lights[i].outerCutOff < cutOff) ? lights[i].outerCutOff : (cutOff - 0.05);

                float spotIntensity = clamp((dotLF - outerCutOff) / (cutOff - outerCutOff), 0.0, 1.0);
                attenuation *= spotIntensity;
            }
        }

        if (attenuation <= 0.0001) {
            continue;
        }

        vec3 halfwayDir = normalize(normLightDir + normViewDir);

        diff = calculateDiffuse(normLightDir, normWorldNorm);
        spec = pow(max(dot(normWorldNorm, halfwayDir), 0.0), matShininess);

        if (diff <= 0.0) {
            spec = 0.0;
        }

        totalDiffuse += diff * lights[i].diffuse.xyz * attenuation;
        totalSpecular += spec * lights[i].diffuse.xyz * attenuation;
    }

    vec4 texColor = texture(textureUnitID, TexCoords);
    vec3 ambient = matAmbient * texColor.rgb;
    vec3 diffusePart = totalDiffuse * matDiffuse * texColor.rgb;
    vec3 specularPart = totalSpecular * matSpecular;

    vec3 resultColor = ambient + diffusePart + specularPart;

    fragColor = vec4(resultColor, 1.0);
}
