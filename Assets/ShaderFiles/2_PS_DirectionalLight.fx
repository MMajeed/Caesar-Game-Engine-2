cbuffer cbObject : register(b0)
{
	float4 Eye;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
	float HasPrivousLight;
};

struct PS_INPUT
{
	float4 PosWVP	: SV_POSITION;
	float3 tex		: TEXCOORD0;
};

SamplerState TextureSampler
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
Texture2D PrivousLightTexture : register(t5);

float4 main(PS_INPUT input) : SV_Target
{
	float4 total = float4(0.0, 0.0, 0.0, 1.0);

	float4 oLocation = LocationTexture.Sample(TextureSampler, input.tex);
	
	if(oLocation.x != -1.0f) // Nothing there, don't bother
	{
		float4 oNormal = NormalTexture.Sample(TextureSampler, input.tex);
		float4 oAmbient = AmbientTexture.Sample(TextureSampler, input.tex);

		float4 toEye = normalize(Eye - oLocation);

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
			float4 oDiffuse = DiffuseTexture.Sample(TextureSampler, input.tex);
				float4 oSpecular = SpecularTexture.Sample(TextureSampler, input.tex);

				float4 v = reflect(-Direction, oNormal);
				float specFactor = pow(max(dot(v, toEye), 0.0f), oSpecular.w);

			diffuse = diffuseFactor * oDiffuse * Diffuse;
			spec = specFactor * oSpecular * Specular;
		}

		total = ambient + diffuse + spec;
	}

	if(HasPrivousLight != 0)
	{
		total += PrivousLightTexture.Sample(TextureSampler, input.tex);
	}

	return total;
}