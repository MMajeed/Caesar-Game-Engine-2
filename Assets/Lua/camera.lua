local camera = {}

local verticeArray = {};
verticeArray[1] = Vertice({["Point"] = Vector4(0.0, 0.0, 0.0), 
                           ["Texture"] = Vector4(0.0, 0.0, 0.0), });
verticeArray[2] = Vertice({["Point"] = Vector4(1.0, 0.0, 0.0), 
                           ["Texture"] = Vector4(1.0, 0.0, 0.0), });
verticeArray[3] = Vertice({["Point"] = Vector4(0.0, 1.0, 0.0), 
                           ["Texture"] = Vector4(0.0, 1.0, 0.0), });
verticeArray[4] = Vertice({["Point"] = Vector4(1.0, 1.0, 0.0), 
                           ["Texture"] = Vector4(1.0, 1.0, 0.0), });
local faces = {0, 1, 2, 2, 1, 3};

local spriteModel = Model();
spriteModel.Vertices = verticeArray;
spriteModel.Faces = faces;
local Quad2DDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = spriteModel,
                                            [Keys["BasicDrawable"]["Dimension"]]        = Dimension["2D"],
                                            [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                            [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_2_Texture.cso",
                                           });
local Quad2D = Object({[Keys["ObjectInfo"]["DrawableObj"]]  = Quad2DDrawable,
                       [Keys["ObjectInfo"]["Scale"]]        = Vector4(GetClientsSize()["Width"], GetClientsSize()["Height"], 1.0, 1.0),
                      });
local sniperTexture = BasicTexture("Assets/Texture/Sniper2.png");

                      
local Quad2DCam = Camera({[Keys["Camera"]["Eye"]]              = Vector4(0.0, 5.0, -50.0, 0.0),
                           [Keys["Camera"]["TargetMagnitude"]] = Vector4(0.0, 0.0, 1.0, 0.0),
                           [Keys["Camera"]["Up"]]              = Vector4(0.0, 1.0, 0.0, 0.0),
                           [Keys["Camera"]["RadianRoll"]]      = 0.0,
                           [Keys["Camera"]["RadianPitch"]]     = 0.0,
                           [Keys["Camera"]["RadianYaw"]]       = 0.0,
                           [Keys["Camera"]["FovAngle"]]        = 0.785398163,
                           [Keys["Camera"]["NearZ"]]           = 0.01,              
                           [Keys["Camera"]["FarZ"]]            = 5000.0,
                           [Keys["Camera"]["ClearColor"]]      = Vector4(0.5, 0.5, 0.5, 1.0),
                           [Keys["Camera"]["Global2DTexture"]] = sniperTexture,
                           [Keys["Camera"]["GlobalUserData"]]  = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  },
                           [Keys["Camera"]["InclusionState"]]  = InclusionType["Include"],
                           [Keys["Camera"]["ObjectList"]]      = { Quad2D },
                         }); 
Quad2DCam:SetAsMain();
                      

regularCam = Camera({[Keys["Camera"]["Eye"]]             = Vector4(0.0, 5.0, -50.0, 0.0),
                     [Keys["Camera"]["TargetMagnitude"]] = Vector4(0.0, 0.0, 1.0, 0.0),
                     [Keys["Camera"]["Up"]]              = Vector4(0.0, 1.0, 0.0, 0.0),
                     [Keys["Camera"]["RadianRoll"]]      = 0.0,
                     [Keys["Camera"]["RadianPitch"]]     = 0.0,
                     [Keys["Camera"]["RadianYaw"]]       = 0.0,
                     [Keys["Camera"]["FovAngle"]]        = 0.785398163,
                     [Keys["Camera"]["NearZ"]]           = 0.01,              
                     [Keys["Camera"]["FarZ"]]            = 5000.0,
                     [Keys["Camera"]["ClearColor"]]      = Vector4(0.5, 0.5, 0.5, 1.0),
                     [Keys["Camera"]["GlobalUserData"]]  = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  },
                     [Keys["Camera"]["InclusionState"]]  = InclusionType["Exclude"],
                     [Keys["Camera"]["ObjectList"]]      = { Quad2D },
                   }); 
