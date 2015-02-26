require("Helper")

local VSShader = VertexShader("Assets/ShaderFiles/VS_Basic.cso");
local PSColorShader = PixelShader("Assets/ShaderFiles/PS_Color.cso");

local WalkScene = LoadScene("Assets/Animation/walk.BVH");
local runScene = LoadScene("Assets/Animation/Run1.bvh");
local boardScene = LoadScene("Assets/Animation/bored.bvh");

local mesh = WalkScene["Model"];
local rootNode = WalkScene["RootNode"];

local walkAnimation = WalkScene["Animation"];
local runAnimation = runScene["Animation"];
local boardAnimation = boardScene["Animation"]

local walkBasicAnimation = BasicAnimation(walkAnimation[1]); 
local runBasicAnimation = BasicAnimation(runAnimation[1]); 
local boardBasicAnimation = BasicAnimation(boardAnimation[1]); 
local StickPersonAnimationController = AnimationController({
                    [Keys["AnimationController"]["BasicAnimation"]]   = boardBasicAnimation,
                    [Keys["AnimationController"]["RootNode"]]         = rootNode,
                    [Keys["AnimationController"]["Speed"]]            = 1.0,
                                    });

local stickRotation = Vector4(0.0, 0.0, 0.0);
local stickLocation = Vector4(-100.0, 0.0, -40.0);
local stickFigerObjNodes = {};    
function RecursiveLoadJoint(joint)
    local meshes = joint.Meshes;
    local meshGraphic = GraphicModel(mesh[meshes[1]]);
    stickFigerObjNodes[joint.Name] = Object({
                    [Keys["ObjectInfo"]["Scale"]]           = Vector4(0.1, 0.1, 0.1),
                    [Keys["ObjectInfo"]["GraphicModel"]]    = meshGraphic,
                    [Keys["ObjectInfo"]["VertexShader"]]    = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]     = PSColorShader,
                    [Keys["ObjectInfo"]["UserData"]]        = { ["Color"] = Vector4(0.0, 1.0, 0.0) },
                    [Keys["ObjectInfo"]["AnimationJoint"]]  =  joint.Name,
                    [Keys["ObjectInfo"]["AnimationObj"]]    =  StickPersonAnimationController,
                    [Keys["ObjectInfo"]["RigidBody"]]       = mainBodyRididBody,
                        });

    for key,value in pairs(joint.Childern) do 
        RecursiveLoadJoint(value);
    end
end
RecursiveLoadJoint(rootNode);

function UpdateStickFigureJoints()
    for key,value in pairs(stickFigerObjNodes) do 
        value.Rotation = stickRotation;
        value.Location = stickLocation;
    end
end

local StickForwardButton   = false;    local StickBackwardButton  = false;
local StickLeftButton     = false;     local StickkRightButton   = false;
local StickRunButton     = false;

local IdleToWalkLength = 2;
local WalkToIdleLength = 1;
local WalkToRunLength = 2;
local RunToWalkLength = 1;

local currentState;
local timeSinceStateStart = 0.0;

function IdleStateUpdate(time)
    if(StickForwardButton == true) then
        StickPersonAnimationController:ChangeAnimation({
                    [Keys["AnimationController"]["BasicAnimation"]]     = walkBasicAnimation,
                    [Keys["AnimationController"]["TransitionType"]]     = TransitionType["CrossFade"],
                    [Keys["AnimationController"]["TransitionLength"]]   = IdleToWalkLength,
                    --[Keys["AnimationController"]["StartOnNextPhase"]]   = true,
                                                    });
        currentState = IdleToWalkStateUpdate;
        timeSinceStateStart = 0.0;
    end;
end;
function WalkToIdleStateUpdate(time)
    local precentageSinceStart = timeSinceStateStart / (WalkToIdleLength  * 1000);
    stickLocation = MoveObject(stickLocation, Vector4(0.0, 0.0, 1.0), stickRotation.X, stickRotation.Y, stickRotation.Z, (time * 0.01 * (1.0 - precentageSinceStart)));
    
    if(precentageSinceStart > 1.0) then
        currentState = IdleStateUpdate;
        timeSinceStateStart = 0.0;
    end;
end;
function IdleToWalkStateUpdate(time)
    local precentageSinceStart = timeSinceStateStart /(IdleToWalkLength * 1000) ;
    stickLocation = MoveObject(stickLocation, Vector4(0.0, 0.0, 1.0), stickRotation.X, stickRotation.Y, stickRotation.Z, (time * 0.01 * precentageSinceStart));
    
    if(precentageSinceStart > 1.0) then
        currentState = WalkStateUpdate;
        timeSinceStateStart = 0.0;
    end;
