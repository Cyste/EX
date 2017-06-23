11-
#define PI 3.14159265359


#ifdef VERTEX_PROGRAM

layout(location = 0) in vec2 in_position;

out vec2 var_texcoord;

void main() {
    var_texcoord = in_position * 0.5 + 0.5;
    gl_Position = vec4(in_position, 0.0f, 1.0f);
}

#endif

#ifdef PIXEL_PROGRAM

in vec2 var_texcoord;

uniform sampler2D color_map;
uniform sampler2D normal_map;

uniform vec3 light_direction;
uniform vec3 light_color;
uniform vec3 camera_position;

out vec4 out_color;

void main()
{
	vec4 color_data = texture(color_map, var_texcoord);
	vec4 normal_data = texture(normal_map, var_texcoord);
	
	float specular_power = normal_data.a * 255.0;
	float specular_intensity = color_data.a;
	
	vec3 normal = normal_data.xyz * 2.0 - 1.0;
	
	float ndotl = dot(normal, -light_direction);
	
	if (ndotl <= 0.0) {
		discard;
	}
	
	out_color = vec4(ndotl * light_color, 0.0);
}

#endif