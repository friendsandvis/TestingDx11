
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
	return float4(psin.uv.x,psin.uv.y,1.0f,1.0f);//psOutCol;//float4(0.0f,0.0f,1.0f,1.0f);
}