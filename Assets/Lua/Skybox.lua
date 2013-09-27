local SkyBox = {}

skyBoxDrawable = BasicDrawableObject({[Keys["ModelFile"]]        = "Assets/PlyFiles/Sphere_Smooth_3.ply",
                                      [Keys["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                      [Keys["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_5_SkyMap.fx",});

skyBoxDrawable:ChangeRastersizerState(CullMode["None"], FillMode["Solid"], true, true);

skyBoxTexture = BasicTexture(5, "Assets/Texture/Sky/Sky.dds");


skyBoxObject = Object();
skyBoxObject.Scale = Vector4(2000.0, 2000.0, 2000.0);
skyBoxObject:SetGraphic(skyBoxDrawable);
skyBoxObject:SetTexture(skyBoxTexture);

return SkyBox

