//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 g_mWorldViewProjection;  // World * View * Projection transformation
float g_fTime;			  // Time parameter. This keeps increasing
texture g_MeshTexture;            // Color texture for mesh


sampler MeshTextureSampler =
sampler_state
{
	Texture = < g_MeshTexture > ;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = CLAMP;
	AddressV = CLAMP;
};


// Vertex shader


struct VS_OUTPUT
{
	float4 Position   : POSITION;   // vertex position
	float2 TextureUV  : TEXCOORD1;  // vertex texture coords 
};



VS_OUTPUT TextWiggleShader(float4 vPosition : POSITION,
	 float2 vTexCoord0 : TEXCOORD0)
{
	VS_OUTPUT Output;

	float x = length( vPosition ) * (.3 * g_fTime) * 15.0f;

	Output.Position = mul( float4( vPosition.x, vPosition.y + (sin(x) * 0.1f), vPosition.z, 1.0f ), g_mWorldViewProjection );

	Output.TextureUV = vTexCoord0;

	return Output;
}

//Pixel Shader

struct PS_OUTPUT
{
	float4 RGBColor : COLOR0;  // Pixel color    
};



PS_OUTPUT RainbowColorShader(VS_OUTPUT In)
{
	PS_OUTPUT Output;

	float red = 0;
	float green = 255;
	float blue = 0;

	Output.RGBColor = tex2D(MeshTextureSampler, In.TextureUV) * float4(red, green, blue, 1);

	return Output;
}


// Renders scene


technique RenderScene
{
	pass P0
	{
		VertexShader = compile vs_2_0 TextWiggleShader();
		PixelShader = compile ps_2_0 RainbowColorShader();
	}
}