

bool IsInShadow(float4 lightPos,
				Texture2D depthMap,
				SamplerState shadowSampler)
{
	lightPos.xyz /= lightPos.w;

	if(lightPos.x < 1.0f && lightPos.y < 1.0f
		&& lightPos.x > 0.0f && lightPos.y > 0.0f)
	{
		float4 depthTexture = depthMap.Sample( shadowSampler, lightPos.xy);

		bool depthWithin = (lightPos.z - depthTexture.x) >= 0.0001;

		return depthWithin && (depthTexture.x < 0.99f);
	}
	else
	{
		return false;
	}
}