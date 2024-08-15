#version 460 core
uniform float u_velocity;
uniform float u_time;
in vec3 a_pos;
in vec2 a_uv;

out vec2 uv;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
	uv = vec2(a_uv.x + u_time * u_velocity, a_uv.y);
}