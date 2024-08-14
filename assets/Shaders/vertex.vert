#version 460 core
// layout (location = 0) in vec3 pos;
// layout (location = 1) in vec3 acolor;
uniform float u_time;
in vec3 a_pos;
in vec3 a_color;
out vec3 color;
void main()
{
    gl_Position = vec4(a_pos, 1.0);
	color = a_color * (sin(u_time) + 1) / 2;
}

// #version 460 core
// // layout (location = 0) in vec3 pos;
// // layout (location = 1) in vec3 acolor;
// in vec3 a_pos;
// in vec3 a_color;
// out vec3 color;
// void main()
// {
//     gl_Position = vec4(a_pos, 1.0);
// 	color = a_color;
// }