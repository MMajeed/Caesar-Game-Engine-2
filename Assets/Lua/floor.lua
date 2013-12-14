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

                                 
OnKeyDown(string.byte("A"), 
    function() 
        
        myTexture = TakeScreenShot({[Keys["ScreenCapture"]["Width"]]        = 1024,
                                    [Keys["ScreenCapture"]["Height"]]       = 1024,
                                    [Keys["ScreenCapture"]["CameraMatrix"]] = ViewCalculation(cam.Eye, cam.TargetMagintude, cam.Up, cam.Pitch, cam.Yaw, cam.Roll), });
        box1:RemoveAll2DTexture();
        box1:Set2DTexture(myTexture);
    end
);

OnKeyDown(string.byte("S"), 
    function() 
        box1:RemoveAll2DTexture();
        box1:Set2DTexture(tilesTexture);
    end
);

return camera

