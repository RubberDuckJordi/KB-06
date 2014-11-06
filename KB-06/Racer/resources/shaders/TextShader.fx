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


VS_OUTPUT TextShader( in float4 vPosition : POSITION,
	float2 vTexCoord0 : TEXCOORD0 )
{
	VS_OUTPUT Output;
	
    //float fSin, fCos;   
    //float x = length( vPosition ) * sin( g_fTime ) * 15.0f;
    
    // This HLSL intrinsic computes returns both the sine and cosine of x
    //sincos( x, fSin, fCos );

	// Change the y of the vertex position based on a function of time 
	// and transform the vertex into projection space. 
    Output.Position = float4(1,1,1,1);//mul( float4( vPosition.x, vPosition.y, vPosition.z, 1.0f ), g_mWorldViewProjection);
    
    // Output the diffuse color as function of time and 
    // the vertex's object space position
    Output.Diffuse = 1;//0.5f - 0.5f * fCos;
    
//    Output.TextureUV = vTexCoord0;

    
    return Output;
};


// pixel shader

struct PS_OUTPUT
{
	float4 RGBColor : COLOR0;  // Pixel color    
};


PS_OUTPUT RainbowShader(VS_OUTPUT In)
{
	
	PS_OUTPUT Output;
	Output.RGBColor = In.Diffuse; //tex2D(MeshTextureSampler, In.TextureUV) * In.Diffuse;
	return Output;
};



//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
	

	pass P1
	{
		VertexShader = compile vs_2_0 TextShader();
		PixelShader = compile ps_2_0 RainbowShader();
		//CullMode = CCW;
	}
}
