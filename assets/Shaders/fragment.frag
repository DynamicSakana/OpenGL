#version 460 core
uniform sampler2D samp;
uniform float u_velocity;
uniform float u_time;
in vec2 uv;

out vec4 FragColor;

void main()
{
	FragColor = vec4(texture(samp, uv));
}