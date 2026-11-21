
Texture2D<float4> diffuseTexture: register(t0);
Texture2D<float4> normalTexture: register(t1);
Texture2D<float4> roughnessTexture: register(t2);
SamplerState LinearSampler: register(s0);

struct Vout
{
	float4 opos:SV_Position;
	float4 vcol : COLOUR0;
	float2 uv:UV;
};
cbuffer testConstants : register(b0)
{
	float4 psOutCol;
}
float4 main(Vout psin) : SV_TARGET0
{
	float4 diffuseCol = diffuseTexture.Sample(LinearSampler, psin.uv.xy);
	return float4(diffuseCol.xyz,1.0f);//float4(0.0f,1.0f,0.0f,1.0f);
}