require("camera")
require("SkyBox")

ClearScreen(0.5, 0.5, 0.5);

boxDrawable = BasicDrawableObject({[Keys["ModelFile"]]        = "Assets/PlyFiles/1x1_2Tri_Quad_2_Sided.ply",
                                   [Keys["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                   [Keys["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_1_Texture.fx",});

tilesTexture = BasicTexture(0, "Assets/Texture/Tiles.png");

box1 = Object();
box1.Scale = Vector4(20.0, 20.0, 20.0);
box1:SetGraphic(boxDrawable);
box1:SetTexture(tilesTexture);