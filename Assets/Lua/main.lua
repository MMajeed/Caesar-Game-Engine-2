require("camera")
require("SkyBox")
require("LightSetup")

ClearScreen(0.5, 0.5, 0.5);

boxDrawable = BasicDrawableObject({[Keys["ModelFile"]]        = "Assets/PlyFiles/Box.ply",
                                   [Keys["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                   [Keys["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_3_LightNTexture.fx",});

tilesTexture = BasicTexture(0, "Assets/Texture/Tiles.png");

box1 = Object();
box1.Scale = Vector4(50.0, 0.2, 50.0);
box1:SetGraphic(boxDrawable);
box1:SetTexture(tilesTexture);
box1.Diffuse = Vector4(1.0, 1.0, 1.0)
box1.Amibent = Vector4(1.0, 1.0, 1.0)
box1.Specular = Vector4(0.4, 0.4, 0.4, 0.4)

sphereDrawable = BasicDrawableObject({[Keys["ModelFile"]]        = "Assets/PlyFiles/Sphere_Smooth.ply",
                                      [Keys["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                      [Keys["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_2_Light.fx",});


--for i = 1, 10, 1 do
--    local x = ((i % 10) - 5) * 4;
--    local y = 2;
--    local z = 0;
--    sphereObject = Object();
--    sphereObject.Location = Vector4(x, y, z);
--    sphereObject.Diffuse = Vector4(0.51, 0.53, 0.58)
--    sphereObject.Amibent = Vector4(0.5, 0.5, 0.5)
--    sphereObject.Specular = Vector4(0.5, 0.5, 0.5, 0.5)
--    sphereObject:SetGraphic(sphereDrawable);
--end

for i = 1, 10, 1 do
    local x = ((i % 10) - 5) * 4;
    local y = 2;
    local z = 20;
    sphereObject = Object();
    sphereObject.Location = Vector4(x, y, z);
    sphereObject.Diffuse = Vector4(0.51, 0.53, 0.58)
    sphereObject.Amibent = Vector4(0.4, 0.4, 0.4)
    sphereObject.Specular = Vector4(0.3, 0.3, 0.3, 0.3)
    sphereObject:SetGraphic(sphereDrawable);
end

--for i = 1, 10, 1 do
--    local x = ((i % 10) - 5) * 4;
--    local y = 2;
--    local z = -20;
--    sphereObject = Object();
--    sphereObject.Location = Vector4(x, y, z);
--    sphereObject.Diffuse = Vector4(0.51, 0.53, 0.58)
--    sphereObject.Amibent = Vector4(0.4, 0.4, 0.4)
--    sphereObject.Specular = Vector4(0.4, 0.4, 0.4, 0.1)
--    sphereObject:SetGraphic(sphereDrawable);
--end