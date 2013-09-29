require("camera")
require("SkyBox")

ClearScreen(0.5, 0.5, 0.5);

boxDrawable = BasicDrawableObject({[Keys["ModelFile"]]        = "Assets/PlyFiles/Box2.ply",
                                   [Keys["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                   [Keys["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_1_Texture.fx",});

tilesTexture = BasicTexture(0, "Assets/Texture/Tiles.png");

box1 = Object();
box1.Scale = Vector4(50.0, 0.2, 50.0);
box1:SetGraphic(boxDrawable);
box1:SetTexture(tilesTexture);


sphereDrawable = BasicDrawableObject({[Keys["ModelFile"]]        = "Assets/PlyFiles/Box2.ply",
                                      [Keys["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                      [Keys["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_2_Light.fx",});


for i = 1, 5000, 1 do
    sphereObject = Object();
    if(i % 2 == 0) then
        sphereObject.Location = Vector4((i * 2), 5.0, 00.0)
    else
        sphereObject.Location = Vector4((i * -2), 5.0, 00.0)
    end
    sphereObject:SetGraphic(sphereDrawable);
end