local textureWidth = GetClientSize()["Width"];
local textureHeight = GetClientSize()["Height"];

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
local PSDeferredDirectionalLight = PixelShader("Assets/ShaderFiles/1_PS_DeferredLight.cso");
local PSDirectionalLight = PixelShader("Assets/ShaderFiles/4_PS_SpotLight.cso");

local DrawSettingsDeferredGenerator = DrawSettings({
                [Keys["DrawSettings"]["ClearColor"]]      = Vector4(-1.0, -1.0, -1.0, 1.0),
                [Keys["DrawSettings"]["InclusionState"]]  = InclusionType["Exclude"],
                [Keys["DrawSettings"]["InclusionList"]]   = { "NoLight" },
                [Keys["DrawSettings"]["PixelShader"]]     = PSDeferredDirectionalLight,
                [Keys["DrawSettings"]["PixelShaderState"]]= ShaderType["Force"],
                [Keys["DrawSettings"]["UserData"]]        = {
                                                      ["Diffuse"]   = Vector4(1.0, 1.0, 1.0),
                                                      ["Ambient"]   = Vector4(1.0, 1.0, 1.0),
                                                      ["Specular"]  = Vector4(1.0, 1.0, 1.0),}
               }); 
               
local DefferredGenerator = BasicScreenCapture({
                    [Keys["ScreenShot"]["Width"]]         = textureWidth,
                    [Keys["ScreenShot"]["Height"]]        = textureHeight,
                    [Keys["ScreenShot"]["Priority"]]      = 0,
                    [Keys["ScreenShot"]["NumOfTargets"]]  = 5,
                    [Keys["ScreenShot"]["CameraID"]]      = MainCamera,
                    [Keys["ScreenShot"]["DrawSettingsID"]]= DrawSettingsDeferredGenerator, });   

local GUIDID = GenerateGUID();

local SpriteObj = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(0.0, 0.0, 0.0, 1.0),
                    [Keys["ObjectInfo"]["Scale"]]        = Vector4(1366, 768, 0.0, 1.0),
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
        userData["CameraEye"] = MainCamera.Eye;
        
        self.DrawSettingsLightCalculator = DrawSettings({
                   [Keys["DrawSettings"]["ClearColor"]]      = Vector4(0.0, 0.0, 0.0, 1.0),
                   [Keys["DrawSettings"]["InclusionState"]]  = InclusionType["Include"],
                   [Keys["DrawSettings"]["InclusionList"]]   = { GUIDID },                
                   [Keys["DrawSettings"]["PixelShader"]]     = LightInfo:GetShader(),
                   [Keys["DrawSettings"]["PixelShaderState"]]= ShaderType["Force"],
                   [Keys["DrawSettings"]["UserData"]]        = userData
                  }); 
        self.LightCalculator = BasicScreenCapture({
                   [Keys["ScreenShot"]["Width"]]         = textureWidth,
                   [Keys["ScreenShot"]["Height"]]        = textureHeight,
                   [Keys["ScreenShot"]["Priority"]]      = 200,
                   [Keys["ScreenShot"]["NumOfTargets"]]  = 1,
                   [Keys["ScreenShot"]["CameraID"]]      = MainCamera,
                   [Keys["ScreenShot"]["DrawSettingsID"]]= self.DrawSettingsLightCalculator, 
                   });
                           
        function UpdateLightResource(ID, Value)
            self.DrawSettingsLightCalculator:SetUserData(ID, Value);
        end
        LightInfo:AddToCallOnUpdate(UpdateLightResource);
     end)
     

local LightArray = {};

function SetupLight()
    local counter = 100;

    local lastLookedUpValue = nil;
    for key,value in pairs(LightArray) do 
        if(lastLookedUpValue == nil) then -- First variable
            value.DrawSettingsLightCalculator:SetUserData("HasPrivousLight", 0);
        else
            value.DrawSettingsLightCalculator:SetUserData("HasPrivousLight", 1);
            value.DrawSettingsLightCalculator:SetTexture("PrivousLightTexture", lastLookedUpValue.LightCalculator:GetTexture());
        end
        lastLookedUpValue = value;
        value.LightCalculator:SetPriority(counter);
        counter = counter + 10;
    end
    
    MainDrawSettings.Texture = { ["LightTexture"] =  lastLookedUpValue.LightCalculator:GetTexture() };
end

function AddLight(LightInfo)
    local l = Light(LightInfo);
    table.insert(LightArray, l)
    SetupLight();
end

                            
function ResizeLightFunction(ID, Width, Height)
    DefferredGenerator:GetTexture()[1]:Release();
    DefferredGenerator:GetTexture()[2]:Release();
    DefferredGenerator:GetTexture()[3]:Release();
    DefferredGenerator:GetTexture()[4]:Release();
    DefferredGenerator:GetTexture()[5]:Release();
    DefferredGenerator:Release();
    DefferredGenerator = BasicScreenCapture({
                    [Keys["ScreenShot"]["Width"]]         = Width,
                    [Keys["ScreenShot"]["Height"]]        = Height,
                    [Keys["ScreenShot"]["Priority"]]      = 0,
                    [Keys["ScreenShot"]["NumOfTargets"]]  = 5,
                    [Keys["ScreenShot"]["CameraID"]]      = MainCamera, 
                    [Keys["ScreenShot"]["DrawSettingsID"]]= DrawSettingsDeferredGenerator, });

    SpriteObj.Scale = Vector4(Width, Height, 0.0, 1.0);
    SpriteObj.Texture =  {
                   ["LocationTexture"]    = DefferredGenerator:GetTexture()[1],
                   ["NormalTexture"]      = DefferredGenerator:GetTexture()[2],
                   ["DiffuseTexture"]     = DefferredGenerator:GetTexture()[3],
                   ["AmbientTexture"]     = DefferredGenerator:GetTexture()[4],
                   ["SpecularTexture"]    = DefferredGenerator:GetTexture()[5],
            };
    for key,value in pairs(LightArray) do 
        value.LightCalculator:GetTexture():Release();
        value.LightCalculator:Release();
        value.LightCalculator = BasicScreenCapture({
                   [Keys["ScreenShot"]["Width"]]         = Width,
                   [Keys["ScreenShot"]["Height"]]        = Height,
                   [Keys["ScreenShot"]["Priority"]]      = 200,
                   [Keys["ScreenShot"]["NumOfTargets"]]  = 1,
                   [Keys["ScreenShot"]["CameraID"]]      = MainCamera,
                   [Keys["ScreenShot"]["DrawSettingsID"]]= value.DrawSettingsLightCalculator, 
                   });
    end
    SetupLight();
end
CallOnResize(ResizeLightFunction);