precision mediump float;
varying vec3 v_color;
uniform sampler2D u_texture0;
varying vec2 v_uv;
vec4 cCeata;
uniform float razaMare;
uniform float razaMica;
uniform vec3 fogColor;
uniform vec3 cameraPosition;
varying vec3 v_pos;

void main()
{
    vec4 color = texture2D(u_texture0,v_uv);
    if(color.a < 0.01)
        discard;
	float d = distance(v_pos,cameraPosition);
	float alpha;
	if(d <= razaMica)
		alpha=0.0;
	else if(d >= razaMare)
		alpha = 1.0;
	else alpha = (d-razaMica)/(razaMare-razaMica);
	color = vec4(alpha * fogColor + (1.0-alpha) * color.xyz,1.0);
	gl_FragColor = color;
 }
