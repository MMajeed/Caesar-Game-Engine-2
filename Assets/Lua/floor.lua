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
                        [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = tilesTexture },
                        });
                        
local floor2 = Object({
                        [Keys["ObjectInfo"]["Location"]]     = Vector4(0.0, 0.0, 0.0),
                        [Keys["ObjectInfo"]["Scale"]]        = Vector4(100.0, 0.5, 100.0),
                        [Keys["ObjectInfo"]["GraphicModel"]] = boxDrawable,
                        [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                        [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                        [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = tilesTexture },
                        });

local floor3 = Object({
                        [Keys["ObjectInfo"]["Location"]]     = Vector4(-100.0, 0.0, 0.0),
                        [Keys["ObjectInfo"]["Scale"]]        = Vector4(100.0, 0.5, 100.0),
                        [Keys["ObjectInfo"]["GraphicModel"]] = boxDrawable,
                        [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                        [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                        [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = tilesTexture },
                        });

                                 
OnKeyDown(KeyCode["Z"], 
    function() 
        local myTexture = TakeScreenShot({[Keys["ScreenShot"]["Width"]]    = 1024,
                                          [Keys["ScreenShot"]["Height"]]   = 1024,
                                          [Keys["ScreenShot"]["CameraID"]] = regularCam, });
        WaitToProcessGraphic(
            function()
                floor1.Texture = { ["Texture"] = myTexture };
            end
        );
    end
);

OnKeyDown(KeyCode["X"], 
    function() 
       floor1.Texture = { };
    end
);

