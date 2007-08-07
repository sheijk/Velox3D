varying float intensity;
uniform sampler2D cloud;
uniform sampler2D sun;
uniform float v3d_TimeFraction60;
void main(void)
{
  const float cutOff = 0.0;
  const float cutOffX = 0.0;
  vec3 skyColor = vec3((1.0 - intensity),
			 (1.0 - intensity),
			 intensity);

  vec2 texCoords = gl_TexCoord[0].x;
  texCoords[1] = gl_TexCoord[0].y;
  
  texCoords[0] +=(v3d_TimeFraction60);
  
  if(texCoords[0] > 1.0)
  {
    texCoords[0] = texCoords[0] -1.0;
    //gl_FragColor = vec4(texCoords[0],0,0,1);
    //return;
  }
 


  vec3 cloud = texture2D(cloud, texCoords);
  vec3 sun = texture2D(sun, gl_TexCoord[0]);

  skyColor[0] = skyColor[0] + (sun[0]);
  skyColor[1] = skyColor[1] + (sun[1]);
  skyColor[2] = skyColor[2] + (sun[2]);
  
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
