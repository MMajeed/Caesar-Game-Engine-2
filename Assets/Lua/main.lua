require("File3DLoader")
require("AnimationDude")
require("Text")
require("camera")
require("SkyBox")
require("LightSetup")
require("floor")
require("Information")

local ironManMesh =  BasicDrawableObject({[Keys["BasicDrawable"]["MODEL"]]            = LoadDefaultModel("Assets/Models/Iron_Man_mark_4.obj"),
                                          [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                          [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
local ironManTexture= BasicTexture("Assets/Texture/Iron_Man_mark_4_D.jpg");

local ironMan = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(0.0, 0.2, -15.0),
                        [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.15, 0.15, 0.15, 1.0),
                        [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.0, 0.0, 0.0),
                        [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.1),
                        [Keys["ObjectInfo"]["DrawableObj"]] = ironManMesh,
                        [Keys["ObjectInfo"]["Texture2DObj"]]= ironManTexture,
                        [Keys["ObjectInfo"]["UserData"]]    = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  },
                        });

sphereDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["MODEL"]]            = LoadDefaultModel("Assets/Models/Sphere_Smooth.ply"),
                                      [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                      [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
for zIndex = 0, 2, 1 do
    for xIndex = 1, 10, 1 do
        local x = ((xIndex % 10) - 5) * 4;
        local y = 2;
        local z = -20 + (zIndex * 20);
        local sphereObject = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(x, y, z),
                                     [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58, 0.5),
                                     [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
                                     [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
                                     [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,});
    end
end

lightPos = 10.0;
OnKeyDown(KeyCode["B"], 
    function()       
      SpotLight({[Keys["Light"]["Diffuse"]]     = Vector4(0.0, 0.0, 1.0),
                 [Keys["Light"]["Ambient"]]     = Vector4(0.1, 0.1, 1.0),
                 [Keys["Light"]["Specular"]]    = Vector4(0.0, 0.0, 1.0),
                 [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, lightPos),
                 [Keys["Light"]["Direction"]]   = Vector4(0.7853, -3.14, -3.14),
                 [Keys["Light"]["Attenuation"]] = Vector4(0.0, 0.1, 0.0),
                 [Keys["Light"]["Spot"]]        = 0.5,
                 [Keys["Light"]["Range"]]       = 20,
                 [Keys["Light"]["HasShadow"]]   = true,});
      lightPos = lightPos - 20.0;
    end
);


Sleep(5000, function (time)
    local textExample = Text2D("Hello!",  Vector4(50.0, 200.0, 0.0));
    textExample:Scale(Vector4(5.0, 5.0, 5.0));
    Sleep(5000, function (time)
        textExample:Release();
    end);
end);

--mirrorSphereCam1 = Camera({[Keys["Camera"]["Eye"]]        = Vector4(40, 20, 0),
--                           [Keys["Camera"]["NearZ"]]      = 0.01,              
--                           [Keys["Camera"]["FarZ"]]       = 5000.0,
--                           [Keys["Camera"]["ClearColor"]] = Vector4(0.5, 0.5, 0.5, 1.0),
--                           [Keys["Camera"]["Process2D"]]  = false,
--                            });
--mirrorSphereSC = CubeScreenCapture({[Keys["ScreenShot"]["Width"]]   = 1024,
--                                    [Keys["ScreenShot"]["Height"]]   = 1024,
--                                    [Keys["ScreenShot"]["CameraID"]] = mirrorSphereCam1, });
--local mirrorSphere1 = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(40, 20, 0),
--                              [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58, 1.0),
--                              [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
--                              [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
--                              [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,
--                              [Keys["ObjectInfo"]["Scale"]]       = Vector4(10.0, 10.0, 10.0),
--                              [Keys["ObjectInfo"]["Light"]]       = false,});
--mirrorSphere1:AddCubeTexture(mirrorSphereSC:GetTexture());

--mirrorSphereCam2 = Camera({[Keys["Camera"]["Eye"]]        = Vector4(-40, 20, 0),
--                           [Keys["Camera"]["NearZ"]]      = 0.01,              
--                           [Keys["Camera"]["FarZ"]]       = 5000.0,
--                           [Keys["Camera"]["ClearColor"]] = Vector4(0.5, 0.5, 0.5, 1.0),
--                           [Keys["Camera"]["Process2D"]]  = false,
--                            });
--mirrorSphereSC2 = CubeScreenCapture({[Keys["ScreenShot"]["Width"]]   = 1024,
--                                     [Keys["ScreenShot"]["Height"]]   = 1024,
--                                     [Keys["ScreenShot"]["CameraID"]] = mirrorSphereCam2, });
--local mirrorSphere2 = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(-40, 20, 0),
--                              [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58, 1.0),
--                              [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
--                              [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
--                              [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,
--                              [Keys["ObjectInfo"]["Scale"]]       = Vector4(10.0, 10.0, 10.0),
--                              [Keys["ObjectInfo"]["Light"]]       = false,});
--mirrorSphere2:AddCubeTexture(mirrorSphereSC2:GetTexture());