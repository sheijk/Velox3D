float4x4 modelViewProj : ModelViewProjection;

struct vsout {
	float4 pos : POSITION;
	float4 color : COLOR;
};

float4 unitToColor(float4 unit) {
	float4 ret = (unit + float4(1, 1, 1, 0))/2;
	return float4(ret.xyz, unit.w);
}

vsout vertex(float4 pos : POSITION) {
	vsout o;

	pos.y += 2 - pos.z;	
	o.pos = mul(modelViewProj, pos);
	o.color = unitToColor(pos);
//	o.color = pos;
	
	return o;
}

float4 fragment(vsout v) : COLOR {
//	float red = noise(pos.x);

	return v.color;
		
//	float red = sin(.5);
//	return float4(red, 1, 0, 0);
}

technique defaultT {
    pass p0 {
		VertexProgram = compile vp40 vertex();
		FragmentProgram  = compile fp40 fragment();
    }
}
