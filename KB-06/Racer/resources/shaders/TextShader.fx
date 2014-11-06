//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4 g_mWorldViewProjection;  // World * View * Projection transformation
float g_fTime;			  // Time parameter. This keeps increasing


//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float4 Diffuse    : COLOR0;     // vertex diffuse color
};


VS_OUTPUT TextShader( in float3 vPosition : POSITION )
{
	VS_OUTPUT Output;
	
    float fSin, fCos;   
    float x = length( vPosition ) * sin( .3 * g_fTime ) * 15.0f;
    
    // This HLSL intrinsic computes returns both the sine and cosine of x
    sincos( x, fSin, fCos );

	// Change the y of the vertex position based on a function of time 
	// and transform the vertex into projection space. 
    Output.Position = mul( float4( vPosition.x, fSin * 0.1f, vPosition.y, 1.0f ), g_mWorldViewProjection );
    
    // Output the diffuse color as function of time and 
    // the vertex's object space position
    Output.Diffuse = 0.5f - 0.5f * fCos;
    
    return Output;
}

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
	int red = int(sin(3 * g_fTime + 0) * 128 + 127);
	int green = int(sin(3 * g_fTime + 2) * 128 + 127);
	int blue = int(sin(3 * g_fTime + 4) * 128 + 127);
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

