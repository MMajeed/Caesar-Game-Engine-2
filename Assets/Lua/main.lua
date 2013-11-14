require("camera")
require("SkyBox")
require("LightSetup")

ClearScreen(0.5, 0.5, 0.5);

boxDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = "Assets/PlyFiles/Box.ply",
                                   [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                   [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_1_Texture.cso",});

tilesTexture = BasicTexture("Assets/Texture/Tiles.png");


box1 = Object({[Keys["ObjectInfo"]["Scale"]]       = Vector4(50.0, 0.2, 50.0),
               [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(1.0, 1.0, 1.0),
               [Keys["ObjectInfo"]["Ambient"]]     = Vector4(1.0, 1.0, 1.0),
               [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.4, 0.4, 0.4, 0.4),
               [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
               [Keys["ObjectInfo"]["TextureObj"]]  = tilesTexture,});

sphereDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = "Assets/PlyFiles/Sphere_Smooth.ply",
                                      [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                      [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_2_Light.cso",});


for i = 1, 10, 1 do
    local x = ((i % 10) - 5) * 4;
    local y = 2;
    local z = 0;
    local sphereObject = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(x, y, z),
                                 [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58),
                                 [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
                                 [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
                                 [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,});
end

for i = 1, 10, 1 do
    local x = ((i % 10) - 5) * 4;
    local y = 2;
    local z = 20;
    local sphereObject = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(x, y, z),
                                 [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58),
                                 [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
                                 [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
                                 [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,});
end

for i = 1, 10, 1 do
    local x = ((i % 10) - 5) * 4;
    local y = 2;
    local z = -20;
    local sphereObject = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(x, y, z),
                                 [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58),
                                 [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
                                 [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
                                 [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,});
end
  
OnKeyDown(string.byte("A"), 
    function() 
        myTexture = TakeScreenShot({[Keys["BasicScreenCapture"]["Width"]]    = 768,
                                    [Keys["BasicScreenCapture"]["Height"]]   = 1024,});
        box1:SetTexture(myTexture);
    end
);        