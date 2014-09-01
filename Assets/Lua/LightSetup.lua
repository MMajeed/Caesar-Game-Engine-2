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
local PSDirectionalLight = PixelShader("Assets/ShaderFiles/4_PS_SpotLight.cso");

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
                    [Keys["ScreenShot"]["Priority"]]      = 0,
                    [Keys["ScreenShot"]["NumOfTargets"]]  = 5,
                    [Keys["ScreenShot"]["CameraID"]]      = CamDeferredGenerator, });
                    

local GUIDID = GenerateGUID();

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

Light = class(function(self, LightInfo) 
        local userData = LightInfo:GetResource();
        userData["CameraEye"] = regularCam.Eye;
        
        self.CamLightCalculator = Camera({
                   [Keys["Camera"]["ClearColor"]]      = Vector4(0.0, 0.0, 0.0, 1.0),
                   [Keys["Camera"]["InclusionState"]]  = InclusionType["Include"],
                   [Keys["Camera"]["InclusionList"]]   = { GUIDID },                
                   [Keys["Camera"]["PixelShader"]]     = LightInfo:GetShader(),
                   [Keys["Camera"]["PixelShaderState"]]= ShaderType["Force"],
                   [Keys["Camera"]["UserData"]]        = userData
                  }); 
        self.LightCalculator = BasicScreenCapture({
                   [Keys["ScreenShot"]["Width"]]         = 1024,
                   [Keys["ScreenShot"]["Height"]]        = 768,
                   [Keys["ScreenShot"]["Priority"]]      = 200,
                   [Keys["ScreenShot"]["NumOfTargets"]]  = 1,
                   [Keys["ScreenShot"]["CameraID"]]      = self.CamLightCalculator, 
                   });
                   
        function UpdateLightEye(time, ID)
            self.CamLightCalculator:SetUserData("CameraEye", regularCam.Eye);
        end
        AddToCallOnCameraUpdate(UpdateLightEye)
        
        function UpdateLightResource(ID, Value)
            self.CamLightCalculator:SetUserData(ID, Value);
        end
        LightInfo:AddToCallOnUpdate(UpdateLightResource);
     end)
     

local LightArray = {};

function SetupLight()
    local lastLookedUpValue = nil;
    for key,value in pairs(LightArray) do 
        if(lastLookedUpValue == nil) then -- First variable
            value.CamLightCalculator:SetUserData("HasPrivousLight", 0);
        else
            value.CamLightCalculator:SetUserData("HasPrivousLight", 1);
            value.CamLightCalculator:SetTexture("PrivousLightTexture", lastLookedUpValue.LightCalculator:GetTexture());
        end
        lastLookedUpValue = value;
    end
    
    regularCam.Texture = { ["LightTexture"] =  lastLookedUpValue.LightCalculator:GetTexture() };
end

function AddLight(LightInfo)
    local l = Light(LightInfo);
    table.insert(LightArray, l)
    SetupLight();
end
