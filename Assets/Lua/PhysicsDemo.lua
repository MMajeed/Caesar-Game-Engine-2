-- --------------------------- Floor -------------------------------------
local floorDrawable = BasicDrawableObject({
                            [Keys["BasicDrawable"]["MODEL"]]            = LoadDefaultModel("Assets/Models/Box.ply"),
                            [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                            [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});

local floorBoxCollisionShape = CreateBoxShape(Vector4(50.0, 0.25, 50.0));
local floorBoxRididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-100.0, 0.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Inertia"]]        = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 0.0,
                [Keys["RigidBody"]["CollisionShape"]] = floorBoxCollisionShape,});
local floorBoxRididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Inertia"]]        = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 0.0,
                [Keys["RigidBody"]["CollisionShape"]] = floorBoxCollisionShape,});
local floorBoxRididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(100.0, 0.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Inertia"]]        = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 0.0,
                [Keys["RigidBody"]["CollisionShape"]] = floorBoxCollisionShape,});
-- --------------------------- Floor -------------------------------------

-- --------------------------- Main Body -------------------------------------
local mainBodyDrawable = BasicDrawableObject({
                            [Keys["BasicDrawable"]["MODEL"]]            = LoadDefaultModel("Assets/Models/Box.ply"),
                            [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                            [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
local mainBodyCollisionShape = CreateBoxShape(Vector4(1.5, 0.5, 2.0));
local mainBodyRididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-100.0, 5.0, 0.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
                [Keys["RigidBody"]["Mass"]]           = 10.0,
                [Keys["RigidBody"]["CollisionShape"]] = mainBodyCollisionShape,});   
local mainBody = Object({
                [Keys["ObjectInfo"]["Rotation"]]    =  Vector4(0.0, 0.0, 0.0),
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(3.0, 1.0, 4.0),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.7, 0.1, 0.1, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.2, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = mainBodyRididBody,});     
-- --------------------------- Main Body -------------------------------------

-- --------------------------- Tires -------------------------------------
local Low = 0;
local High = 6.28  ;
local Softness = 0.9;
local BiasFactor = 0.01;
local RelaxationFactor = 0.0;
local MaxMotorImpulse = 2.0;

local SizeOfCylinder = 0.5 ;

local cylinderModel = LoadDefaultModel("Assets/Models/Cylinder_1x1.ply");
local cylinderDrawable = BasicDrawableObject({
                            [Keys["BasicDrawable"]["MODEL"]]            = cylinderModel,
                            [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                            [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
local cylinderShape =   CreateCylinderShape(Vector4( SizeOfCylinder, SizeOfCylinder, SizeOfCylinder));

local tire1RididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-105.0, 2.5, 5.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 1.57),
                [Keys["RigidBody"]["Mass"]]           = 10.0,
                [Keys["RigidBody"]["CollisionShape"]] = cylinderShape,});  
local tire1Constraint = Hinge({
                [Keys["Constraint"]["RigidBodyA"]]          = mainBodyRididBody,
                [Keys["Constraint"]["PivotPointA"]]         = Vector4(-2, -1.0, 2.0),
                [Keys["Constraint"]["AxesA"]]               = Vector4(1.57, 0.0, 0.0),
                [Keys["Constraint"]["RigidBodyB"]]          = tire1RididBody,
                [Keys["Constraint"]["PivotPointB"]]         = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["AxesB"]]               = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["Low"]]                 = Low,
                [Keys["Constraint"]["High"]]                = High,
                [Keys["Constraint"]["Softness"]]            = Softness,
                [Keys["Constraint"]["BiasFactor"]]          = BiasFactor,
                [Keys["Constraint"]["RelaxationFactor"]]    = RelaxationFactor,
                [Keys["Constraint"]["MaxMotorImpulse"]]     = MaxMotorImpulse,
                });       
local objTire1 = Object({
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(SizeOfCylinder, SizeOfCylinder, SizeOfCylinder),
                [Keys["ObjectInfo"]["Rotation"]]    = Vector4(0.0, 0.0, 1.57),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(1.0, 0.1, 0.1, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.4, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = cylinderDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = tire1RididBody,});  
                
local tire2RididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-105.0, 2.5, -5.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 1.57),
                [Keys["RigidBody"]["Mass"]]           = 10.0,
                [Keys["RigidBody"]["CollisionShape"]] = cylinderShape,});  
