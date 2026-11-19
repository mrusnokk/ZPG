#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 worldPos;
in vec3 worldNorm;
in vec3 vertexColor;

uniform vec3 cameraPosition;
uniform Material material;

out vec4 fragColor;

float calculateDiffuse(vec3 normLightDir, vec3 normWorldNorm)
{
	float dotLN = dot(normLightDir, normWorldNorm);
	return max(dotLN, 0.0);
}

void main(void)
{
	vec3 lightPosition = vec3(0.0, 0.0, 0.0);

	vec3 normWorldNorm = normalize(worldNorm);
	vec3 normLightDir = normalize(lightPosition - worldPos);
	vec3 normViewDir = normalize(cameraPosition - worldPos);

	vec3 matAmbient = (length(material.ambient) > 0.0001) ? material.ambient : vec3(0.1);
	vec3 matDiffuse = (length(material.diffuse) > 0.0001) ? material.diffuse : vec3(1.0);
	vec3 matSpecular = (length(material.specular) > 0.0001) ? material.specular : vec3(1.0);
	float matShininess = (material.shininess > 0.0) ? material.shininess : 32.0;

	vec3 halfwayDir = normalize(normLightDir + normViewDir);

	float diff = calculateDiffuse(normLightDir, normWorldNorm);

	float spec = pow(max(dot(normWorldNorm, halfwayDir), 0.0), matShininess);

	vec3 resultColor = (matAmbient * vertexColor) + (diff * matDiffuse * vertexColor) + (spec * matSpecular);

	fragColor = vec4(resultColor, 1.0);
}
