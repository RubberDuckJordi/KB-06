//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 g_mWorldViewProjection;  // World * View * Projection transformation
float g_fTime;			  // Time parameter. This keeps increasing
texture g_MeshTexture;            // Color texture for mesh


//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Position   : POSITION;   // vertex position
	float2 TextureUV  : TEXCOORD1;  // vertex texture coords 
};

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

VS_OUTPUT TextWiggleShader(float4 vPosition : POSITION,
	 float2 vTexCoord0 : TEXCOORD0)
{
	VS_OUTPUT Output;

	float x = length( vPosition ) * (.3 * g_fTime) * 15.0f;

	Output.Position = mul( float4( vPosition.x, vPosition.y + (sin(x) * 0.1f), vPosition.z, 1.0f ), g_mWorldViewProjection );

	Output.TextureUV = vTexCoord0;

	return Output;
}


//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
	pass P0
	{
		VertexShader = compile vs_2_0 TextWiggleShader();
	}
}