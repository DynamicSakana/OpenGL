#version 330 core
uniform float u_time;
in vec3 color;
out vec4 FragColor;
void main()
{
	float density = (cos(u_time) + 1) / 2;
	FragColor = vec4(vec3(density) + color, 1.0);
}