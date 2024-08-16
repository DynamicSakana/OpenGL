#version 460 core
uniform sampler2D skySampler;
uniform sampler2D catSampler;
uniform sampler2D cloudSampler;

in vec2 uv;
in vec3 color;

out vec4 FragColor;

void main()
{
	float weight = texture(catSampler, uv).r;
	vec4 finalColor = texture(skySampler, uv) * weight + texture(cloudSampler, uv) * (1.0 - weight);
	FragColor = vec4(finalColor.xyz, 1.0);
}