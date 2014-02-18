local PhysicsDemo = {}


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
local fallingBoxRididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-100.0, 200.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 1.0,
                [Keys["RigidBody"]["CollisionShape"]] = fallingBoxCollisionShape,});   
local fallingBox = Object({
                [Keys["ObjectInfo"]["Location"]]    = Vector4(0.0, 0.0, 0.0),
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(5.0, 5.0, 5.0),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.5, 0.5, 0.5, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.1, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = fallingBoxRididBody,});           

local PhysicsForwardButton   = false;    local PhysicsBackwardButton  = false;
local PhysicsLeftButton     = false;     local PhysicsRightButton   = false;


OnKeyDown(KeyCode["F"], function() PhysicsLeftButton = true; end);-- Left
OnKeyDown(KeyCode["H"], function() PhysicsRightButton = true; end);-- Right
OnKeyDown(KeyCode["T"], function() PhysicsForwardButton = true; end);-- Up
OnKeyDown(KeyCode["G"], function() PhysicsBackwardButton = true; end);-- Down

OnKeyUp(KeyCode["F"], function() PhysicsLeftButton = false; end);-- Left
OnKeyUp(KeyCode["H"], function() PhysicsRightButton = false; end);-- Right
OnKeyUp(KeyCode["T"], function() PhysicsForwardButton = false; end);-- Up
OnKeyUp(KeyCode["G"], function() PhysicsBackwardButton = false; end);-- Down

function UpdatePhysicsDemo(time, ID)
    local delta = 2.0 * time;
    if(PhysicsLeftButton == true) then
        fallingBoxRididBody:ApplyCentralFroce(Vector4(delta, 0.0, 0.0));
    end
    if(PhysicsRightButton == true) then
        fallingBoxRididBody:ApplyCentralFroce(Vector4(-delta , 0.0, 0.0));
    end
    
    if(PhysicsForwardButton == true) then
        fallingBoxRididBody:ApplyCentralFroce(Vector4(0.0, delta, 0.0));
    end
    if(PhysicsBackwardButton == true) then
        fallingBoxRididBody:ApplyCentralFroce(Vector4(0.0, -delta, 0.0));
    end
end

LoopCall(0, UpdatePhysicsDemo);

return PhysicsDemo;

