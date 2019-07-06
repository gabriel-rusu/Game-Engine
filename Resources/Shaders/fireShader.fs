precision mediump float;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform float u_Time;
uniform float u_DispMax;
varying vec2 v_uv;
varying vec2 v_uv2;

void main()
{
    vec2 disp = texture2D(u_texture2, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 offset= (2.0*disp - 1.0)*u_DispMax; 
	vec2 v_uv_displaced=v_uv+offset;
	vec4 c_fire = texture2D(u_texture1,v_uv_displaced);
	vec4 c_alpha = texture2D(u_texture0,v_uv);
	c_fire.a = c_alpha.r * c_fire.a;
	if(c_fire.a < 0.01)
        discard;
	gl_FragColor = c_fire;
 }