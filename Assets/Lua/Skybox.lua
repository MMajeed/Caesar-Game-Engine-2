require("Helper")

local VSShader = VertexShader("Assets/ShaderFiles/VS_Basic.cso");
local PSTextureShader = PixelShader("Assets/ShaderFiles/PS_SkyMap.cso");
local sphereGraphic = GraphicModel(LoadDefaultModel("Assets/Models/Sphere_Smooth.ply"));
local skyBoxTexture = BasicTexture("Assets/Texture/Sky/Sky.dds");

local skybox = Object({
                        [Keys["ObjectInfo"]["Location"]]     = Vector4(0.0, 0.0, 0.0),
                        [Keys["ObjectInfo"]["Scale"]]        = Vector4(1000.0, 1000.0, 1000.0),
                        [Keys["ObjectInfo"]["GraphicModel"]] = sphereGraphic,
                        [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                        [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                        [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = skyBoxTexture },
                        [Keys["ObjectInfo"]["FillMode"]]     = FillMode["Solid"],
                        [Keys["ObjectInfo"]["CullMode"]]     = CullMode["Front"],
                        });
                        
function UpdateSkyBox()
    skybox.Location = regularCam.Eye;
end
LoopCall(1, UpdateSkyBox);