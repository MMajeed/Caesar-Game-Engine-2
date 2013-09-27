local camera = {}

eye = Vector4(0.0, 5.0, -20.0, 0.0)
targetMagintude = Vector4(0.0, 0.0, 1.0, 0.0)
up = Vector4(0.0, 1.0, 0.0, 0.0)

cam = Camera(eye, targetMagintude, up, 0.0, 0.0, 0.0); 

CamLeftButton   = false;    CamRightButton  = false;
CamUpButton     = false;    CamDownButton   = false;
CamPgUpButton   = false;    CamPgDownButton = false;

function UpdateCamera()
    if(CamLeftButton == true) then
        cam.Yaw = cam.Yaw - 0.025;
    end
    if(CamRightButton == true) then
        cam.Yaw = cam.Yaw + 0.025;
    end
    
    if(CamPgUpButton == true) then
        cam.Pitch = cam.Pitch - 0.025;
    end
    if(CamPgDownButton == true) then
        cam.Pitch = cam.Pitch + 0.025;
    end
    
    if(CamUpButton == true) then
        cam:MoveFroward(1.0);
    end
    if(CamDownButton == true) then
        cam:MoveFroward(-1.0);
    end
end

LoopCall(16, UpdateCamera);

OnKeyDown(37, function() CamLeftButton = true; end);-- Left
OnKeyDown(39, function() CamRightButton = true; end);-- Right
OnKeyDown(38, function() CamUpButton = true; end);-- Up
OnKeyDown(40, function() CamDownButton = true; end);-- Down
OnKeyDown(33, function() CamPgUpButton = true; end);-- Up
OnKeyDown(34, function() CamPgDownButton = true; end);-- Down

OnKeyUp(37, function() CamLeftButton = false; end);-- Left
OnKeyUp(39, function() CamRightButton = false; end);-- Right
OnKeyUp(38, function() CamUpButton = false; end);-- Up
OnKeyUp(40, function() CamDownButton = false; end);-- Down
OnKeyUp(33, function() CamPgUpButton = false; end);-- Up
OnKeyUp(34, function() CamPgDownButton = false; end);-- Down

return camera

