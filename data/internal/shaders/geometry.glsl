11-
#define PI 3.14159265359

#define COLOR_MAP_BIT  1
#define NORMAL_MAP_BIT 2

#ifdef VERTEX_PROGRAM

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;

uniform mat4 proj_view;
uniform mat4 world;

out vec3 var_normal;
out vec2 var_texcoord;
out vec4 var_position;

void main() {
	var_normal = (world * vec4(normalize(in_normal), 0.0f)).xyz;
	var_texcoord = in_texcoord;
	var_position = world * vec4(in_position, 1.0f);
    gl_Position = proj_view * var_position;
}

#endif

#ifdef PIXEL_PROGRAM

in vec3 var_normal;
in vec2 var_texcoord;
in vec4 var_position;

uniform sampler2D color_map;
uniform sampler2D normal_map;
uniform sampler2D light_map;

uniform vec3 diffuse;
uniform float roughness;
uniform float metallic;

uniform int bitfield;

out vec4 color1;
out vec4 color2;
 
void main()
{
	color1 = vec4(diffuse, roughness);
	if ((bitfield & COLOR_MAP_BIT) != 0) {
		color1.rgb *= texture(color_map, var_texcoord).rgb;
	}
	color2 = vec4((var_normal + 1.0f) * 0.5f, metallic);
}

#endif