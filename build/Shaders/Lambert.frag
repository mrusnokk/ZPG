# version 330 core 

in vec3 wPosition;
in vec3 wNormal;
in vec3 fColor;

out vec4 fragColor;

void main (void)
{
	vec3 lightPosition = vec3 (0.0, 0.0, 0.0);
	vec3 lightDir = lightPosition - wPosition;

	float diff = max(dot(normalize(lightDir),normalize (wNormal)),0.0);
	
	vec3 ambient = vec3 (0.1, 0.1, 0.1);
	fragColor =  vec4((ambient*fColor), 1.0) + vec4(diff * fColor, 1.0);
}