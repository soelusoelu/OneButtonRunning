//グローバル
Texture2D g_texDecal : register(t0); //テクスチャーは レジスターt(n)
SamplerState g_samLinear : register(s0); //サンプラーはレジスターs(n)

cbuffer global
{
    matrix gWP; //ワールドから射影までの変換行列
    float4 gColor;
    float4 gUV;
};

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//
//バーテックスシェーダー
//
VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.Pos = mul(Pos, gWP);
    output.Tex = Tex * float2(gUV.z, gUV.w) + float2(gUV.x, gUV.y);

    return output;
}

//
//ピクセルシェーダー
//
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = g_texDecal.Sample(g_samLinear, input.Tex);
    color *= gColor;
    return color;
}