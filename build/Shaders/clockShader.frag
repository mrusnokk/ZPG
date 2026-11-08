#version 330
in vec3 vertexColor;
out vec4 FragColor;

void main() {
vec3 color;
    if (vertexColor.r > 0.9 && vertexColor.g > 0.9 && vertexColor.b < 0.1) 
    {
        color =  vec3(5/255.0f,195/255.0f,222/255.0f);
    }
    else{
        color = vertexColor;
    }
    FragColor = vec4(color, 1.0); 
}