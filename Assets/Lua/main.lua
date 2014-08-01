--require("Text")
--require("Information")
require("camera")
--require("LightSetup")
require("SkyBox")
require("floor")
--require("PhysicsDemo")
----require("RandomAnimation")
--require("StickPerson")
require("Helper")

local ironManTexture= BasicTexture("Assets/Texture/Iron_Man_mark_4_D.jpg");
local ironManMesh = GraphicModel(LoadDefaultModel("Assets/Models/Iron_Man_mark_4.obj"));
local sphereGraphic = GraphicModel(LoadDefaultModel("Assets/Models/Sphere_Smooth.ply"));
local VSShader = VertexShader("Assets/ShaderFiles/VS_Basic.cso");
local PSColorShader = PixelShader("Assets/ShaderFiles/PS_Color.cso");
local PSTextureShader = PixelShader("Assets/ShaderFiles/PS_Texture.cso");

local ironMan = Object({
                        [Keys["ObjectInfo"]["Location"]]     = Vector4(0.0, 0.5, -30.0),
                        [Keys["ObjectInfo"]["GraphicModel"]] = ironManMesh,
                        [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                        [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                        [Keys["ObjectInfo"]["UserData"]]     = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                        [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = ironManTexture },
                        });
                        
for zIndex = 0, 2, 1 do
    for xIndex = 1, 10, 1 do
        local x = ((xIndex % 10) - 5) * 4;
        local y = 2;
        local z = -20 + (zIndex * 20);
        local sphereObject = Object({
                                    [Keys["ObjectInfo"]["Location"]]     = Vector4(x, y, z),
                                    [Keys["ObjectInfo"]["GraphicModel"]] = sphereGraphic,
                                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                                    [Keys["ObjectInfo"]["PixelShader"]]  = PSColorShader,
                                    [Keys["ObjectInfo"]["UserData"]]     = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                                    });
    end
end



local lastTimeCheck = 0.0;
local lastGraphicFrameCheck = GetGraphicFrame();
local lastInputFrameCheck = GetInputFrame();
local lastScriptFrameCheck = GetScriptFrame();
local lastAnimationFrameCheck = GetAnimationFrame();
local lastPhysicsFrameCheck = GetPhysicsFrame();

function UpdateFrameText()
    local currentTime = GetTimeSinceStart();
    local timeDifference = currentTime - lastTimeCheck;
    lastTimeCheck = currentTime;
    
    local graphicFrameCount = GetGraphicFrame();
    local graphicFrameDifference = graphicFrameCount - lastGraphicFrameCheck;
    lastGraphicFrameCheck = graphicFrameCount;
    local graphicFrame = graphicFrameDifference / timeDifference;
    
    local inputFrameCount = GetInputFrame();
    local inputFrameDifference = inputFrameCount - lastInputFrameCheck;
    lastInputFrameCheck = inputFrameCount;
    local inputFrame = inputFrameDifference / timeDifference;
    
    local scriptFrameCount = GetScriptFrame();
    local scriptFrameDifference =  scriptFrameCount - lastScriptFrameCheck;
    lastScriptFrameCheck =  scriptFrameCount;
    local scriptFrame = scriptFrameDifference / timeDifference;
    
    local animationFrameCount = GetAnimationFrame();
    local animationFrameDifference =  animationFrameCount - lastAnimationFrameCheck;
    lastAnimationFrameCheck =  animationFrameCount;
    local animationFrame = animationFrameDifference / timeDifference;
    
    local physicFrameCount = GetPhysicsFrame();
    local physicFrameDifference =  physicFrameCount - lastPhysicsFrameCheck;
    lastPhysicsFrameCheck =  physicFrameCount;
    local physicFrame = physicFrameDifference / timeDifference;
    
    local message = "Frame Rate:" .. 
                    " Graphic: " .. string.format("%3.2f", graphicFrame) .. 
                    " Input: " .. string.format("%3.2f", inputFrame) .. 
                    " Script: " .. string.format("%3.2f", scriptFrame).. 
                    " Animation: " .. string.format("%3.2f", animationFrame) ..
                    " Physics: " .. string.format("%3.2f", physicFrame) ;
    SetWindowsTitle(message);
end
UpdateFrameText();
LoopCall(1000, UpdateFrameText);
--lightPos = 10.0;
--OnKeyDown(KeyCode["B"], 
--    function()   
--		spotLight = SpotLight(
--					  {[Keys["Light"]["Diffuse"]]     = Vector4(0.0, 0.0, 0.8),
--                       [Keys["Light"]["Ambient"]]     = Vector4(0.0, 0.0, 0.5),
--                       [Keys["Light"]["Specular"]]    = Vector4(0.0, 0.0, 1.0),
--                       [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, lightPos),
--                       [Keys["Light"]["Direction"]]   = Vector4(0.7853, -3.14, -3.14),
--                       [Keys["Light"]["Attenuation"]] = Vector4(0.0, 0.1, 0.0),
--                       [Keys["Light"]["Spot"]]        = 0.5,
--                       [Keys["Light"]["Range"]]       = 20,
--                       [Keys["Light"]["HasShadow"]]   = true,});    
--      lightPos = lightPos - 20.0;
--    end
--);


--Sleep(5000, function (time)
--    local textExample = Text2D("Hello!",  Vector4(50.0, 200.0, 0.0));
--    textExample:Scale(Vector4(5.0, 5.0, 5.0));
--    Sleep(5000, function (time)
--        textExample:Release();
--    end);
--end);

--mirrorSphereCam1 = Camera({[Keys["Camera"]["Eye"]]        = Vector4(40, 20, 0),
--                           [Keys["Camera"]["NearZ"]]      = 0.01,              
--                           [Keys["Camera"]["FarZ"]]       = 5000.0,
--                           [Keys["Camera"]["ClearColor"]] = Vector4(1.0, 0.5, 0.5, 1.0),
--                           [Keys["Camera"]["Process2D"]]  = false,
--                            });
--mirrorSphereSC = CubeScreenCapture({[Keys["ScreenShot"]["Width"]]   = 512,
--                                    [Keys["ScreenShot"]["Height"]]   =512,
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
--mirrorSphereSC2 = CubeScreenCapture({[Keys["ScreenShot"]["Width"]]   = 512,
--                                     [Keys["ScreenShot"]["Height"]]   = 512,
--                                     [Keys["ScreenShot"]["CameraID"]] = mirrorSphereCam2, });
--local mirrorSphere2 = Object({[Keys["ObjectInfo"]["Location"]]    = Vector4(-40, 20, 0),
--                              [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58, 1.0),
--                              [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
--                              [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
--                              [Keys["ObjectInfo"]["DrawableObj"]] = sphereDrawable,
--                              [Keys["ObjectInfo"]["Scale"]]       = Vector4(10.0, 10.0, 10.0),
--                              [Keys["ObjectInfo"]["Light"]]       = false,});
--mirrorSphere2:AddCubeTexture(mirrorSphereSC2:GetTexture());