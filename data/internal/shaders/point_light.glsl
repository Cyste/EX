11-
#define PI 3.14159265359


#ifdef VERTEX_PROGRAM

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;

uniform mat4 proj_view;
uniform mat4 world;

out vec4 var_screen_position;
out mat4 var_inverse_matrix;
out vec2 var_texcoord;

void main() {
	var_inverse_matrix = inverse(proj_view); //inverse(projView);
	var_texcoord = vec2(in_texcoord.x, 1.0f - in_texcoord.y);
    gl_Position = proj_view * world * vec4(in_position, 1.0f);
    var_screen_position = gl_Position;
}

#endif

#ifdef PIXEL_PROGRAM

in vec4 var_screen_position;
in mat4 var_inverse_matrix;
in vec2 var_texcoord;

uniform sampler2D color_map;
uniform sampler2D normal_map;
uniform sampler2D depth_map;
uniform sampler2D position_map;

uniform samplerCube shadow_map;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform float light_radius;
uniform vec3 camera_position;
uniform mat4 inv_proj_view;

out vec4 color;

void main()
{
    vec4 screen_pos = var_screen_position;	
	screen_pos.xyz /= screen_pos.w;
	
	vec2 texcoord = vec2(screen_pos.x, screen_pos.y) * 0.5 + 0.5;
	
	vec4 normal_data = texture(normal_map, texcoord);
	
    vec3 normal = normal_data.rgb * 2.0f - 1.0f;
	
	float specular_power = normal_data.a * 255.0f;
	
	float specular_intensity = texture(color_map, texcoord).a;
	
	float depth = texture(depth_map, texcoord).r;// * 2.0f - 1.0f;
	float n = 1.0;                                
	float f = 10.0;                               
	float c = (2.0 * n) / (f + n - depth * (f - n));
	
	//color = vec4(c, 0.0f, 0.0f, 0.0f);
	//return;
	
	
    vec4 pos;
	pos.xy = screen_pos.xy;
	pos.z = depth * 2.0f - 1.0f;
	pos.w = 1.0f;
	pos = inv_proj_view * pos;
	pos.xyz /= pos.w;
	
	vec3 light_vector = light_pos - pos.xyz;
	
	float attenuation = clamp(1.0f - length(light_vector) / light_radius, 0.0f, 1.0f); 
	
	attenuation = 1.0 - cos(attenuation * PI * 0.5);
	
	float s = 1.0f;
	
	/*
	if (length(lightVector) > shadow)
		s = 0.0f;
	*/
	
	light_vector = normalize(light_vector); 
	
	float ndotl = dot(normal, light_vector);
	
	if (ndotl <= 0) {
		discard;
	}
	
	vec3 diffuse_light = ndotl * light_color * s;
	
	vec3 reflection_vector = normalize(reflect(-light_vector, normal));
	
	vec3 dir_to_camera = normalize(camera_position - pos.xyz);
	
	float specular_light = specular_intensity * pow( clamp(dot(reflection_vector, dir_to_camera), 0.0f, 1.0f), specular_power);
	
	color = attenuation * vec4(diffuse_light.rgb, specular_light);
}

#endif