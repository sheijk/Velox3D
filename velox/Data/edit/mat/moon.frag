uniform sampler2D moonTex;
uniform float v3d_TimeFraction60;


void main(void)
{
  const float timeFactor = 10.0;
  

  vec3 finalColor = texture2D(moonTex, gl_TexCoord[0]);
  gl_FragColor = vec4(finalColor[0], finalColor[1], finalColor[2], 1.0);
}
