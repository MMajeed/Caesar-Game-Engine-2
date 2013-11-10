local SkyBox = {}

skyBoxDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = "Assets/PlyFiles/Sphere_Smooth.ply",
                                      [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                      [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_5_SkyMap.fx",
                                      [Keys["BasicDrawable"]["CullMode"]]         = CullMode["None"],
                                      [Keys["BasicDrawable"]["FillMode"]]         = FillMode["Solid"],
                                      [Keys["BasicDrawable"]["Antialiasedline"]]  = true,
                                      [Keys["BasicDrawable"]["MultisampleEnable"]]= true,});

skyBoxTexture = BasicTexture(5, "Assets/Texture/Sky/Sky.dds");


skyBoxObject = Object();
skyBoxObject.Scale = Vector4(2000.0, 2000.0, 2000.0);
skyBoxObject:SetGraphic(skyBoxDrawable);
skyBoxObject:SetTexture(skyBoxTexture);

return SkyBox