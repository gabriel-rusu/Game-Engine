precision mediump float;
vec4 v_color;
vec4 c_blend;
vec4 c_rock;
vec4 c_dirt;
vec4 c_grass;
vec4 c_final;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform float razaMare;
uniform float razaMica;
uniform vec3 fogColor;
uniform vec3 cameraPosition;
varying vec3 v_pos;

void main()
{
	c_blend = texture2D(u_texture3, v_uv2);
	c_dirt = texture2D(u_texture0,v_uv);
	c_rock = texture2D(u_texture1,v_uv);
	c_grass = texture2D(u_texture2,v_uv);
	

	c_final = c_blend.r*c_rock + c_blend.g*c_grass + c_blend.b*c_dirt;
	c_final.a = 1.0;
	gl_FragColor =c_final;
	float d = distance(v_pos,cameraPosition);
	float alpha;
	if(d <= razaMica)
		alpha=0.0;
	else if(d >= razaMare)
		alpha = 1.0;
	else alpha = (d-razaMica)/(razaMare-razaMica);
	 c_final = vec4(alpha * fogColor + (1.0-alpha) * c_final.xyz,1.0);
	gl_FragColor =  c_final;
 }