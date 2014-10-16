struct PixelShaderInput
{
    float3 color : COLOR;
};

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main(PixelShaderInput input)
{
    PixelShaderOutput output; 
    output.color.rgba = float4(input.color.r, 0.0f, 0.0f, 0.5f);
    return output;
}