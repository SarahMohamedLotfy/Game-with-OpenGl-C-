#version 330 core

in Interpolators {
    vec2 uv;
    vec3 view;
    vec3 normal;
} fs_in;

in vec2 vUV;

struct Material {
    sampler2D ambient_occlusion;
    sampler2D emissive;
    sampler2D albedo;
    sampler2D specular;
    sampler2D roughness;
    vec3 albedo_tint;
    vec3 specular_tint;
    float roughness_scale;
    vec3 emissive_tint;
    //TODO: Complete The Material Struct. Find the variable names in the scene code. 
};
uniform Material material;

uniform float Scale=0.5;

float RADIUS = Scale;

//softness of our vignette, between 0.0 and 1.0
 float SOFTNESS = 0.35;

  vec2 resolution ;


struct DirectionalLight {
    vec3 color;
    vec3 direction;
};
uniform DirectionalLight light;

uniform vec3 ambient;

out vec4 color;

float lambert(vec3 n, vec3 l){
    return max(0, dot(n,l));
}

float phong(vec3 n, vec3 l, vec3 v, float shininess){
    //TODO: Change Model from Phong to Blinn Phong
   
    return pow(max(0, dot(n,normalize(l+v))), shininess);
}

void main()
{

    resolution =  vec2(1280.0,720.0);
	
		
	//determine center position
	vec2 position = (gl_FragCoord.xy / vec2(1280.0,720.0)) - vec2(0.5);
	//position.y = position.y * (resolution.x/resolution.y);
	//determine the vector length of the center position
	float len = length(position);
	
	//use smoothstep to create a smooth vignette
	float vignette = smoothstep(RADIUS, RADIUS - SOFTNESS, len);
    float ao = texture(material.ambient_occlusion, fs_in.uv).r;
    vec3 emissive = material.emissive_tint * texture(material.emissive, fs_in.uv).rgb;
    //TODO: fix albedo, specular and roughness from textures and apply tint and/or scale 
    vec3 albedo = material.albedo_tint * texture(material.albedo, fs_in.uv).rgb;
    vec3 specular = material.specular_tint * texture(material.specular, fs_in.uv).rgb;
    vec3 n = normalize(fs_in.normal);
    float roughness = material.roughness_scale *(texture(material.roughness, fs_in.uv).r+texture(material.roughness, fs_in.uv).g+texture(material.roughness, fs_in.uv).b)/3;
  
    vec3 v = normalize(fs_in.view);
    vec3 l = -light.direction;
    float shininess = 2/pow(max(0.01f,roughness), 2) - 2;
    vec4 texColor  = vec4(
        emissive +
        albedo*ao*ambient + 
        albedo*light.color*lambert(n, l) + 
        specular*light.color*phong(n, l, v, shininess),
        1.0f
    );

   texColor.rgb = mix(texColor.rgb, texColor.rgb * vignette, 0.8);
   color = texColor;
}