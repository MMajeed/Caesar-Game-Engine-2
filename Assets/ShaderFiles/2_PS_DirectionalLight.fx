cbuffer cbObject : register(b0)
{
	float4 CameraEye;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
};

struct PS_INPUT
{
	float4 PosWVP	: SV_POSITION;
	float3 tex		: TEXCOORD0;
};

SamplerState MeshTextureSampler
{
	Filter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

Texture2D LocationTexture : register(t0);
Texture2D NormalTexture : register(t1);
Texture2D DiffuseTexture : register(t2);
Texture2D AmbientTexture : register(t3);
Texture2D SpecularTexture : register(t4);

float4 main(PS_INPUT input) : SV_Target
{
	float4 oLocation = LocationTexture.Sample(MeshTextureSampler, input.tex.xy);
	float4 oNormal = NormalTexture.Sample(MeshTextureSampler, input.tex.xy);
	float4 oDiffuse = DiffuseTexture.Sample(MeshTextureSampler, input.tex.xy);
	float4 oAmbient = AmbientTexture.Sample(MeshTextureSampler, input.tex.xy);
	float4 oSpecular = SpecularTexture.Sample(MeshTextureSampler, input.tex.xy);

	float4 toEye = normalize(CameraEye - oLocation);

	// Initialize outputs.
	float4 ambient = oAmbient * Ambient;
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Add diffuse and specular term, provided the surface is in 
	// the line of site of the light.
	float diffuseFactor = dot(Direction, oNormal);

	// Flatten to avoid dynamic branching.
	[flatten]
	if(diffuseFactor > 0.0f)
	{
		float4 v = reflect(-Direction, oNormal);
			float specFactor = pow(max(dot(v, toEye), 0.0f), oSpecular.w);

		diffuse = diffuseFactor * oDiffuse * Diffuse;
		spec = specFactor * oSpecular * Specular;
	}

	return (ambient + diffuse + spec);
}