end
function WalkStateUpdate(time)
    stickLocation = MoveObject(stickLocation, Vector4(0.0, 0.0, 1.0), stickRotation.X, stickRotation.Y, stickRotation.Z, (time * 0.01));
    
    if(StickForwardButton == false) then
        StickPersonAnimationController:ChangeAnimation({
                    [Keys["AnimationController"]["BasicAnimation"]]     = boardBasicAnimation,
                    [Keys["AnimationController"]["TransitionType"]]     = TransitionType["SnapShot"],
                    [Keys["AnimationController"]["TransitionLength"]]   = WalkToIdleLength,
                    [Keys["AnimationController"]["StartOnNextPhase"]]   = true,
                                                    });
        currentState = WalkToIdleStateUpdate;
        timeSinceStateStart = 0.0;
    elseif(StickRunButton == true) then
        StickPersonAnimationController:ChangeAnimation({
                    [Keys["AnimationController"]["BasicAnimation"]]     = runBasicAnimation,
                    [Keys["AnimationController"]["TransitionType"]]     = TransitionType["TimeSync"],
                    [Keys["AnimationController"]["TransitionLength"]]   = WalkToIdleLength,
                    [Keys["AnimationController"]["StartOnNextPhase"]]   = true,
                                                    });
        currentState = WalkToRunStateUpdate;
        timeSinceStateStart = 0.0;
    end;
end;
function WalkToRunStateUpdate(time)
    local precentageSinceStart = timeSinceStateStart /(WalkToRunLength * 1000) ;
    stickLocation = MoveObject(stickLocation, Vector4(0.0, 0.0, 1.0), stickRotation.X, stickRotation.Y, stickRotation.Z, (time * (0.01 * precentageSinceStart) + (time * 0.01)));
    
    if(precentageSinceStart > 1.0) then
        currentState = RunStateUpdate;
        timeSinceStateStart = 0.0;
    end;
end;
function RunStateUpdate(time)
    stickLocation = MoveObject(stickLocation, Vector4(0.0, 0.0, 1.0), stickRotation.X, stickRotation.Y, stickRotation.Z, (time * 0.02));
    
    if(StickForwardButton == false or StickRunButton == false) then
        StickPersonAnimationController:ChangeAnimation({
                    [Keys["AnimationController"]["BasicAnimation"]]     = walkBasicAnimation,
                    [Keys["AnimationController"]["TransitionType"]]     = TransitionType["TimeSync"],
                    [Keys["AnimationController"]["TransitionLength"]]   = WalkToIdleLength,
                    [Keys["AnimationController"]["StartOnNextPhase"]]   = true,
                                                    });
        currentState = RunToWalkStateUpdate;
        timeSinceStateStart = 0.0;
    end;
end; 
function RunToWalkStateUpdate(time)
    local precentageSinceStart = timeSinceStateStart /(RunToWalkLength * 1000) ;
    stickLocation = MoveObject(stickLocation, Vector4(0.0, 0.0, 1.0), stickRotation.X, stickRotation.Y, stickRotation.Z, (time * 0.01 * (1.0 - precentageSinceStart) + (time * 0.01)));
    
    if(precentageSinceStart > 1.0) then
        currentState = WalkStateUpdate;
        timeSinceStateStart = 0.0;
    end;
end;

currentState = IdleStateUpdate;

function UpdateStickFigure(time, ID)
    timeSinceStateStart = timeSinceStateStart + time;
    
    currentState(time);
    
    if(StickLeftButton == true) then
        stickRotation.y = stickRotation.y + (time * 0.001);
    end
    if(StickkRightButton == true) then
        stickRotation.y = stickRotation.y + (time * -0.001);
    end
end

UpdateStickFigure(0);
UpdateStickFigureJoints(0);

LoopCall(15, UpdateStickFigure);
LoopCall(15, UpdateStickFigureJoints);

OnKeyDown(KeyCode["J"], function() StickLeftButton = true; end);-- Left
OnKeyDown(KeyCode["L"], function() StickkRightButton = true; end);-- Right
OnKeyDown(KeyCode["I"], function() StickForwardButton = true; end);-- Up
OnKeyDown(KeyCode["K"], function() StickBackwardButton = true; end);-- Down
OnKeyDown(KeyCode["LSHIFT"], function() StickRunButton = true; end);-- Shift

OnKeyUp(KeyCode["J"], function() StickLeftButton = false; end);-- Left
OnKeyUp(KeyCode["L"], function() StickkRightButton = false; end);-- Right
OnKeyUp(KeyCode["I"], function() StickForwardButton = false; end);-- Up
OnKeyUp(KeyCode["K"], function() StickBackwardButton = false; end);-- Down
OnKeyUp(KeyCode["LSHIFT"], function() StickRunButton = false; end);-- Shift

local minorAnimationID = "";
OnKeyDown(KeyCode["U"],
    function() 
        if(minorAnimationID == "") then
            minorAnimationID = StickPersonAnimationController:AddMinorAnimation({
                    [Keys["AnimationController"]["BasicAnimation"]] = boardBasicAnimation,
                    [Keys["AnimationController"]["StartNodeName"]]  = "chest",
                    [Keys["AnimationController"]["StartRatio"]]     = 0.3,
                    [Keys["AnimationController"]["StepRatio"]]      = 0.2,
                                                         });
        else
            StickPersonAnimationController:RemoveMinorAnimation(minorAnimationID);
            minorAnimationID = ""; 
        end
    end);-- Left
