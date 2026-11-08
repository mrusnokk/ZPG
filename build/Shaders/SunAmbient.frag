#version 330

out vec4 FragColor;

in vec3 fColor;

void main()
{
	float ambientStrenght = 1.0;
	vec3 res = ambientStrenght * fColor;
	FragColor = vec4(res, 1.0);
}


