struct VSIn
{
    float3 vpos:POS;
	float2 vuv:VUV;
};

struct VSOut
{
    float4 pos : SV_Position;
    float4 color : COLOUR0;
	float2 uv:UV;
};
cbuffer VertexConstants : register(b1)
{
	float4x4 viewMat;
	float4x4 projMat;
}
VSOut main(VSIn input)
{
    VSOut output;

		
		//input.vpos=input.vpos/float3(1920.0f,1080.0f,1.0f);
		float4x4 vpMat = mul(viewMat,projMat);
		output.pos = mul(vpMat,float4(input.vpos,1.0f));//float4(input.vpos,1.0f);

    output.color =float4(1.0,1.0,1.0,1.0f);
	output.uv=input.vuv;

    return output;
}