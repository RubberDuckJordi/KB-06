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
    output.color.rgba = float4(1.0f, 0.0f, 0.0f, 1.0f);
    return output;
}