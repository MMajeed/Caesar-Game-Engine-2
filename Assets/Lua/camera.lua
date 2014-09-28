local ScreenWidth = GetClientSize()["Width"];
local ScreenHeight = GetClientSize()["Height"];

MainDrawSettings = DrawSettings({
                    [Keys["DrawSettings"]["ClearColor"]]      = Vector4(0.5, 0.5, 0.5, 1.0),
                    [Keys["DrawSettings"]["ClearScreen"]]     = true,
                    [Keys["DrawSettings"]["InclusionState"]]  = InclusionType["Exclude"],
                    [Keys["DrawSettings"]["InclusionList"]]   = { "NoMainDraw" },
                    [Keys["DrawSettings"]["UserData"]]        = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                   }); 
SetMainDrawSettings(MainDrawSettings);

MainCamera = Camera({
                    [Keys["Camera"]["Eye"]]             = Vector4(0, 5.0, -60.0, 0.0),
                    [Keys["Camera"]["TargetMagnitude"]] = Vector4(0.0, 0.0, 1.0, 0.0),
                    [Keys["Camera"]["Up"]]              = Vector4(0.0, 1.0, 0.0, 0.0),
                    [Keys["Camera"]["Roll"]]            = 0.0,
                    [Keys["Camera"]["Pitch"]]           = 0.0,
                    [Keys["Camera"]["Yaw"]]             = 0.0,
                    [Keys["Camera"]["FovAngle"]]        = 0.785398163,
                    [Keys["Camera"]["NearZ"]]           = 0.01,              
                    [Keys["Camera"]["FarZ"]]            = 1100.0,
                   }); 
SetMainCamera(MainCamera);

local CamLeftButton   = false;    local CamRightButton  = false;
local CamUpButton     = false;    local CamDownButton   = false;
local CamPgUpButton   = false;    local CamPgDownButton = false;

local CallOnUpdate = {};

function AddToCallOnCameraUpdate(func)
      table.insert(CallOnUpdate, func)
end

function UpdateCamera(time, ID)
    if(CamLeftButton == true) then
        MainCamera.Yaw = MainCamera.Yaw + (0.002 * time);
    end
    if(CamRightButton == true) then
        MainCamera.Yaw = MainCamera.Yaw - (0.002 * time);
    end
    
    if(CamPgUpButton == true) then
        MainCamera.Pitch = MainCamera.Pitch - (0.002 * time);
    end
    if(CamPgDownButton == true) then
        MainCamera.Pitch = MainCamera.Pitch + (0.002 * time);
    end
    
    if(CamUpButton == true) then
        local moveDistance = 0.05 * time;
        MainCamera.Eye = MoveObject(MainCamera.Eye, MainCamera.TargetMagnitude, MainCamera.Pitch,  MainCamera.Yaw,  MainCamera.Roll, moveDistance)
    end
    if(CamDownButton == true) then
        local moveDistance = -0.05 * time;
        MainCamera.Eye = MoveObject(MainCamera.Eye, MainCamera.TargetMagnitude, MainCamera.Pitch,  MainCamera.Yaw,  MainCamera.Roll, moveDistance)
    end
    for key,value in pairs(CallOnUpdate) do value(time, ID) end
end

LoopCall(16, UpdateCamera);

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


