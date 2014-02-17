local PhysicsDemo = {}

local floorBox = Object({
                [Keys["ObjectInfo"]["Location"]]    = Vector4(-100.0, 0.0, 0.0),
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(100.0, 0.5, 100.0),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.5, 0.5, 0.5, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.1, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.01, 0.01, 0.01, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
                [Keys["ObjectInfo"]["Texture2DObj"]]= tilesTexture,});
local floorBoxCollisionShape = CreateBoxShape(Vector4(50.0, 0.25, 50.0));
local floorBoxRididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-100.0, 0.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Inertia"]]        = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 0.0,
                [Keys["RigidBody"]["CollisionShape"]] = floorBoxCollisionShape,});
                
  

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
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.01, 0.01, 0.01, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = fallingBoxRididBody,});           


return PhysicsDemo;

