require("camera")
require("SkyBox")
require("LightSetup")
require("floor")

ClearScreen(0.5, 0.5, 0.5);

sphereDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = "Assets/PlyFiles/Sphere_Smooth.ply",
                                      [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                      [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
for zIndex = 0, 2, 1 do
    for xIndex = 1, 10, 1 do
        local x = ((xIndex % 10) - 5) * 4;
        local y = 2;
        local z = -20 + (zIndex * 20);
        local sphereObject = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(x, y, z),
                                     [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58),
                                     [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
                                     [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
                                     [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,});
    end
end

lightPos = 10.0;
OnKeyDown(string.byte("B"), 
    function()       
      SpotLight({[Keys["Light"]["Diffuse"]]     = Vector4(0.0, 0.0, 1.0),
                 [Keys["Light"]["Ambient"]]     = Vector4(0.1, 0.1, 1.0),
                 [Keys["Light"]["Specular"]]    = Vector4(0.0, 0.0, 1.0),
                 [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, lightPos),
                 [Keys["Light"]["Direction"]]   = Vector4(0.7853, -3.14, -3.14),
                 [Keys["Light"]["Attenuation"]] = Vector4(0.0, 0.1, 0.0),
                 [Keys["Light"]["Spot"]]        = 0.5,
                 [Keys["Light"]["Range"]]       = 20,});
      lightPos = lightPos - 10.0;
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