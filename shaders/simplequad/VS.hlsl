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
	float4x4 modelMat;
}
VSOut main(VSIn input)
{
    VSOut output;
		float4x4 mvpMat = mul(mul(modelMat,viewMat), projMat);
		output.pos = mul(float4(input.vpos,1.0f), mvpMat);

    output.color =float4(1.0,1.0,1.0,1.0f);
	output.uv=input.vuv;

    return output;
}