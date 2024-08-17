#version 460 core
uniform sampler2D skySampler;
uniform sampler2D catSampler;
uniform sampler2D cloudSampler;

in vec2 uv;
in vec3 color;

out vec4 FragColor;

void main()
{
	FragColor = vec4(texture(cloudSampler, uv).rgb, 1.0);
}