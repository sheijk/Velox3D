varying float intensity;
void main(void)
{
  const float radius = 8000.0;
  
  intensity        = gl_Vertex.y / 4000.0;
  intensity        = exp(clamp(intensity, 0.0, 1.0))/1.8;
  //intensitySqrd    = intensity*intensity;
  
  gl_TexCoord[0].x = (gl_Vertex.x +radius) / (2*radius);
  gl_TexCoord[0].y = (gl_Vertex.z +radius) / (2*radius);
  gl_TexCoord[0].z = 1.0 - (gl_Vertex.y / radius);
  //gl_TexCoord[0].z = sin(gl_TexCoord[0].z);
  gl_Position = ftransform();
}
