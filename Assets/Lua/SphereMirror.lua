require("Helper")

local sphereGraphic = GraphicModel(LoadDefaultModel("Assets/Models/Sphere.obj"));
local VSShader = VertexShader("Assets/ShaderFiles/VS_Basic.cso");
local PSCubeShader = PixelShader("Assets/ShaderFiles/PS_CubeTexture.cso");

local mirrorWidth = 1024 / 2;
local mirrorHeight = 1024 / 2;

local mirrorSphereCam1 = Camera({
                    [Keys["Camera"]["Eye"]]             = Vector4(40, 20, 0),
                    [Keys["Camera"]["NearZ"]]           = 1.0,              
                    [Keys["Camera"]["FarZ"]]            = 2000.0,
                    [Keys["Camera"]["ClearColor"]]      = Vector4(0.5, 0.5, 0.5, 1.0),
                    [Keys["Camera"]["InclusionState"]]  = InclusionType["Exclude"],
                    [Keys["Camera"]["InclusionList"]]    = {"Text", "NoMainDraw"},
                    [Keys["Camera"]["Texture"]]          = regularCam.Texture,
                   }); 
                   
local mirrorSphereSC1 = CubeScreenCapture({
                    [Keys["ScreenShot"]["Width"]]    = mirrorWidth,
                    [Keys["ScreenShot"]["Height"]]   = mirrorHeight,
                    [Keys["ScreenShot"]["Priority"]] = mirrorSphereCam1, });
                                    
                                    
local mirrorSphere1 = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(40, 20, 0),
                    [Keys["ObjectInfo"]["Scale"]]        = Vector4(10.0, 10.0, 10.0),
                    [Keys["ObjectInfo"]["GraphicModel"]] = sphereGraphic,
                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSCubeShader,
                    [Keys["ObjectInfo"]["UserData"]]     = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                    [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = mirrorSphereSC1:GetTexture() },
                    [Keys["ObjectInfo"]["Group"]]        = { "NoLight"},
                        });
                        
local mirrorSphereCam2 = Camera({
                    [Keys["Camera"]["Eye"]]             = Vector4(-40, 20, 0),
                    [Keys["Camera"]["NearZ"]]           = 1.0,              
                    [Keys["Camera"]["FarZ"]]            = 2000.0,
                    [Keys["Camera"]["ClearColor"]]      = Vector4(0.5, 0.5, 0.5, 1.0),
                    [Keys["Camera"]["InclusionState"]]  = InclusionType["Exclude"],
                    [Keys["Camera"]["InclusionList"]]    = {"Text", "NoMainDraw"},
                    [Keys["Camera"]["Texture"]]          = regularCam.Texture,
                   }); 
                   
local mirrorSphereSC2 = CubeScreenCapture({
                    [Keys["ScreenShot"]["Width"]]    = mirrorWidth,
                    [Keys["ScreenShot"]["Height"]]   = mirrorHeight,
                    [Keys["ScreenShot"]["Priority"]] = mirrorSphereCam2, });
                                    
                                    
local mirrorSphere2 = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(-40, 20, 0),
                    [Keys["ObjectInfo"]["Scale"]]        = Vector4(10.0, 10.0, 10.0),
                    [Keys["ObjectInfo"]["GraphicModel"]] = sphereGraphic,
                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSCubeShader,
                    [Keys["ObjectInfo"]["UserData"]]     = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                    [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = mirrorSphereSC2:GetTexture() },
                    [Keys["ObjectInfo"]["Group"]]        = { "NoLight"},
                        });