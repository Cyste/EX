11-
#define PI 3.14159265359

#ifdef VERTEX_PROGRAM

layout (location = 0) in vec2 in_position;

out vec2 var_texcoord;

void main() {
    var_texcoord = in_position * 0.5 + 0.5;
    gl_Position = vec4(in_position, 0.0f, 1.0f);
}

#endif

#ifdef PIXEL_PROGRAM

in vec2 var_texcoord;

uniform sampler2D color_map;
uniform sampler2D light_map;

out vec4 out_color;

void main() {
    out_color = vec4(texture(light_map, var_texcoord).rgb, 1.0f);
	
	vec3 diffuse_color = texture(color_map, var_texcoord).rgb;
	
	vec4 light = texture(light_map, var_texcoord);
	
	vec3 diffuse_light = light.rgb;
	
    float specular = light.a;
	
	out_color = vec4(diffuse_color * diffuse_light, 1.0f);// + max(0.0f, specular), 1.0f);
}

#endif