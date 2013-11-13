

bool IsInShadow(float4 lightPos,
				Texture2D depthMap,
				SamplerState shadowSampler)
{
	lightPos.xyz /= lightPos.w;

	float4 depthTexture = depthMap.Sample(shadowSampler, lightPos.xy);

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