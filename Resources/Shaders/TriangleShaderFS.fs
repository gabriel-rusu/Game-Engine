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
uniform vec3 pozitieLumina;
uniform vec3 culoareSpeculara;
uniform vec3 culoareDifuza;
uniform vec3 ambinetalLight;
uniform float ratio;
uniform float specPower;
vec3 N;
vec3 L;
varying vec3 v_norm;

void main()
{
	N = normalize(v_norm);
	L =normalize( v_pos - pozitieLumina);
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
	vec3 comp_amb = color.xyz * ambinetalLight;
	vec3 c_diff = color.xyz*culoareDifuza * max(dot(N,-L),0.0);
	vec3 R = normalize(reflect(L,N));
	vec3 E = normalize(cameraPosition - pozitieLumina);
	vec3 c_spec = culoareSpeculara * pow(max(dot(R,E),0.0),specPower);
	vec3 c_final = ratio*comp_amb + (1.0-ratio)*(c_diff - c_spec);
	gl_FragColor = vec4(c_final,color.a);
	gl_FragColor = vec4(ambinetalLight,1.0);
 }
