//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 g_mWorldViewProjection;  // World * View * Projection transformation
float g_fTime;			  // Time parameter. This keeps increasing
texture g_MeshTexture;              // Color texture for mesh
float4x4 g_mWorld;                  // World matrix for object




//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
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


//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float4 Diffuse    : COLOR0;     // vertex diffuse color
    float2 TextureUV  : TEXCOORD1;  // vertex texture coords 
};



VS_OUTPUT TextShader( in float3 vPosition : POSITION )
{
	VS_OUTPUT Output;
	
    float fSin, fCos;   
    float x = length( vPosition ) * sin( .3 * g_fTime ) * 15.0f;

    
    // This HLSL intrinsic computes returns both the sine and cosine of x
    //sincos( x, fSin, fCos );

	// Change the y of the vertex position based on a function of time 
	// and transform the vertex into projection space. 

    Output.Position = mul( float4( vPosition.x, fSin * 0.1f, vPosition.y, 1.0f ), g_mWorldViewProjection );

    
    // Output the diffuse color as function of time and 
    // the vertex's object space position
    Output.Diffuse = 1;//0.5f - 0.5f * fCos;
    
//    Output.TextureUV = vTexCoord0;

    
    return Output;
};

//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
	float4 RGBColor : COLOR0;  // Pixel color    
};

PS_OUTPUT ColorShader()
{
	PS_OUTPUT Output;
	float red = (sin(g_fTime + 0) * (255/2) + (255/2)) / 255;
	float green = (sin(g_fTime + 2) * (255/2) + (255/2)) / 255;
	float blue = (sin(g_fTime + 4) * (255/2) + (255/2)) / 255;
	Output.RGBColor = float4(red, green, blue, 1);
	return Output;
}

//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
	pass P0
	{
		VertexShader = compile vs_2_0 TextShader();
		PixelShader = compile ps_2_0 ColorShader();
		//CullMode = CW;
	}
}