local tire2Constraint = Hinge({
                [Keys["Constraint"]["RigidBodyA"]]          = mainBodyRididBody,
                [Keys["Constraint"]["PivotPointA"]]         = Vector4(-2.0, -1.0, -2.0),
                [Keys["Constraint"]["AxesA"]]               = Vector4(1.57, 0.0, 0.0),
                [Keys["Constraint"]["RigidBodyB"]]          = tire2RididBody,
                [Keys["Constraint"]["PivotPointB"]]         = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["AxesB"]]               = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["Low"]]                 = Low,
                [Keys["Constraint"]["High"]]                = High,
                [Keys["Constraint"]["Softness"]]            = Softness,
                [Keys["Constraint"]["BiasFactor"]]          = BiasFactor,
                [Keys["Constraint"]["RelaxationFactor"]]    = RelaxationFactor,
                [Keys["Constraint"]["MaxMotorImpulse"]]     = MaxMotorImpulse,
                });        
local objTire2 = Object({
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(SizeOfCylinder, SizeOfCylinder, SizeOfCylinder),
                [Keys["ObjectInfo"]["Rotation"]]    = Vector4(0.0, 0.0, 1.57),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(1.0, 0.1, 0.1, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.4, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = cylinderDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = tire2RididBody,});  

local tire3RididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-95.0, 2.5, -5.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 1.57),
                [Keys["RigidBody"]["Mass"]]           = 10.0,
                [Keys["RigidBody"]["CollisionShape"]] = cylinderShape,});   
local tire3Constraint = Hinge({
                [Keys["Constraint"]["RigidBodyA"]]          = mainBodyRididBody,
                [Keys["Constraint"]["PivotPointA"]]         = Vector4(2.0, -1.0, -2.0),
                [Keys["Constraint"]["AxesA"]]               = Vector4(1.57, 0.0, 0.0),
                [Keys["Constraint"]["RigidBodyB"]]          = tire3RididBody,
                [Keys["Constraint"]["PivotPointB"]]         = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["AxesB"]]               = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["Low"]]                 = Low,
                [Keys["Constraint"]["High"]]                = High,
                [Keys["Constraint"]["Softness"]]            = Softness,
                [Keys["Constraint"]["BiasFactor"]]          = BiasFactor,
                [Keys["Constraint"]["RelaxationFactor"]]    = RelaxationFactor,
                [Keys["Constraint"]["MaxMotorImpulse"]]     = MaxMotorImpulse,
                });        
local objTire3 = Object({
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(SizeOfCylinder, SizeOfCylinder, SizeOfCylinder),
                [Keys["ObjectInfo"]["Rotation"]]    = Vector4(0.0, 0.0, 1.57),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(1.0, 0.1, 0.1, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.4, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = cylinderDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = tire3RididBody,});  
                
local tire4RididBody = RididBody({
                [Keys["RigidBody"]["Position"]]       = Vector4(-95.0, 2.5, 5.0),
                [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 1.57),
                [Keys["RigidBody"]["Mass"]]           = 10.0,
                [Keys["RigidBody"]["CollisionShape"]] = cylinderShape,});   
local tire4Constraint = Hinge({
                [Keys["Constraint"]["RigidBodyA"]]          = mainBodyRididBody,
                [Keys["Constraint"]["PivotPointA"]]         = Vector4(2.0, -1.0, 2.0),
                [Keys["Constraint"]["AxesA"]]               = Vector4(1.57, 0.0, 0.0),
                [Keys["Constraint"]["RigidBodyB"]]          = tire4RididBody,
                [Keys["Constraint"]["PivotPointB"]]         = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["AxesB"]]               = Vector4(0.0, 0.0, 0.0),
                [Keys["Constraint"]["Low"]]                 = Low,
                [Keys["Constraint"]["High"]]                = High,
                [Keys["Constraint"]["Softness"]]            = Softness,
                [Keys["Constraint"]["BiasFactor"]]          = BiasFactor,
                [Keys["Constraint"]["RelaxationFactor"]]    = RelaxationFactor,
                [Keys["Constraint"]["MaxMotorImpulse"]]     = MaxMotorImpulse,
                });   
