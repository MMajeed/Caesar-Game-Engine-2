// This is used to specify what the material property of the light and objects are
struct MaterialInfo
{
    float4 Diffuse;
	float4 Ambient;
    float4 Specular;
};

struct LightDesc
{
	float4 Position;			// Only used with point and spot
	float4 Direction;			// Only used with directional(parallel) and spot
	MaterialInfo material;		// ambient, diffuse, spec
	float4 Att;
	float Spot;
	float Range;
	int Type;
	int HasShadow;
	matrix lightView;
	matrix lightProject;
};

//---------------------------------------------------------------------------------------
// Computes the ambient, diffuse, and specular terms in the lighting equation
// from a directional light.  We need to output the terms separately because
// later we will modify the individual terms.
//---------------------------------------------------------------------------------------
float4 ComputeDirectionalLight(MaterialInfo mat, LightDesc L, 
                             float4 normal, float4 toEye)
{
	// Initialize outputs.
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 lightVec = L.Direction;

	// Add ambient term.
	ambient = mat.Ambient * L.material.Ambient;	

	// Add diffuse and specular term, provided the surface is in 
	// the line of site of the light.
	
	float diffuseFactor = dot(lightVec, normal);

	// Flatten to avoid dynamic branching.
	[flatten]
	if( diffuseFactor > 0.0f )
	{
		float4 v         = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);
					
		diffuse = diffuseFactor * mat.Diffuse * L.material.Diffuse;
		spec    = specFactor * mat.Specular * L.material.Specular;
	}

	float4 total = (ambient + diffuse + spec);
	return total;
}

//---------------------------------------------------------------------------------------
// Computes the ambient, diffuse, and specular terms in the lighting equation
// from a point light.  We need to output the terms separately because
// later we will modify the individual terms.
//---------------------------------------------------------------------------------------
float4 ComputePointLight(MaterialInfo mat, LightDesc L, float4 pos, float4 normal, float4 toEye)
{
	// Initialize outputs.
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The vector from the surface to the light.
	float4 lightVec = L.Position - pos;
		
	// The distance from surface to light.
	float d = length(lightVec);
	
	// Range test.
	if (d > L.Range)
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
	else
	{
		// Normalize the light vector.
		lightVec /= d;

		// Ambient term.
		ambient = mat.Ambient * L.material.Ambient;

		// Add diffuse and specular term, provided the surface is in 
		// the line of site of the light.

		float diffuseFactor = dot(lightVec, normal);

		// Flatten to avoid dynamic branching.
		[flatten]
		if (diffuseFactor > 0.0f)
		{
			float4 v = reflect(-lightVec, normal);
				float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);

			diffuse = diffuseFactor * mat.Diffuse * L.material.Diffuse;
			spec = specFactor * mat.Specular * L.material.Specular;
		}

		// Attenuate
		float att = 1.0f / dot(L.Att, float4(1.0f, d, d*d, 0.0));

		diffuse *= att;
		spec *= att;

		float4 total = (ambient + diffuse + spec);
			return total;
	}
}

//---------------------------------------------------------------------------------------
// Computes the ambient, diffuse, and specular terms in the lighting equation
// from a spotlight.  We need to output the terms separately because
// later we will modify the individual terms.
//---------------------------------------------------------------------------------------
float4 ComputeSpotLight(MaterialInfo mat, LightDesc L, float4 pos, float4 normal, float4 toEye)
{
	// Initialize outputs.
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The vector from the surface to the light.
	float4 lightVec = L.Position - pos;
		
	// The distance from surface to light.
	float d = length(lightVec);
	
	// Range test.
	if( d > L.Range )
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
	else
	{
		// Normalize the light vector.
		lightVec /= d; 
	
		// Ambient term.
		ambient = mat.Ambient * L.material.Ambient;	

		// Add diffuse and specular term, provided the surface is in 
		// the line of site of the light.

		float diffuseFactor = dot(lightVec, normal);

		// Flatten to avoid dynamic branching.
		[flatten]
		if( diffuseFactor > 0.0f )
		{
			float4 v         = reflect(-lightVec, normal);
			float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);
					
			diffuse = diffuseFactor * mat.Diffuse * L.material.Diffuse;
			spec    = specFactor * mat.Specular * L.material.Specular;
		}
	
		// Scale by spotlight factor and attenuate.
		float spot = pow(max(dot(-lightVec, L.Direction), 0.0f), L.Spot);

		// Scale by spotlight factor and attenuate.
		float att = spot / dot(L.Att, float4(1.0f, d, d*d, 0.0));

		ambient *= spot;
		diffuse *= att;
		spec    *= att;

		float4 total = (ambient + diffuse + spec);
		return total;
	}
}