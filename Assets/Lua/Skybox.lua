local SkyBox = {}

skyBoxDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = LoadModel("Assets/Models/Sphere_Smooth.ply"),
                                      [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                      [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_5_SkyMap.cso",
                                      [Keys["BasicDrawable"]["CullMode"]]         = CullMode["Front"],
                                      [Keys["BasicDrawable"]["FillMode"]]         = FillMode["Solid"],});

skyBoxTexture = BasicTexture("Assets/Texture/Sky/Sky.dds");

skyBoxObject = Object({[Keys["ObjectInfo"]["Scale"]]          = Vector4(2000.0, 2000.0, 2000.0),
                       [Keys["ObjectInfo"]["DrawableObj"]]    = skyBoxDrawable,
                       [Keys["ObjectInfo"]["TextureCubeObj"]] = skyBoxTexture,
                       [Keys["ObjectInfo"]["Light"]]          = false,
                       [Keys["ObjectInfo"]["Shadow"]]         = false,});
return SkyBox