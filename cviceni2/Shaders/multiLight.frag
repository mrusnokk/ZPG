
#define MAX_LIGHTS 4

struct light
{
  vec4 position;
  vec4 diffuse;
};

in vec3 worldPos;
in vec3 worldNorm;
in vec3 vertexColor;

uniform vec3 cameraPosition;
uniform light lights[MAX_LIGHTS];

out vec4 fragColor;

float calculateDiffuse(vec3 lightDir, vec3 normal)
{
	float dotLN = dot(normalize(lightDir),normalize(normal));

	return max(dotLN, 0.0);
}


void main(){
	vec3 normWorldNorm = normalize(worldNorm);
	vec3 normViewDir = normalize(cameraPosition - worldPos);

	float diff = 0.0;
    float spec = 0.0;

	vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

	vec3 normLightDir;
	vec3 reflectDir;

	for(int i = 0; i < MAX_LIGHTS; i++){
		normLightDir = normalize(lights[i].position.xyz - worldPos);
		reflectDir = reflect(-normLightDir, normWorldNorm);
		diff = calculateDiffuse(normLightDir, normWorldNorm);
		spec = pow(max(dot(normViewDir, reflectDir), 0.0), 32.0);

		if(diff <= 0.0){
			spec = 0.0;
		}

	totalDiffuse += diff * lights[i].diffuse.xyz;
	totalSpecular += specIntensity * lights[i].diffuse.xyz;

	}	
	
	
	
	vec3 ambient=vec3(0.1,0.1,0.1);

	vec3 resultColor = (ambient*vertexColor) + (totalDiffuse* vertexColor ) + (totalSpecular*vertexColor);

	fragColor=vec4(resultColor, 1.0);

}
