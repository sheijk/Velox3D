template <typename VertexStructure>
void VHeightmap<VertexStructure>::CreateCoordinates()
{
	vbool bSwitchSides = false;
	int count = 0;

	for(vint i = 0; i <= Size; i += Stepsize)
	{
		if(bSwitchSides)
		{
			
			for(vint y = Size; y >= 0; y -= Stepsize)
			{
				buffer[count].position.v[0]  = i;
				buffer[count].position.v[1]  = GetHeight(i,y);
				buffer[count].position.v[2]  = y;

				count++;

				buffer[count].position.v[0]  = i + Stepsize;
				buffer[count].position.v[1]  = GetHeight(i + Stepsize, y);
				buffer[count].position.v[2]  = y;
				
				count++;
			}
		}
		else
		{
			for ( vint y = 0; y <= Size; y += Stepsize)
			{
				buffer[count].position.v[0] = i + Stepsize; 
				buffer[count].position.v[1] = GetHeight(i + Stepsize, y); 
				buffer[count].position.v[2]=  y;

				count++;

				buffer[count].position.v[0]  = i;
				buffer[count].position.v[1]  = GetHeight(i, y);
				buffer[count].position.v[2]  = y;

				count++;
			}
		}
		bSwitchSides = !bSwitchSides;
	}
				
}

template <typename VertexStructure>
vint VHeightmap<VertexStructure>::GetHeight(vint in_iX, vint in_iY)
{
	vint x = in_iX % Size;					// Error check our x value
	vint y = in_iY % Size;					// Error check our y value

	return m_pBuffer[x + (y * Size)];
}
template <typename VertexStructure>
vint VHeightmap<VertexStructure>::GetNumElements()
{
	vbool bSwitchSides = false;
	vint count = 0;
	for(vint i = 0; i <= Size; i += Stepsize)
	{
		if(bSwitchSides)
		{
			for(vint y = Size; y >= 0; y -= Stepsize)
			{
				count++;
				count++;
			}
		}
		else
		{
			for ( vint y = 0; y <= Size; y += Stepsize)
			{
				count++;
				count++;
			}
		}
		bSwitchSides = !bSwitchSides;
	}
	return count;
}

template <typename VertexStructure>
void VHeightmap<VertexStructure>::CreateTextureCoordinates()
{
	vbool bSwitchSides = false;
	int count = 0;
	vfloat32 x = 0;
	vfloat32 z = 0;

	for(vint i = 0; i <= Size; i += Stepsize)
	{
		if(bSwitchSides)
		{

			for(vint y = Size; y >= 0; y -= Stepsize)
			{
				x = (vfloat32)i / (vfloat32)Size;
				z = (vfloat32)y / (vfloat32)Size;
				buffer[count].texCoords =
					v3d::graphics::VTexCoord2f(x, -z);
								
				count++;

				x = (vfloat32)(i + Stepsize) / (vfloat32) Size;
				z = (vfloat32)y / (vfloat32)Size;
				buffer[count].texCoords  =
					v3d::graphics::VTexCoord2f(x, -z);
				
				count++;
			}
		}
		else
		{
			for ( vint y = 0; y <= Size; y += Stepsize)
			{
				x = (vfloat32)(i + Stepsize) /(vfloat32)Size; 
				z = (vfloat32)y /(vfloat32)Size;
				
				buffer[count].texCoords  =
					v3d::graphics::VTexCoord2f(x, -z);
				
				count++;

				x = (vfloat32)i / (vfloat32)Size;
				z = (vfloat32)y / (vfloat32)Size;

				buffer[count].texCoords =
					v3d::graphics::VTexCoord2f(x, -z);
				
				count++;
			}
		}
		bSwitchSides = !bSwitchSides;
	}
}