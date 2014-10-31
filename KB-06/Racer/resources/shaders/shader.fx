// Authors: Robert & Robert


//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
float4 g_MaterialAmbientColor;      // Material's ambient color
float4 g_MaterialDiffuseColor;      // Material's diffuse color
float3 g_LightDir;                  // Light's direction in world space
float4 g_LightDiffuse;              // Light's diffuse color
texture g_MeshTexture;              // Color texture for mesh

float    g_fTime;                   // App's time in seconds
float4x4 g_mWorld;                  // World matrix for object
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix



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


//--------------------------------------------------------------------------------------
// Vertex shader output structure
//--------------------------------------------------------------------------------------

struct VS_OUTPUT
{
	float4 Position   : POSITION;
	float4 Diffuse    : COLOR0;     // vertex diffuse color (note that COLOR0 is clamped from 0..1)
	float2 TextureUV  : TEXCOORD1;  // vertex texture coords 
};

VS_OUTPUT OutlineVertexShader(float4 vPos : POSITION,
	float3 vNormal : NORMAL,
	float2 vTexCoord0 : TEXCOORD0)
{
	VS_OUTPUT Output;

	// Transform the position from object space to homogeneous projection space
	Output.Position = mul(vPos, g_mWorldViewProjection);
	float4 normal = mul(vNormal, g_mWorldViewProjection);

	Output.Position = Output.Position + (mul(1.5f, normal));

	// Black is fine in this case, 
	Output.Diffuse.rgb = float4(0, 0, 0, 1);
	Output.Diffuse.a = 1.0f;

	// Just copy the texture coordinate through
	Output.TextureUV = vTexCoord0;

	return Output;
}

//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
VS_OUTPUT RenderSceneVS(float4 vPos : POSITION,
	float3 vNormal : NORMAL,
	float2 vTexCoord0 : TEXCOORD0)
{
	VS_OUTPUT Output;
	float3 vNormalWorldSpace;

	// Transform the position from object space to homogeneous projection space
	Output.Position = mul(vPos, g_mWorldViewProjection);

	// Transform the normal from object space to world space    
	vNormalWorldSpace = normalize(mul(vNormal, (float3x3)g_mWorld)); // normal (world space)

	// Calc diffuse color    
	Output.Diffuse.rgb = g_MaterialDiffuseColor * g_LightDiffuse * max(0, dot(vNormalWorldSpace, g_LightDir)) +g_MaterialAmbientColor;
	Output.Diffuse.a = 1.0f;

	// Just copy the texture coordinate through
	Output.TextureUV = vTexCoord0;

	return Output;
}


//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
	float4 RGBColor : COLOR0;  // Pixel color    
};

PS_OUTPUT OutlinePixelShader(VS_OUTPUT In)
{
	PS_OUTPUT Output;
	Output.RGBColor = float4(0, 0, 0, 1);
	return Output;
}

float cartoonify(float input)
{
	if (input < 0.5f)
	{
		return 0.1f;
	}
	if (input < 0.8f)
	{
		return 0.5f;
	}
	return 0.9f;
}

PS_OUTPUT CelPixelShader(VS_OUTPUT In)
{
	In.Diffuse.r = cartoonify(In.Diffuse.r);
	In.Diffuse.g = cartoonify(In.Diffuse.g);
	In.Diffuse.b = cartoonify(In.Diffuse.b);

	PS_OUTPUT Output;
	Output.RGBColor = tex2D(MeshTextureSampler, In.TextureUV) * In.Diffuse;
	return Output;
}

//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
	pass P0
	{
		VertexShader = compile vs_2_0 OutlineVertexShader();
		PixelShader = compile ps_2_0 OutlinePixelShader();
		CullMode = CW;
	}

	pass P1
	{
		VertexShader = compile vs_2_0 RenderSceneVS();
		PixelShader = compile ps_2_0 CelPixelShader();
		CullMode = CCW;
	}
}