local objTire4 = Object({
                [Keys["ObjectInfo"]["Scale"]]       = Vector4(SizeOfCylinder, SizeOfCylinder, SizeOfCylinder),
                [Keys["ObjectInfo"]["Rotation"]]    = Vector4(0.0, 0.0, 1.57),
                [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(1.0, 0.1, 0.1, 1.0),
                [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.4, 0.1, 0.1),
                [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.1, 0.1, 0.1, 0.001),
                [Keys["ObjectInfo"]["DrawableObj"]] = cylinderDrawable,
                [Keys["ObjectInfo"]["RigidBody"]]   = tire4RididBody,});  
-- --------------------------- Tires -------------------------------------


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
    
    local forwardTorque = time * 5;
    local turingTorque = time * 10;
    local maxTorque = 5.0;
    if(PhysicsLeftButton == true) then
        tire1RididBody:ApplyTorque(Vector4(0.0, -turingTorque, 0.0));
        tire4RididBody:ApplyTorque(Vector4(0.0, -turingTorque, 0.0));
    end
    if(PhysicsRightButton == true) then
        tire1RididBody:ApplyTorque(Vector4(0.0, turingTorque, 0.0));
        tire4RididBody:ApplyTorque(Vector4(0.0, turingTorque, 0.0));
    end
    
    if(PhysicsForwardButton == true) then
        local mainBodyRotation = mainBodyRididBody:GetQuaRotation();
        
        local tire1NewTorque = RotateVector(Vector4(forwardTorque, 0.0, 0.0), mainBodyRotation);
        tire1RididBody:ApplyTorque(tire1NewTorque);
    
        local tire2NewTorque = RotateVector(Vector4(forwardTorque, 0.0, 0.0), mainBodyRotation);
        tire2RididBody:ApplyTorque(tire2NewTorque);
    end
    if(PhysicsBackwardButton == true) then
        tire2RididBody:SetTorque(Vector4(0.0, 0.0, 0.0));
        tire3RididBody:SetTorque(Vector4(0.0, 0.0, 0.0));
    end
end

LoopCall(0, UpdatePhysicsDemo);

---- --------------------------- Random Boxes -------------------------------------

--local boxModel = LoadDefaultModel("Assets/Models/Box.ply")
--for zIndex = 0, 2, 1 do
--    for xIndex = 1, 10, 1 do
--        local x = (((xIndex % 10) - 5) * 4) - 100;
--        local y = 2;
--        local z = -30 + (zIndex * 20);
--        local randomBoxDrawable = BasicDrawableObject({
--                            [Keys["BasicDrawable"]["MODEL"]]            = boxModel,
--                            [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
--                            [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
--        local randomBoxShape = CreateBoxShape(Vector4(1.0, 1.0, 1.0));
--        local randomBoxRididBody = RididBody({
--                        [Keys["RigidBody"]["Position"]]       = Vector4(x, y, z),
--                        [Keys["RigidBody"]["Rotation"]]       = Vector4(0.0, 0.0, 0.0),
--                        [Keys["RigidBody"]["Mass"]]           = 100.0,
--                        [Keys["RigidBody"]["CollisionShape"]] = randomBoxShape,});   
--        local randomBoxBody = Object({
--                         [Keys["ObjectInfo"]["Scale"]]       = Vector4(2.0, 2.0, 2.0),
--                         [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.51, 0.53, 0.58, 1.0),
--                         [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.5, 0.5, 0.5),
--                         [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.5, 0.5, 0.5, 0.5),
--                         [Keys["ObjectInfo"]["DrawableObj"]] = randomBoxDrawable,
--                         [Keys["ObjectInfo"]["RigidBody"]]   = randomBoxRididBody,});    

--    end
--end
---- --------------------------- Random Boxes -------------------------------------
