varying float intensity;
uniform sampler2D cloudTex;
uniform sampler2D sunTex;
uniform float v3d_TimeFraction60;
void main(void)
{
  const vec2 sunDirection = vec2(0.0,0.0);
  const float cutOff = 0.0;
  const float cutOffX = 0.0;
  const float sunScale = 0.4;
  const float timeFactor = 1.0;
  vec3 skyColor = vec3((1.0 - intensity),
			 (1.0 - intensity),
			 intensity);

  vec2 texCoords = gl_TexCoord[0].xy;
  texCoords[0] +=(v3d_TimeFraction60);
  
  if(texCoords[0] > 1.0)
  {
    texCoords[0] = texCoords[0] - 1.0;
  }

  vec2 sunCoords = gl_TexCoord[0].xy;
  vec3 cloud = texture2D(cloudTex, texCoords);

  sunCoords += sunDirection * (v3d_TimeFraction60) * timeFactor;

  //cloud *= noise3(texCoords); //turn on if available sometime

  if(gl_TexCoord[0].x > sunScale)
  {
    if(gl_TexCoord[0].y > sunScale)
    {
      if(gl_TexCoord[0].x < (1.0 - sunScale))
      {
	if(gl_TexCoord[0].y < (1.0 - sunScale))
	{
	  vec2 sunCoord = smoothstep(sunScale, (1.0 - sunScale), (gl_TexCoord[0].xy) );
	  vec3 sun = texture2D(sunTex, sunCoord);
	  skyColor += sun;
	}
      }
    }
  }
  
  vec3 base = skyColor;
  if(gl_TexCoord[0].x > cutOffX)
  {
    if(gl_TexCoord[0].y > cutOff)
    {
      if(gl_TexCoord[0].x < (1.0 - cutOffX))
      {
	if(gl_TexCoord[0].y < (1.0 - cutOff))
	{
	  skyColor[0] = skyColor[0] + (cloud[0])* (intensity*intensity);
	  skyColor[1] = skyColor[1] + (cloud[1])* (intensity*intensity);
	  skyColor[2] = skyColor[2] + (cloud[2])* (intensity*intensity);
	  //skyColor *= 1.0-sin(gl_TexCoord[0].z);

	  skyColor *= sin(1.0-gl_TexCoord[0].z)-0.15;
	}
      }
    }
  }
  
  skyColor +=base;
  vec4 frag = vec4(skyColor[0], skyColor[1], skyColor[2],1.0);
  gl_FragColor = frag;
  //gl_FragColor = vec4(gl_TexCoord[0].x, gl_TexCoord[0].y, 0, 1);
  //gl_FragColor = vec4(cloud[0],cloud[1],cloud[2], 1);
  //gl_FragColor = vec4(sun[0],sun[1],sun[2], 1);
  //gl_FragColor = vec4(v3d_TimeFraction60, 0,0, 1.0);
}