varying float intensity;
uniform sampler2D cloudTex;
uniform sampler2D sunTex;
uniform float v3d_TimeFraction60;

void main(void)
{
  const vec2 sunDirection = vec2(0.0,0.0);
  const vec2 cloudDirection = vec2(0.5, 0.2);
  const float cloudTrans = 0.8;
  const float sunTrans = 1.15;
  const float cutOffY = 0.0;
  const float cutOffX = 0.0;
  const float sunScale = 0.4;
  const float timeFactor = 1.0;
  const float timeCloudFactor = 5.0;
  const float edgeFallOff = 0.015;

  vec3 skyColor = vec3((1.0 - intensity),
		       (1.0 - intensity),
		       intensity);

  vec2 cloudCoords = gl_TexCoord[0].xy;
  cloudCoords += v3d_TimeFraction60 * timeCloudFactor * cloudDirection;
  
  if(cloudCoords[0] > 1.0)
  {
    cloudCoords[0] = cloudCoords[0] - 1.0;
  }
  if(cloudCoords[1] > 1.0)
  {
    cloudCoords[1] = cloudCoords[1] - 1.0;
  }

  if(gl_TexCoord[0].x > sunScale)
  {
    if(gl_TexCoord[0].y > sunScale)
    {
      if(gl_TexCoord[0].x < (1.0 - sunScale))
      {
	if(gl_TexCoord[0].y < (1.0 - sunScale))
	{
	  vec2 sunCoords = gl_TexCoord[0].xy;
	  sunCoords += sunDirection * (v3d_TimeFraction60) * timeFactor;
	  vec2 sunCoord = smoothstep(sunScale, (1.0 - sunScale), (gl_TexCoord[0].xy) );
	  vec3 sun = texture2D(sunTex, sunCoord);
	  skyColor += sun* sunTrans;
	}
      }
    }
  }
  
  vec3 sunColor = skyColor;
  if( cloudTrans > 0.0 )
  {
    if(gl_TexCoord[0].x > cutOffX)
    {
      if(gl_TexCoord[0].y > cutOffY)
      {
	if(gl_TexCoord[0].x < (1.0 - cutOffX))
        {
	  if(gl_TexCoord[0].y < (1.0 - cutOffY))
	  {
	    vec3 cloud = texture2D(cloudTex, cloudCoords);
	    //cloud *= noise3(cloudCoords); //turn on if available sometime
	    skyColor += cloud * intensity * intensity * cloudTrans;
	    skyColor *= sin(1.0-gl_TexCoord[0].z) - edgeFallOff;
	  }
	}
      }
    }
  }
  skyColor +=sunColor;
  vec4 frag = vec4(skyColor[0], skyColor[1], skyColor[2],1.0);
  gl_FragColor = frag;
  //gl_FragColor = vec4(gl_TexCoord[0].x, gl_TexCoord[0].y, 0, 1);
  //gl_FragColor = vec4(cloud[0],cloud[1],cloud[2], 1);
  //gl_FragColor = vec4(sun[0],sun[1],sun[2], 1);
  //gl_FragColor = vec4(v3d_TimeFraction60, 0,0, 1.0);
}
