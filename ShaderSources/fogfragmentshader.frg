void main()
{
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	gl_FragColor = mix(color, gl_Fog.color, gl_FogCoord);
}
