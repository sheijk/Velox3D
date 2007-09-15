uniform sampler2D moonTex;
uniform float v3d_TimeFraction60;


void main(void)
{
  const float timeFactor = 10.0;
  gl_FragColor = texture2D(moonTex, gl_TexCoord[0].st);
}
