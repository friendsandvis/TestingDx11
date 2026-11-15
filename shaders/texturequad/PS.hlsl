
Texture2D<float4> MainTexture: register(t1);
SamplerState MainSampler: register(s0);
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
	return MainTexture.Sample(MainSampler, psin.uv.xy);//float4(psin.uv.xy,1.0f,1.0f);
}