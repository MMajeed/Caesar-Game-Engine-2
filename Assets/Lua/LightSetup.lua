local verticeArray = {};
local textureArray = {};
        
verticeArray[1] = Vector4(0.0, 0.0, 0.0);
textureArray[1] = Vector4(0.0, 0.0, 0.0);

verticeArray[2] = Vector4(1.0, 1.0, 0.0);
textureArray[2] = Vector4(1.0, 1.0, 0.0);

verticeArray[3] = Vector4(0.0, 1.0, 0.0);
textureArray[3] = Vector4(0.0, 1.0, 0.0);

verticeArray[4] = Vector4(1.0, 0.0, 0.0);
textureArray[4] = Vector4(1.0, 0.0, 0.0);

local faces = { 0, 2, 1, 0, 1, 3};

local spriteModel = Model();
spriteModel.Faces = faces;
spriteModel.Vertices = verticeArray;
spriteModel.Texture = textureArray;

local graphicSpriteModel = GraphicModel(spriteModel);
local VS2DShader = VertexShader("Assets/ShaderFiles/VS_2D.cso");
local PSDeferredDirectionalLight = PixelShader("Assets/ShaderFiles/1_PS_DeferredDirectionalLight.cso");
local PSDirectionalLight = PixelShader("Assets/ShaderFiles/2_PS_DirectionalLight.cso");

local GUIDID = GenerateGUID();

local CamDeferredGenerator = Camera({
                [Keys["Camera"]["Eye"]]             = regularCam.Eye,
                [Keys["Camera"]["TargetMagnitude"]] = regularCam.TargetMagnitude,
                [Keys["Camera"]["Up"]]              = regularCam.Up,
                [Keys["Camera"]["Roll"]]            = regularCam.Roll,
                [Keys["Camera"]["Pitch"]]           = regularCam.Pitch,
                [Keys["Camera"]["Yaw"]]             = regularCam.Yaw,
                [Keys["Camera"]["NearZ"]]           = 0.01,              
                [Keys["Camera"]["FarZ"]]            = 5000.0,
                [Keys["Camera"]["ClearColor"]]      = Vector4(0.0, 0.0, 0.0, 1.0),
                [Keys["Camera"]["InclusionState"]]  = InclusionType["Exclude"],
                [Keys["Camera"]["InclusionList"]]   = { "NoLight" },
                [Keys["Camera"]["PixelShader"]]     = PSDeferredDirectionalLight,
                [Keys["Camera"]["PixelShaderState"]]= ShaderType["Force"],
                [Keys["Camera"]["UserData"]]        = {
                                                      ["Diffuse"]   = Vector4(1.0, 1.0, 1.0),
                                                      ["Ambient"]   = Vector4(1.0, 1.0, 1.0),
                                                      ["Specular"]  = Vector4(1.0, 1.0, 1.0),}
               }); 
               
function UpdateDeferredCam(time, ID)
    CamDeferredGenerator.Eye = regularCam.Eye;
    CamDeferredGenerator.TargetMagnitude = regularCam.TargetMagnitude;
    CamDeferredGenerator.Up = regularCam.Up;
    CamDeferredGenerator.Roll = regularCam.Roll;
    CamDeferredGenerator.Pitch = regularCam.Pitch;
    CamDeferredGenerator.Yaw = regularCam.Yaw;
end
AddToCallOnCameraUpdate(UpdateDeferredCam)

local DefferredGenerator = BasicScreenCapture({
                    [Keys["ScreenShot"]["Width"]]         = 1024,
                    [Keys["ScreenShot"]["Height"]]        = 768,
                    [Keys["ScreenShot"]["Priority"]]      = 1,
                    [Keys["ScreenShot"]["NumOfTargets"]]  = 5,
                    [Keys["ScreenShot"]["CameraID"]]      = CamDeferredGenerator, });
                    
local SpriteObj = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(0.0, 0.0, 0.0, 1.0),
                    [Keys["ObjectInfo"]["Scale"]]        = Vector4(1024, 768, 0.0, 1.0),
                    [Keys["ObjectInfo"]["GraphicModel"]] = graphicSpriteModel,
                    [Keys["ObjectInfo"]["VertexShader"]] = VS2DShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSDirectionalLight,
                    [Keys["ObjectInfo"]["Group"]]        = { "NoMainDraw", "NoLight", GUIDID },
                    [Keys["ObjectInfo"]["UserData"]]     = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                    [Keys["ObjectInfo"]["CullMode"]]     = CullMode["None"],
                    [Keys["ObjectInfo"]["Texture"]]     = {
                                                             ["LocationTexture"]    = DefferredGenerator:GetTexture()[1],
                                                             ["NormalTexture"]      = DefferredGenerator:GetTexture()[2],
                                                             ["DiffuseTexture"]     = DefferredGenerator:GetTexture()[3],
                                                             ["AmbientTexture"]     = DefferredGenerator:GetTexture()[4],
                                                             ["SpecularTexture"]    = DefferredGenerator:GetTexture()[5],
                                                              },
                            });  

