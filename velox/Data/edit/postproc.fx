
float4x4 mvp : ModelViewProjection;

float4 vertex(
	float4 pos : POSITION,
	float4 inCol : COLOR,
	float4 out outCol : COLOR,
	float out x) 
	: POSITION
{
//	outCol = inCol;
	outCol = float4(1, .5, 0, 1);
//	outCol = float4(.5, .5, .5, 1);
	x = pos.x * 5;
//	outCol = float4(0, sin(pos.x*2), 0, 1);
    return mul(mvp, pos);
}

float4 fragment(float4 color : COLOR, float x) : COLOR 
{
	float4 res = color * (1 + abs(sin(x)))/2;
//	res.y = abs(sin(x));
	return res;
//	return (float4(1, 0, 0, 1) + color)/2;
}

float4 flatFragment(float4 inCol : COLOR, float x) : COLOR
{
	return float4(1, 0, 0, 1);
}

technique flat {
	pass p0 {
        VertexProgram = compile arbvp1 vertex();
        FragmentProgram = compile arbfp1 fragment();
	}
}

technique fallback {
	pass p0 {
	}
}

//technique VertexProgram {
//    pass p0 {
//        VertexProgram = compile arbvp1 vertex();
//        FragmentProgram = compile arbfp1 fragment();
//    }
//}
