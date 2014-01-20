local camera = {}

cam = Camera({[Keys["Camera"]["Eye"]]             = Vector4(0.0, 5.0, -50.0, 0.0),
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
            }); 
cam:SetAsMain();

CamLeftButton   = false;    CamRightButton  = false;
CamUpButton     = false;    CamDownButton   = false;
CamPgUpButton   = false;    CamPgDownButton = false;

function UpdateCamera(time, ID)
    if(CamLeftButton == true) then
        cam.Yaw = cam.Yaw - 0.05;
    end
    if(CamRightButton == true) then
        cam.Yaw = cam.Yaw + 0.05;
    end
    
    if(CamPgUpButton == true) then
        cam.Pitch = cam.Pitch - 0.05;
    end
    if(CamPgDownButton == true) then
        cam.Pitch = cam.Pitch + 0.05;
    end
    
    if(CamUpButton == true) then
        cam:MoveFroward(1.0);
    end
    if(CamDownButton == true) then
        cam:MoveFroward(-1.0);
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

return camera

