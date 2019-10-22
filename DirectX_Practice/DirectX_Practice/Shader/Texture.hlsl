//�O���[�o��
Texture2D g_texDecal : register(t0); //�e�N�X�`���[�� ���W�X�^�[t(n)
SamplerState g_samLinear : register(s0); //�T���v���[�̓��W�X�^�[s(n)

cbuffer global
{
    matrix gWP; //���[���h����ˉe�܂ł̕ϊ��s��
    float4 gColor;
    float4 gUV;
};

//�\����
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//
//�o�[�e�b�N�X�V�F�[�_�[
//
VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.Pos = mul(Pos, gWP);
    output.Tex = Tex * float2(gUV.z, gUV.w) + float2(gUV.x, gUV.y);

    return output;
}

//
//�s�N�Z���V�F�[�_�[
//
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color = g_texDecal.Sample(g_samLinear, input.Tex);
    color *= gColor;
    return color;
}