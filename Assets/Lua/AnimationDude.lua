local AnimationDude = {}

local fileNames = { "Assets/Animation/bored.BVH", "Assets/Animation/DanceCharleston.BVH", "Assets/Animation/StandIdle.BVH",
                    "Assets/Animation/walk.BVH", "Assets/Animation/WalkCasually.BVH", "Assets/Animation/Zombie.BVH",  };
local zPosition = -40;

for k,v in pairs(fileNames) do 
    local animationRunScene = LoadScene(v);
    local meshRun = animationRunScene["Model"];
    local animationRun = animationRunScene["Animation"];
    local rootNodeRun = animationRunScene["RootNode"];

    local runBasicAnimation = BasicAnimation(animationRun[1],rootNodeRun); 
    local runAnimationPlayer = AnimationPlayer(runBasicAnimation);
    local runAnimationController = AnimationController(runAnimationPlayer);

    function RecursiveLoadJoint(joint)
        local meshes = joint.Meshes;
        local runManDrawable =  BasicDrawableObject({[Keys["BasicDrawable"]["MODEL"]]            = meshRun[meshes[1]],
                                                     [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                                     [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});

        local runManObj =   Object({[Keys["ObjectInfo"]["Location"]]        = Vector4(0.0, 0.0, zPosition),
                                    [Keys["ObjectInfo"]["Scale"]]           = Vector4(0.1, 0.1, 0.1),
                                    [Keys["ObjectInfo"]["Diffuse"]]         = Vector4(0.15, 0.15, 0.15, 1.0),
                                    [Keys["ObjectInfo"]["Ambient"]]         = Vector4(0.0, 0.0, 0.0),
                                    [Keys["ObjectInfo"]["Specular"]]        = Vector4(0.1, 0.1, 0.1, 0.1),
                                    [Keys["ObjectInfo"]["DrawableObj"]]     = runManDrawable,
                                    [Keys["ObjectInfo"]["AnimationJoint"]]  = {runAnimationController,  joint.Name},
                                });
        for key,value in pairs(joint.Childern) do 
            RecursiveLoadJoint(value);
        end
    end

    RecursiveLoadJoint(rootNodeRun);
    
    zPosition = zPosition + 20;
end

return AnimationDude;

