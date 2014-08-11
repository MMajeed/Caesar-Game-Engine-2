local ScreenWidth = GetClientsSize()["Width"];
local ScreenHeight = GetClientsSize()["Height"];

regularCam = Camera({
                    [Keys["Camera"]["Eye"]]             = Vector4(0, 5.0, -60.0, 0.0),
                    [Keys["Camera"]["TargetMagnitude"]] = Vector4(0.0, 0.0, 1.0, 0.0),
                    [Keys["Camera"]["Up"]]              = Vector4(0.0, 1.0, 0.0, 0.0),
                    [Keys["Camera"]["Roll"]]            = 0.0,
                    [Keys["Camera"]["Pitch"]]           = 0.0,
                    [Keys["Camera"]["Yaw"]]             = 0.0,
                    [Keys["Camera"]["FovAngle"]]        = 0.785398163,
                    [Keys["Camera"]["NearZ"]]           = 0.01,              
                    [Keys["Camera"]["FarZ"]]            = 1100.0,
                    [Keys["Camera"]["ClearColor"]]      = Vector4(0.5, 0.5, 0.5, 1.0),
                    [Keys["Camera"]["InclusionState"]]  = InclusionType["Exclude"],
                    [Keys["Camera"]["InclusionList"]]   = {},
                    [Keys["Camera"]["UserData"]]        = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                   }); 
SetMainCamera(regularCam);

local CamLeftButton   = false;    local CamRightButton  = false;
local CamUpButton     = false;    local CamDownButton   = false;
local CamPgUpButton   = false;    local CamPgDownButton = false;

function UpdateCamera(time, ID)
    if(CamLeftButton == true) then
        regularCam.Yaw = regularCam.Yaw + (0.002 * time);
    end
    if(CamRightButton == true) then
        regularCam.Yaw = regularCam.Yaw - (0.002 * time);
    end
    
    if(CamPgUpButton == true) then
        regularCam.Pitch = regularCam.Pitch - (0.002 * time);
    end
    if(CamPgDownButton == true) then
        regularCam.Pitch = regularCam.Pitch + (0.002 * time);
    end
    
    if(CamUpButton == true) then
        local moveDistance = 0.05 * time;
        regularCam.Eye = MoveObject(regularCam.Eye, regularCam.TargetMagnitude, regularCam.Pitch,  regularCam.Yaw,  regularCam.Roll, moveDistance)
    end
    if(CamDownButton == true) then
        local moveDistance = -0.05 * time;
        regularCam.Eye = MoveObject(regularCam.Eye, regularCam.TargetMagnitude, regularCam.Pitch,  regularCam.Yaw,  regularCam.Roll, moveDistance)
    end
end

LoopCall(1, UpdateCamera);

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