--regularCam:SetAsMain();

local regularCapture = BasicScreenCapture({[Keys["ScreenShot"]["Width"]]    = GetClientsSize()["Width"],
                                           [Keys["ScreenShot"]["Height"]]   = GetClientsSize()["Height"],
                                           [Keys["ScreenShot"]["CameraID"]] = regularCam, });

Quad2D:Add2DTexture(regularCapture:GetTexture());

local currentShaderState = 0;
OnKeyDown(KeyCode["R"],
    function()
        if(currentShaderState == 0) then
            Quad2DDrawable:ChangePS("Assets/ShaderFiles/PS_3_Sniper.cso");
            currentShaderState = 1;
        else 
            Quad2DDrawable:ChangePS("Assets/ShaderFiles/PS_2_Texture.cso");
            currentShaderState = 0;
        end
    end);

local CamLeftButton   = false;    local CamRightButton  = false;
local CamUpButton     = false;    local CamDownButton   = false;
local CamPgUpButton   = false;    local CamPgDownButton = false;

function UpdateCamera(time, ID)
    if(CamLeftButton == true) then
        regularCam.Yaw = regularCam.Yaw - (0.0025 * time);
        Quad2DCam.Yaw = regularCam.Yaw;
    end
    if(CamRightButton == true) then
        regularCam.Yaw = regularCam.Yaw + (0.0025 * time);
        Quad2DCam.Yaw = regularCam.Yaw;
    end
    
    if(CamPgUpButton == true) then
        regularCam.Pitch = regularCam.Pitch - (0.0025 * time);
        Quad2DCam.Pitch = regularCam.Pitch;
    end
    if(CamPgDownButton == true) then
        regularCam.Pitch = regularCam.Pitch + (0.0025 * time);
        Quad2DCam.Pitch = regularCam.Pitch;
    end
    
    if(CamUpButton == true) then
        regularCam:MoveFroward((0.05 * time));
        Quad2DCam.Eye = regularCam.Eye;
    end
    if(CamDownButton == true) then
        regularCam:MoveFroward((-0.05 * time));
        Quad2DCam.Eye = regularCam.Eye;
    end
end

LoopCall(15, UpdateCamera);

OnKeyDown(KeyCode["A"], function() CamLeftButton = true; end);-- Left
OnKeyDown(KeyCode["D"], function() CamRightButton = true; end);-- Right
OnKeyDown(KeyCode["W"], function() CamUpButton = true; end);-- Up
OnKeyDown(KeyCode["S"], function() CamDownButton = true; end);-- Down
OnKeyDown(KeyCode["Q"], function() CamPgUpButton = true; end);-- Up
OnKeyDown(KeyCode["E"], function() CamPgDownButton = true; end);-- Down

OnKeyUp(KeyCode["A"], function() CamLeftButton = false; end);-- Left
OnKeyUp(KeyCode["D"], function() CamRightButton = false; end);-- Right
OnKeyUp(KeyCode["W"], function() CamUpButton = false; end);-- Up
OnKeyUp(KeyCode["S"], function() CamDownButton = false; end);-- Down
OnKeyUp(KeyCode["Q"], function() CamPgUpButton = false; end);-- Up
OnKeyUp(KeyCode["E"], function() CamPgDownButton = false; end);-- Down


sniperCam = Camera({[Keys["Camera"]["Eye"]]             = Vector4(0.0, 5.0, -50.0, 0.0),
                    [Keys["Camera"]["TargetMagnitude"]] = Vector4(0.0, 0.0, 1.0, 0.0),
                    [Keys["Camera"]["Up"]]              = Vector4(0.0, 1.0, 0.0, 0.0),
                    [Keys["Camera"]["RadianRoll"]]      = 0.0,
                    [Keys["Camera"]["RadianPitch"]]     = 0.0,
                    [Keys["Camera"]["RadianYaw"]]       = 0.0,
                    [Keys["Camera"]["ClearColor"]]      = Vector4(0.5, 0.5, 0.5, 1.0),
                    [Keys["Camera"]["GlobalUserData"]]  = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  },
                   }); 

return camera

