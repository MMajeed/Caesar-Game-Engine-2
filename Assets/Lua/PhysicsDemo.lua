
local floorBoxCollisionShape = CreateBoxShape(Vector4(50.0, 0.25, 50.0));
local floorBoxRididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-100.0, 0.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Inertia"]]        = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 0.0,
                [Keys["RigidBody"]["CollisionShape"]] = floorBoxCollisionShape,});
local floorBox = Object({
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(100.0, 0.5, 100.0),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.5, 0.5, 0.5, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.1, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.01, 0.01, 0.01, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
                [Keys["ObjectInfo"]["Texture2DObj"]]= tilesTexture,
                [Keys["ObjectInfo"]["RigidBody"]]   = floorBoxRididBody,});
                
  

local fallingBoxCollisionShape = CreateBoxShape(Vector4(2.5, 2.5, 2.5));
local fallingBoxRididBodyA = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-100.0, 5.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 1.0,
                [Keys["RigidBody"]["CollisionShape"]] = fallingBoxCollisionShape,});   
local fallingBoxA = Object({
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(5.0, 5.0, 5.0),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(1.0, 0.1, 0.1, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = fallingBoxRididBodyA,});     

local fallingBoxRididBodyB = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-95.0, 5.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 1.0,
                [Keys["RigidBody"]["CollisionShape"]] = fallingBoxCollisionShape,});   
local fallingBoxB = Object({
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(5.0, 5.0, 5.0),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.5, 0.5, 0.5, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.1, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = fallingBoxRididBodyB,});     

local constraint = nil;
OnKeyUp(KeyCode["Z"], 
    function()
        if (constraint == nil) then
            constraint = Hinge({
                            [Keys["Constraint"]["RigidBodyA"]]          = fallingBoxRididBodyA,
                            [Keys["Constraint"]["PivotPointA"]]         = Vector4(0.0, 2.5, 0.9),
                            [Keys["Constraint"]["AxesA"]]               = Vector4(0.78, 0.0, 0.0),
                            [Keys["Constraint"]["RigidBodyB"]]          = fallingBoxRididBodyB,
                            [Keys["Constraint"]["PivotPointB"]]         = Vector4(0.0, -2.5, 0.0),
                            [Keys["Constraint"]["AxesB"]]               = Vector4(0.0, 0.0, 0.0),
                            [Keys["Constraint"]["BreakingThreshold"]]   = 1000,
                            });   
        else
            constraint:Release();
            constraint = nil;
        end
    end);  

local PhysicsForwardButton   = false;    local PhysicsBackwardButton  = false;
local PhysicsLeftButton      = false;    local PhysicsRightButton     = false;


OnKeyDown(KeyCode["F"], function() PhysicsLeftButton = true; end);-- Left
OnKeyDown(KeyCode["H"], function() PhysicsRightButton = true; end);-- Right
OnKeyDown(KeyCode["T"], function() PhysicsForwardButton = true; end);-- Up
OnKeyDown(KeyCode["G"], function() PhysicsBackwardButton = true; end);-- Down

OnKeyUp(KeyCode["F"], function() PhysicsLeftButton = false; end);-- Left
OnKeyUp(KeyCode["H"], function() PhysicsRightButton = false; end);-- Right
OnKeyUp(KeyCode["T"], function() PhysicsForwardButton = false; end);-- Up
OnKeyUp(KeyCode["G"], function() PhysicsBackwardButton = false; end);-- Down

function UpdatePhysicsDemo(time, ID)
    local delta = 5.0 * time;
    if(PhysicsLeftButton == true) then
        fallingBoxRididBodyB:ApplyTorque(Vector4(delta, 0.0, 0.0));
    end
    if(PhysicsRightButton == true) then
        fallingBoxRididBodyB:ApplyTorque(Vector4(-delta, 0.0, 0.0));
    end
    
    if(PhysicsForwardButton == true) then
        fallingBoxRididBodyA:ApplyCentralFroce(Vector4(0.0, delta, 0.0));
    end
    if(PhysicsBackwardButton == true) then
        fallingBoxRididBodyA:ApplyCentralFroce(Vector4(0.0, -delta, 0.0));
    end
end

LoopCall(0, UpdatePhysicsDemo);
