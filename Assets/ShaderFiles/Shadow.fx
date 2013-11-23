
SamplerState sam
{
	Filter = MAXIMUM_ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
};

bool IsInShadow(float4 lightPos, LightDesc L)
{
	lightPos.xyz /= lightPos.w;

	float4 depthTexture = Shadow.Sample(sam, float3(lightPos.xy, L.ShadowNum));

	if(lightPos.x < 1.0f && lightPos.y < 1.0f
		&& lightPos.x > 0.0f && lightPos.y > 0.0f)
	{
		bool depthWithin = (lightPos.z - depthTexture.x) >= 0.0001;

		return depthWithin;
	}
	else
	{
		return false;
	}
}