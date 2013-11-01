local LightSetup = {}

diffuse = Vector4(1.0, 1.0, 1.0);
amibent = Vector4(0.5, 0.5, 0.5);
specular = Vector4(0.3, 0.3, 0.3);
direction = Vector4(0.0, 0.785, 0.1);

directionLight = DirectionalLight(0, diffuse, amibent, specular, direction);

--diffuse = Vector4(1.0, 1.0, 0.0);
--amibent = Vector4(0.0, 0.0, 0.0);
--specular = Vector4(0.0, 0.0, 0.0);
--position = Vector4(0.0, 10.0, -45.0);
--range = 40;
--att =  Vector4(1.0, 0.0, 0.0);

--PointLight(1, diffuse, amibent, specular, position, range, att);

diffuse = Vector4(0.0, 0.0, 1.0);
amibent = Vector4(0.0, 0.0, 0.0);
specular = Vector4(0.2, 0.2, 0.2);
position = Vector4(0.0, 10.0, 35.0);
range = 20;
direction = Vector4(0.7853, -3.14, -3.14);
spot = 0.5;
att =  Vector4(0.0, 0.1, 0.0);

spotLight = SpotLight(2, diffuse, amibent, specular, position, range, direction, spot, att);
spotLight:ApplyShadow();

return LightSetup

