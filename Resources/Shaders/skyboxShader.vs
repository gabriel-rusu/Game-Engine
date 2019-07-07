attribute vec3 a_posL;
attribute vec3 a_color;
varying vec3 v_color;
uniform mat4 u_rotation;
attribute vec2 a_uv;
varying vec3 v_coord;
void main()
{
v_coord = a_posL;
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_rotation*posL;
v_color = a_color;
}
   