#version 330 core

in vec3 worldPos;
in vec3 worldNorm;
in vec3 vertexColor;
in vec3 viewDir;

uniform vec3 cameraPosition;

out vec4 fragColor;

float calculateDiffuse(vec3 normLightDir, vec3 normWorldNorm)
{
	float dotLN = dot(normLightDir, normWorldNorm);
	return max(dotLN, 0.0);
}

void main(void)
{
	vec3 lightPosition= vec3(0.0,0.0,0.0);

	vec3 normWorldNorm = normalize(worldNorm);
    vec3 normLightDir = normalize(lightPosition - worldPos);
    vec3 normViewDir = normalize(cameraPosition - worldPos);

	vec3 halfwayDir = normalize(normLightDir + normViewDir);

	float diff= calculateDiffuse(normLightDir, normWorldNorm);

	float spec = pow(max(dot(normWorldNorm, halfwayDir), 0.0), 32.0);

	vec3 ambient=vec3(0.1,0.1,0.1);

	vec3 resultColor = ambient + (diff * vertexColor ) + (spec * vec3(1.0));

	fragColor=vec4(resultColor, 1.0);
}