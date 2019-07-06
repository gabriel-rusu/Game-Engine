attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec3 c_blend;
varying vec3 v_color;
uniform mat4 u_rotation;
attribute vec2 a_uv;
attribute vec2 a_uv2;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform vec3 u_height;
uniform sampler2D u_texture3;
varying vec3 v_pos;
uniform mat4 modelM;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	
	v_color = a_color;
	vec4 pos_nou = vec4(a_posL,1.0);
	vec4 c_blend = texture2D(u_texture3,a_uv2);
	pos_nou.y =c_blend.r*u_height.r+c_blend.g*u_height.g+c_blend.b*u_height.b;
	gl_Position = u_rotation*pos_nou;
	v_uv = a_uv;
	v_uv2 = a_uv2;
	v_pos = (modelM *posL).xyz;
}
   