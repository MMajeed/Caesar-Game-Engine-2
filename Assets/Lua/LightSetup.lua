local LightSetup = {}

directionLight = DirectionalLight({[Keys["Light"]["Diffuse"]]   = Vector4(1.0, 1.0, 1.0),
                                   [Keys["Light"]["Ambient"]]   = Vector4(0.5, 0.5, 0.5),
                                   [Keys["Light"]["Specular"]]  = Vector4(0.3, 0.3, 0.3),
                                   [Keys["Light"]["Direction"]] = Vector4(0.0, 0.785, 0.1),});

pointLight = PointLight({[Keys["Light"]["Diffuse"]]     = Vector4(1.0, 1.0, 0.0),
                         [Keys["Light"]["Ambient"]]     = Vector4(0.0, 0.0, 0.0),
                         [Keys["Light"]["Specular"]]    = Vector4(0.0, 0.0, 0.0),
                         [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, -45.0),
                         [Keys["Light"]["Range"]]       = 40,
                         [Keys["Light"]["Attenuation"]] = Vector4(1.0, 0.0, 0.0),});
            
spotLight = SpotLight({[Keys["Light"]["Diffuse"]]     = Vector4(0.0, 0.0, 1.0),
                       [Keys["Light"]["Ambient"]]     = Vector4(0.0, 0.0, 0.0),
                       [Keys["Light"]["Specular"]]    = Vector4(0.2, 0.2, 0.2),
                       [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, 35.0),
                       [Keys["Light"]["Direction"]]   = Vector4(0.7853, -3.14, -3.14),
                       [Keys["Light"]["Attenuation"]] = Vector4(0.0, 0.1, 0.0),
                       [Keys["Light"]["Spot"]]        = 0.5,
                       [Keys["Light"]["Range"]]       = 20,});
--spotLight:ApplyShadow();

return LightSetup

