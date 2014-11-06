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


VS_OUTPUT TextShader( in float2 vPosition : POSITION )
{
	VS_OUTPUT Output;
	
    float fSin, fCos;   
    float x = length( vPosition ) * sin( fTime ) * 15.0f;
    
    // This HLSL intrinsic computes returns both the sine and cosine of x
    sincos( x, fSin, fCos );

	// Change the y of the vertex position based on a function of time 
	// and transform the vertex into projection space. 
    Output.Position = mul( float4( vPosition.x, fSin * 0.1f, vPosition.y, 1.0f ), mWorldViewProj );
    
    // Output the diffuse color as function of time and 
    // the vertex's object space position
    Output.Diffuse = 0.5f - 0.5f * fCos;
    
    return Output;
}


