require("Helper")

local VSShader = VertexShader("Assets/ShaderFiles/VS_Basic.cso");
local PSTextureShader = PixelShader("Assets/ShaderFiles/PS_Texture.cso");
local boxDrawable = GraphicModel(LoadDefaultModel("Assets/Models/Box.ply"));
local tilesTexture = BasicTexture("Assets/Texture/Tiles.png");

local floor1 = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(100.0, 0.0, 0.0),
                    [Keys["ObjectInfo"]["Scale"]]        = Vector4(100.0, 0.5, 100.0),
                    [Keys["ObjectInfo"]["GraphicModel"]] = boxDrawable,
                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                    [Keys["ObjectInfo"]["Group"]]        = { "NoLight"},
                    [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = tilesTexture },
                    });
                 
floor2 = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(0.0, 0.0, 0.0),
                    [Keys["ObjectInfo"]["Scale"]]        = Vector4(100.0, 0.5, 100.0),
                    [Keys["ObjectInfo"]["GraphicModel"]] = boxDrawable,
                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                    [Keys["ObjectInfo"]["Group"]]        = { "NoLight"},
                    [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = tilesTexture },
                    });

local floor3 = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(-100.0, 0.0, 0.0),
                    [Keys["ObjectInfo"]["Scale"]]        = Vector4(100.0, 0.5, 100.0),
                    [Keys["ObjectInfo"]["GraphicModel"]] = boxDrawable,
                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                    [Keys["ObjectInfo"]["Group"]]        = { "NoLight"},
                    [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = tilesTexture },
                    });
              
OnKeyDown(KeyCode["Z"], 
    function() 
        local tempCam = Camera({
                    [Keys["Camera"]["Eye"]]             = regularCam.Eye,
                    [Keys["Camera"]["TargetMagnitude"]] = regularCam.TargetMagnitude,
                    [Keys["Camera"]["Up"]]              = regularCam.Up,
                    [Keys["Camera"]["Roll"]]            = regularCam.Roll,
                    [Keys["Camera"]["Pitch"]]           = regularCam.Pitch,
                    [Keys["Camera"]["Yaw"]]             = regularCam.Yaw,
                    [Keys["Camera"]["NearZ"]]           = 0.01,              
                    [Keys["Camera"]["FarZ"]]            = 5000.0,
                    [Keys["Camera"]["ClearColor"]]      = Vector4(1.0, 0.0, 0.0, 1.0),
                    [Keys["Camera"]["InclusionState"]]  = InclusionType["Exclude"],
                    [Keys["Camera"]["InclusionList"]]   = {"Text", "NoMainDraw"},
                    [Keys["Camera"]["Texture"]]         = regularCam.Texture,
                   }); 
        local screenTexture = TakeScreenShot({
                                          [Keys["ScreenShot"]["Width"]]         = 1080,
                                          [Keys["ScreenShot"]["Height"]]        = 712,
                                          [Keys["ScreenShot"]["CameraID"]]      = tempCam, });
        WaitToProcessGraphic(
            function()
                floor2.Texture = { ["Texture"] = screenTexture; };
            end
        );
    end
);

OnKeyDown(KeyCode["X"], 
    function() 
        floor2.Texture = { ["Texture"] = tilesTexture };
    end
);