local CamLightCalculator = Camera({
                [Keys["Camera"]["Eye"]]             = regularCam.Eye,
                [Keys["Camera"]["TargetMagnitude"]] = regularCam.TargetMagnitude,
                [Keys["Camera"]["Up"]]              = regularCam.Up,
                [Keys["Camera"]["Roll"]]            = regularCam.Roll,
                [Keys["Camera"]["Pitch"]]           = regularCam.Pitch,
                [Keys["Camera"]["Yaw"]]             = regularCam.Yaw,
                [Keys["Camera"]["NearZ"]]           = 0.01,              
                [Keys["Camera"]["FarZ"]]            = 5000.0,
                [Keys["Camera"]["ClearColor"]]      = Vector4(1.0, 0.0, 0.0, 1.0),
                [Keys["Camera"]["InclusionState"]]  = InclusionType["Include"],
                [Keys["Camera"]["InclusionList"]]   = { GUIDID },
                [Keys["Camera"]["UserData"]]        = {
                                                      ["Diffuse"]   = Vector4(1.0, 1.0, 1.0),
                                                      ["Ambient"]   = Vector4(0.5, 0.5, 0.5),
                                                      ["Specular"]  = Vector4(0.1, 0.1, 0.1),
                                                      ["Direction"] = Vector4(0.0, 0.785, 0.1),
                                                      ["CameraEye"] = regularCam.Eye, }
               }); 
local LightCalculator = BasicScreenCapture({
                    [Keys["ScreenShot"]["Width"]]         = 1024,
                    [Keys["ScreenShot"]["Height"]]        = 768,
                    [Keys["ScreenShot"]["Priority"]]      = 2,
                    [Keys["ScreenShot"]["NumOfTargets"]]  = 1,
                    [Keys["ScreenShot"]["CameraID"]]      = CamLightCalculator, 
                    });

                         
regularCam.Texture = { ["LightTexture"] =  LightCalculator:GetTexture() };
--floor2.Texture = { ["Texture"] =  LightCalculator:GetTexture() };

--directionLight = DirectionalLight({[Keys["Light"]["Diffuse"]]   = Vector4(1.0, 1.0, 1.0),
--                                   [Keys["Light"]["Ambient"]]   = Vector4(0.5, 0.5, 0.5),
--                                   [Keys["Light"]["Specular"]]  = Vector4(0.1, 0.1, 0.1),
--                                   [Keys["Light"]["Direction"]] = Vector4(0.0, 0.785, 0.1),
--                                   [Keys["Light"]["HasShadow"]] = true,});

--pointLight = PointLight({[Keys["Light"]["Diffuse"]]     = Vector4(0.8, 0.8, 0.0),
--                         [Keys["Light"]["Ambient"]]     = Vector4(0.3, 0.3, 0.0),
--                         [Keys["Light"]["Specular"]]    = Vector4(0.0, 0.0, 0.0),
--                         [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, -45.0),
--                         [Keys["Light"]["Range"]]       = 40,
--                         [Keys["Light"]["Attenuation"]] = Vector4(1.0, 0.0, 0.0),});
            
--spotLight = SpotLight({[Keys["Light"]["Diffuse"]]     = Vector4(0.0, 0.0, 0.8),
--                       [Keys["Light"]["Ambient"]]     = Vector4(0.0, 0.0, 0.1),
--                       [Keys["Light"]["Specular"]]    = Vector4(0.0, 0.0, 1.0),
--                       [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, 30.0),
--                       [Keys["Light"]["Direction"]]   = Vector4(0.7853, -3.14, -3.14),
--                       [Keys["Light"]["Attenuation"]] = Vector4(0.0, 0.1, 0.0),
--                       [Keys["Light"]["Spot"]]        = 0.5,
--                       [Keys["Light"]["Range"]]       = 20,
--                       [Keys["Light"]["HasShadow"]]   = fal,});

