

float4 CalculateLight(PS_INPUT input)
{
	float4 returnColor = float4(0.0, 0.0, 0.0, 0.0);

	for(unsigned int index = 0; index < numOfLights; index++)
	{
		if(lightArray[index].Type == 0){ break; } // At the end of the list

		float shadow = 1.0f;


		/*bool isInShadow = lightArray[index].HasShadow && IsInShadow(input.LightShadow[index], Shadow, samShadow);

		if(isInShadow == true)
		{
			shadow = 0.5f;
		}*/

		if(lightArray[index].Type == 1) // Parallel light
		{
			float4 toEyeW = normalize(eye - input.PosWorld);
				float4 lightColor = ComputeDirectionalLight(objectMaterial, lightArray[index],
				input.NormalWorld, toEyeW);

			lightColor *= shadow;
			returnColor += lightColor;
		}
		else if(lightArray[index].Type == 2) // Point
		{
			float4 toEyeW = normalize(eye - input.PosWorld);
				float4 lightColor = ComputePointLight(objectMaterial, lightArray[index],
				input.PosWorld, input.NormalWorld, toEyeW);

			lightColor *= shadow;
			returnColor += lightColor;
		}
		else if(lightArray[index].Type == 3) // Spot
		{
			float4 toEyeW = normalize(eye - input.PosWorld);
				float4 lightColor = ComputeSpotLight(objectMaterial, lightArray[index],
				input.PosWorld, input.NormalWorld, toEyeW);

			lightColor *= shadow;
			returnColor += lightColor;
		}
	}

	return returnColor;
}