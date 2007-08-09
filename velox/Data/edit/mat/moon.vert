varying float intensity;
void main(void)
{
  const float radius = 20;
  gl_TexCoord[0].x = (gl_Vertex.x +radius) / (2*radius);
  gl_TexCoord[0].y = (gl_Vertex.z +radius) / (2*radius);

  gl_Position = ftransform();
}
