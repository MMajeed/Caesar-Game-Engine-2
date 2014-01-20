SamplerState samAnisotropic
{
	Filter = MAXIMUM_ANISOTROPIC;
	AddressU = Wrap;
	AddressV = Wrap;
	AddressW = Wrap;
};

float4 Calculate2DTexture(float2 texCoordinate)
{
	float4 returnColor = float4(0.0, 0.0, 0.0, 0.0);

	[unroll]
	for(unsigned int i = 0; i < NumberOf2DTextures; ++i)
	{
		returnColor += ObjectTextures2D[i].Sample(samAnisotropic, texCoordinate);
	}

	return returnColor;
}

float4 CalculateCubeTexture(float3 texCoordinate)
{
	float4 returnColor = float4(0.0, 0.0, 0.0, 0.0);

	[unroll]
	for(unsigned int i = 0; i < NumberOfCubeTextures; ++i)
	{
		returnColor += ObjectTexturesCube[i].Sample(samAnisotropic, texCoordinate);
	}

	return returnColor;
}