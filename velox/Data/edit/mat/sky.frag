varying float intensity;
uniform sampler2D cloudTex;
uniform sampler2D sunTex;
uniform sampler2D starTex;
uniform float v3d_TimeFraction60;

/**
 * Time independant function
 */
vec3 getSkyBaseColor()
{
  const float skyExtinction = 1.2;
  vec3 skyColor = vec3((1.0 - intensity),
		       (1.0 - intensity),
		       intensity);
  //skyColor *= (skyExtinction - v3d_TimeFraction60);
  return skyColor;
}

vec3 getCloudColor()
{
  const float cloudTrans = 0.4;
  const float timeCloudFactor = 5.0;
  const float cutOffY = 0.0;
  const float cutOffX = 0.0;
  const float edgeFallOff = 0.015;

  vec3 cloudColor;
  vec2 cloudCoords = gl_TexCoord[0].xy;
  cloudCoords += v3d_TimeFraction60 * timeCloudFactor;

  if(cloudCoords[0] < 0.0)
  {
    cloudCoords[0] = cloudCoords[0] *-1.0;
  }
  if(cloudCoords[1] < 0.0)
  {
    cloudCoords[1] = cloudCoords[1] *-1.0;
  }
  if(cloudCoords[0] > 1.0)
  {
    cloudCoords[0] = cloudCoords[0] - floor(cloudCoords[0]);
  }
  if(cloudCoords[1] > 1.0)
  {
    cloudCoords[1] = cloudCoords[1] - floor(cloudCoords[1]);
  }
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
	    cloudColor += cloud * intensity * intensity * cloudTrans;
	    cloudColor *= sin(1.0-gl_TexCoord[0].z) - edgeFallOff;
	  }
	}
      }
    }
  }
  return cloudColor;
}

vec3 getSunColor()
{
  const vec2 sunDirection = vec2(0.0,0.0);
  const float sunTrans = 0.9;
  const float sunRiseAngle = 0.0;
  const float sunScale = 0.8;

  vec3 sunColor;
  vec2 sunCoords = gl_TexCoord[0].xy - sunRiseAngle;
  float angle = 3.14 * v3d_TimeFraction60;
  
  if(v3d_TimeFraction60 < 0.5)
    sunCoords.x -= (sin(angle));
  else
    sunCoords.x += (sin(angle));
      
      
  if( sunTrans > 0.0 )
  {
    vec2 texLookUp = smoothstep(sunScale, (1.0 - sunScale), (sunCoords) );
    vec3 sun = texture2D(sunTex, texLookUp);
    sunColor += sun * sunTrans;
  }
  return sunColor;
}

vec3 getStarColor()
{
  vec3 starColor = texture2D(starTex, gl_TexCoord[0]);
  return starColor;
}

void main(void)
{
  const float timeFactor = 10.0;

  vec3 finalColor;

  vec3 skyColor = getSkyBaseColor();
  vec3 sunColor = getSunColor();
  vec3 cloudColor = getCloudColor();
  vec3 starColor = getStarColor();

  vec3 test = vec3(1,1,1);

  finalColor = sunColor + cloudColor;
  float factor = (1.0 - abs(sin(3.14 * v3d_TimeFraction60)));
  finalColor += skyColor * factor;
  
  gl_FragColor = vec4(finalColor[0], finalColor[1], finalColor[2], 1.0);
}
