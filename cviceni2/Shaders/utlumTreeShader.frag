# version 330 core 

in vec3 wPosition;
in vec3 wNormal;
in vec3 fColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

out vec4 fragColor;

float att(float d, float c, float l, float q)
{
    float att=1.0/ (c + l*d + q*d*d);

    return clamp(att , 0.0 , 1.0);
}

void main (void)
{
	float distance = length(lightPosition - wPosition);
	vec3 lightDir = lightPosition - wPosition;
	vec3 nLightDir = lightDir/distance;

	float diff = max(dot(normalize(nLightDir),normalize (wNormal)),0.0);

	float attenuation = att(distance, 1.0f, 0.7f, 3.8f);

	vec3 ambient = fColor * lightIntensity * lightColor;
	fragColor =  vec4((ambient*fColor*attenuation), 1.0) + vec4(diff * fColor * attenuation, 1.0);
}