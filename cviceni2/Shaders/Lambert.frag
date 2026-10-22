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
	
	vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);
	fragColor =  ambient + vec4(diff * fColor, 1.0);
}