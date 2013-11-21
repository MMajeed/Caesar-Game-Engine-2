require("camera")
require("SkyBox")
require("LightSetup")

ClearScreen(0.5, 0.5, 0.5);

boxDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = "Assets/PlyFiles/Box.ply",
                                   [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                   [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
tilesTexture = BasicTexture("Assets/Texture/Tiles.png");


box1 = Object({[Keys["ObjectInfo"]["Scale"]]       = Vector4(50.0, 0.2, 50.0),
               [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.5, 0.5, 0.5),
               [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.1, 0.1, 0.1),
               [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.01, 0.01, 0.01, 0.001),
               [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
               [Keys["ObjectInfo"]["Texture2DObj"]]= tilesTexture,});

sphereDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = "Assets/PlyFiles/Sphere_Smooth.ply",
                                      [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                      [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});


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
  
myTexture = nil;
                                 
OnKeyDown(string.byte("A"), 
    function() 
        
        myTexture = TakeScreenShot({[Keys["ScreenCapture"]["Width"]]        = 1024,
                                    [Keys["ScreenCapture"]["Height"]]       = 1024,
                                    [Keys["ScreenCapture"]["CameraMatrix"]] = ViewCalculation(cam.Eye, cam.TargetMagintude, cam.Up, cam.Pitch, cam.Yaw, cam.Roll), });
        box1:RemoveAll2DTexture();
        box1:Set2DTexture(myTexture);
    end
);


mirrorSphereDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = "Assets/PlyFiles/Sphere_Smooth.ply",
                                            [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                            [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
                                      
local mirrorSphere1 = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(40, 20, 0),
                              [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58),
                              [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
                              [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
                              [Keys["ObjectInfo"]["DrawableObj"]] = mirrorSphereDrawable,
                              [Keys["ObjectInfo"]["Scale"]]       = Vector4(10.0, 10.0, 10.0),
                              [Keys["ObjectInfo"]["Light"]]       = false,});

myTexture1 = CubeScreenCapture({[Keys["ScreenCapture"]["Width"]]   = 1024,
                               [Keys["ScreenCapture"]["Height"]]   = 1024,
                               [Keys["ScreenCapture"]["Eye"]]      = mirrorSphere1.Location, });
mirrorSphere1:SetCubeTexture(myTexture1:GetTexture());

local mirrorSphere2 = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(-40, 20, 0),
                              [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58),
                              [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
                              [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
                              [Keys["ObjectInfo"]["DrawableObj"]] = mirrorSphereDrawable,
                              [Keys["ObjectInfo"]["Scale"]]       = Vector4(10.0, 10.0, 10.0),
                              [Keys["ObjectInfo"]["Light"]]       = false,});

myTexture2 = CubeScreenCapture({[Keys["ScreenCapture"]["Width"]]   = 1024,
                               [Keys["ScreenCapture"]["Height"]]   = 1024,
                               [Keys["ScreenCapture"]["Eye"]]      = mirrorSphere2.Location, });
mirrorSphere2:SetCubeTexture(myTexture2:GetTexture());