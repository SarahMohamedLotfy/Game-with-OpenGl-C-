#version 330 core

in vec3 view;

uniform vec3 sun_direction;
uniform float sun_size;
uniform float sun_halo_size;
uniform float sun_brightness;
uniform vec3 sun_color;
uniform vec3 sky_top_color;
uniform vec3 sky_bottom_color;
uniform float sky_smoothness;


uniform float Scale=0.5;

float RADIUS = Scale;

//softness of our vignette, between 0.0 and 1.0
 float SOFTNESS = 0.35;

  vec2 resolution ;

out vec4 color;

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


    vec3 dir = normalize(view);
    vec3 sky_color = mix(sky_bottom_color, sky_top_color, smoothstep(-sky_smoothness, sky_smoothness, dir.y));
    float sun = smoothstep(1-sun_size-sun_halo_size,1-sun_size, dot(sun_direction, dir));
    vec4 texColor = vec4(sky_color + sun_brightness * sun_color * sun, 1.0f);

   texColor.rgb = mix(texColor.rgb, texColor.rgb * vignette, 0.8);
   color = texColor;
}