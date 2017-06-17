11-
#define PI 3.14159265359

#ifdef VERTEX_PROGRAM

layout (location = 0) in vec2 in_position;

out vec2 var_texcoord;

void main() {
    var_texcoord = in_position * 0.5 + 0.5;
	var_texcoord.y = 1.0 - var_texcoord.y;
    gl_Position = vec4(in_position.x, in_position.y, 0.0f, 1.0f);
}

#endif

#ifdef PIXEL_PROGRAM

in vec2 var_texcoord;

out vec4 out_color;

void main() {
    out_color = vec4(var_texcoord.x, var_texcoord.y, 0.0f, 1.0f);
}

#endif