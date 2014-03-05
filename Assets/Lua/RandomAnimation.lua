local fileNames = { 
                    "Assets/Animation/bored.BVH", 
                    "Assets/Animation/walk.BVH", 
                    "Assets/Animation/Run1.BVH", 
                    "Assets/Animation/WalkCasually.BVH", 
                    "Assets/Animation/StandIdle.BVH",
                    "Assets/Animation/Zombie.BVH", 
                    "Assets/Animation/DanceCharleston.BVH",  
                  };
local zPosition = -40;
local speed = 1.0;
for k,v in pairs(fileNames) do 
    local animationScene = LoadScene(v);
    local mesh = animationScene["Model"];
    local animation = animationScene["Animation"];
    local rootNode = animationScene["RootNode"];
    local BasicAnimation = BasicAnimation(animation[1]); 
    local AnimationController = AnimationController({
                                    [Keys["AnimationController"]["BasicAnimation"]]   = BasicAnimation,
                                    [Keys["AnimationController"]["RootNode"]]         = rootNode,
                                    [Keys["AnimationController"]["Speed"]]            = speed,
                                    });

    function RecursiveLoadJoint(joint)
        local meshes = joint.Meshes;
        local ManDrawable =  BasicDrawableObject({[Keys["BasicDrawable"]["MODEL"]]            = mesh[meshes[1]],
                                                  [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                                  [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});

        local ManObj =   Object({
                            [Keys["ObjectInfo"]["Location"]]        = Vector4(70, 0.0, zPosition),
                            [Keys["ObjectInfo"]["Scale"]]           = Vector4(0.1, 0.1, 0.1),
                            [Keys["ObjectInfo"]["DrawableObj"]]     = ManDrawable,
                            [Keys["ObjectInfo"]["AnimationJoint"]]  = {AnimationController,  joint.Name},
                            [Keys["ObjectInfo"]["Light"]]           = false,
                                });
        for key,value in pairs(joint.Childern) do 
            RecursiveLoadJoint(value);
        end
    end

    RecursiveLoadJoint(rootNode);
    speed = speed - ( 1 / table.getn(fileNames));
    zPosition = zPosition + 10;
end
