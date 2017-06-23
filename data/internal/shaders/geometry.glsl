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

uniform vec3 camera_position;

uniform vec3 diffuse;
uniform float roughness;
uniform float metallic;

uniform int bitfield;

out vec4 color1;
out vec4 color2;

 mat3 cotangent_frame(vec3 N, vec3 p, vec2 uv) {
  // get edge vectors of the pixel triangle
  vec3 dp1 = dFdx(p);
  vec3 dp2 = dFdy(p);
  vec2 duv1 = dFdx(uv);
  vec2 duv2 = dFdy(uv);

  // solve the linear system
  vec3 dp2perp = cross(dp2, N);
  vec3 dp1perp = cross(N, dp1);
  vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
  vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

  // construct a scale-invariant frame 
  float invmax = 1.0 / sqrt(max(dot(T,T), dot(B,B)));
  return mat3(T * invmax, B * invmax, N);
}

vec3 perturb(vec3 map, vec3 N, vec3 V, vec2 texcoord) {
  mat3 TBN = cotangent_frame(N, -V, texcoord);
  return normalize(TBN * map);
}

vec3 perturb_normal(vec3 N, vec3 V, vec2 texcoord) {
    vec3 p_dx = dFdx(V);
    vec3 p_dy = dFdy(V);
    
    vec2 tc_dx = dFdx(texcoord);
    vec2 tc_dy = dFdy(texcoord);
    
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    vec3 b = normalize( tc_dy.x * p_dx - tc_dx.x * p_dy );
    
    vec3 n = normalize(N);
    vec3 x = cross(n, t);
    t = cross(x, n);
    t = normalize(t);
    
    x = cross(b, n);
    b = cross(n, x);
    b = normalize(b);
	
    mat3 tbn = mat3(t, b, n);
    vec3 map = (texture(normal_map, texcoord ).xyz * 2.0f - 1.0f);
    return normalize(tbn * map );
}

void main()
{
	color1 = vec4(diffuse, roughness);
	if ((bitfield & COLOR_MAP_BIT) != 0) {
		color1.rgb = texture(color_map, var_texcoord).rgb;
	}
	
	if ((bitfield & NORMAL_MAP_BIT) != 0) {
		// color2 = vec4(perturb_normal(var_normal, normalize(camera_position), var_texcoord) * 0.5 + 0.5, metallic);
		vec3 normal = texture(normal_map, var_texcoord).rgb * 2.0 - 1.0;
		
		color2 = vec4(perturb(normal, var_normal, normalize(camera_position - var_position.xyz / var_position.w), var_texcoord) * 0.5 + 0.5, metallic);
	} else {
		color2 = vec4((var_normal + 1.0f) * 0.5f, metallic);
	}
}

#endif