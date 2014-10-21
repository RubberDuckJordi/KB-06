float magic = 0;

struct PixelShaderInput
{
    float4 color : COLOR;
};

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(PixelShaderInput input)
{
    PixelShaderOutput output; 
	output.color.rgba = float4(input.color.r + magic, input.color.g + magic, input.color.b + magic, input.color.a);
    return output;
}