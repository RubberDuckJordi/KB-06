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
    output.color.rgba = float4(input.color.rgb, 1.0f);
    return output;
}