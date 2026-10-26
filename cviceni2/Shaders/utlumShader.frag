# version 330 core 

in vec3 wPosition;
in vec3 wNormal;
in vec3 fColor;

out vec4 fragColor;

void main (void)
{
	vec3 lightPosition = vec3 (0.0, 0.0, 0.0);
	float distance = length(lightPosition - wPosition);
	vec3 lightDir = lightPosition - wPosition;
	vec3 nLightDir = lightDir/distance;

	float diff = max(dot(normalize(nLightDir),normalize (wNormal)),0.0);
	
	float constant = 1.0;
	float linear = 0.09;
	float quadratic = 0.032;

	float attenuation = 1.0/(constant + linear * distance + quadratic * distance * distance);

	vec3 ambient = vec3 (0.1, 0.1, 0.1) * fColor;
	fragColor =  vec4((ambient*fColor*attenuation), 1.0) + vec4(diff * fColor * attenuation, 1.0);
}