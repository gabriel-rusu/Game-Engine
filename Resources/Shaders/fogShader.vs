attribute vec3 a_posL;
attribute vec3 a_color;
varying vec3 v_color;
uniform mat4 u_rotation;
attribute vec2 a_uv;
varying vec2 v_uv;
uniform sampler2D u_texture3;


void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	
	
}