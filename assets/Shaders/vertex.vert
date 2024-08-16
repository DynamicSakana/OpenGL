#version 460 core
in vec3 a_pos;
in vec3 a_color;
in vec2 a_uv;

out vec2 uv;
out vec3 color;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
	uv = a_uv;
	color = a_color;
}