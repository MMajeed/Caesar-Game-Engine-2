local floor = {}


boxDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["ModelFile"]]        = LoadModel("Assets/Models/Box.ply"),
                                   [Keys["BasicDrawable"]["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.cso",
                                   [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Generic.cso",});
tilesTexture = BasicTexture("Assets/Texture/Tiles.png");


box1 = Object({[Keys["ObjectInfo"]["Scale"]]       = Vector4(50.0, 0.2, 50.0),
               [Keys["ObjectInfo"]["Diffuse"]]     = Vector4(0.5, 0.5, 0.5, 1.0),
               [Keys["ObjectInfo"]["Ambient"]]     = Vector4(0.1, 0.1, 0.1),
               [Keys["ObjectInfo"]["Specular"]]    = Vector4(0.01, 0.01, 0.01, 0.001),
               [Keys["ObjectInfo"]["DrawableObj"]] = boxDrawable,
               [Keys["ObjectInfo"]["Texture2DObj"]]= tilesTexture,});

                                 
OnKeyDown(KeyCode["Z"], 
    function() 
        local myTexture = TakeScreenShot({[Keys["ScreenShot"]["Width"]]    = 1024,
                                          [Keys["ScreenShot"]["Height"]]   = 1024,
                                          [Keys["ScreenShot"]["CameraID"]] = cam, });
        WaitToProcessGraphic(
            function()
                box1.Texture2D = {};
                box1.Texture2D = {myTexture};
            end
        );
    end
);

OnKeyDown(KeyCode["X"], 
    function() 
        box1.Texture2D = {};
        box1:Add2DTexture(tilesTexture);
    end
);

return camera

