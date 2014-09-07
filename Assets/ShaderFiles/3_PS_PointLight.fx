cbuffer cbObject : register(b0)
{
	float4 CameraEye;
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
	float4 Position;
	float4 Attenuation;
	float Range;
	float HasPrivousLight;
};

struct PS_INPUT
{
	float4 PosWVP	: SV_POSITION;
	float3 tex		: TEXCOORD0;
};

Texture2D LocationTexture : register(t0);
Texture2D NormalTexture : register(t1);
Texture2D DiffuseTexture : register(t2);
Texture2D AmbientTexture : register(t3);
Texture2D SpecularTexture : register(t4);
Texture2D PrivousLightTexture : register(t5);

float4 main(PS_INPUT input) : SV_Target
{
	float4 oLocation = LocationTexture.Load(float3(input.PosWVP.xy, 0.0));
	
	// The vector from the surface to the light.
	float4 lightVec = Position - oLocation;

	// The distance from surface to light.
	float d = length(lightVec);

	float4 total;

	// Range test.
	if(d > Range)
		total = float4(0.0, 0.0, 0.0, 1.0);
	else
	{
		float4 oNormal = NormalTexture.Load(float3(input.PosWVP.xy, 0.0));
		float4 oDiffuse = DiffuseTexture.Load(float3(input.PosWVP.xy, 0.0));
		float4 oAmbient = AmbientTexture.Load(float3(input.PosWVP.xy, 0.0));
		float4 oSpecular = SpecularTexture.Load(float3(input.PosWVP.xy, 0.0));

		// Normalize the light vector.
		lightVec /= d;

		// Ambient term.
		float4 ambient = oAmbient * Ambient;
		float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

		// Add diffuse and specular term, provided the surface is in 
		// the line of site of the light.

		float diffuseFactor = dot(lightVec, oNormal);

		// Flatten to avoid dynamic branching.
		[flatten]
		if(diffuseFactor > 0.0f)
		{
			float4 toEye = normalize(CameraEye - oLocation);

			float4 v = reflect(-lightVec, oNormal);
			float specFactor = pow(max(dot(v, toEye), 0.0f), oSpecular.w);

			diffuse = diffuseFactor * oDiffuse * Diffuse;
			spec = specFactor * oSpecular * Specular;
		}

		// Attenuate
		float att = 1.0f / dot(Attenuation, float4(1.0f, d, d*d, 0.0));

		diffuse *= att;
		spec *= att;

		total = (ambient + diffuse + spec);
	}
	
	if(HasPrivousLight != 0)
	{
		total += PrivousLightTexture.Load(float3(input.PosWVP.xy, 0.0));
	}

	return total;
}