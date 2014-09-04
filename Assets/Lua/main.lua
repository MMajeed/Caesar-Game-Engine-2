require("camera")
require("Helper")
require("Text")
require("Information")
require("SkyBox")
require("floor")
--require("SphereMirror")
--require("PhysicsDemo")
--require("StickPerson")
--require("RandomAnimation")
require("LightSetup")
require("LightClasses/DirectionalLight")
require("LightClasses/PointLight")
require("LightClasses/SpotLight")

         
local light1 = DirectionalLight({
                    ["Diffuse"]   = Vector4(1.0, 1.0, 1.0),
                    ["Ambient"]   = Vector4(0.5, 0.5, 0.5),
                    ["Specular"]  = Vector4(0.1, 0.1, 0.1),
                    ["Direction"] = Vector4(0.0, 0.785, 0.1)});
AddLight(light1);
local light2 = PointLight({
                    ["Diffuse"]     = Vector4(0.8, 0.8, 0.0),
                    ["Ambient"]     = Vector4(0.3, 0.3, 0.0),
                    ["Specular"]    = Vector4(0.0, 0.0, 0.0),
                    ["Position"]    = Vector4(0.0, 10.0, -45.0),
                    ["Range"]       = 40,
                    ["Attenuation"] = Vector4(1.0, 0.0, 0.0)});
AddLight(light2);
local light3 = SpotLight({
                    ["Diffuse"]     = Vector4(0.0, 0.0, 0.8),
                    ["Ambient"]     = Vector4(0.0, 0.0, 0.1),
                    ["Specular"]    = Vector4(0.0, 0.0, 1.0),
                    ["Position"]    = Vector4(0.0, 10.0, 30.0),
                    ["Direction"]   = Vector4(0.7853, -3.14, -3.14),
                    ["Attenuation"] = Vector4(0.0, 0.1, 0.0),
                    ["Spot"]        = 0.5,
                    ["Range"]       = 20,});     
AddLight(light3);

local ironManTexture= BasicTexture("Assets/Texture/Iron_Man_mark_4_D.jpg");
local ironManMesh = GraphicModel(LoadDefaultModel("Assets/Models/Iron_Man_mark_4.obj"));
local sphereGraphic = GraphicModel(LoadDefaultModel("Assets/Models/Sphere.obj"));
local VSShader = VertexShader("Assets/ShaderFiles/VS_Basic.cso");
local PSColorShader = PixelShader("Assets/ShaderFiles/PS_Color.cso");
local PSTextureShader = PixelShader("Assets/ShaderFiles/PS_Texture.cso");
local PSLightShader = PixelShader("Assets/ShaderFiles/PS_Light.cso");

local ironMan = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(0.0, 0.5, -30.0),
                    [Keys["ObjectInfo"]["Rotation"]]     = Vector4(0.0, 3.14, 0.0),
                    [Keys["ObjectInfo"]["GraphicModel"]] = ironManMesh,
                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSTextureShader,
                    [Keys["ObjectInfo"]["UserData"]]     = { ["Color"] = Vector4(1.0, 1.0, 1.0) },
                    [Keys["ObjectInfo"]["Texture"]]      = { ["Texture"] = ironManTexture },
                    [Keys["ObjectInfo"]["FillMode"]]     = FillMode["Wireframe"],
                    [Keys["ObjectInfo"]["CullMode"]]     = CullMode["None"],
                    [Keys["ObjectInfo"]["Depth"]]        = true,
                    [Keys["ObjectInfo"]["Priority"]]     = -1000.0,
                    [Keys["ObjectInfo"]["UserData"]]     = { 
                                                              ["Diffuse"]   = Vector4(0.51, 0.53, 0.58, 0.5),
                                                              ["Ambient"]   = Vector4(0.5, 0.5, 0.5),
                                                              ["Specular"]  = Vector4(0.5, 0.5, 0.5, 0.5) },
                     });
                        
for zIndex = 0, 2, 1 do
    for xIndex = 1, 10, 1 do
        local x = ((xIndex % 10) - 5) * 4;
        local y = 2;
        local z = -20 + (zIndex * 20);
        local sphereObject = Object({
                    [Keys["ObjectInfo"]["Location"]]     = Vector4(x, y, z),
                    [Keys["ObjectInfo"]["GraphicModel"]] = sphereGraphic,
                    [Keys["ObjectInfo"]["VertexShader"]] = VSShader,
                    [Keys["ObjectInfo"]["PixelShader"]]  = PSLightShader,
                    [Keys["ObjectInfo"]["UserData"]]     = { 
                                                              ["Color"]     = Vector4(1.0, 1.0, 1.0),
                                                              ["Diffuse"]   = Vector4(0.51, 0.53, 0.58, 0.5),
                                                              ["Ambient"]   = Vector4(0.5, 0.5, 0.5),
                                                              ["Specular"]  = Vector4(0.5, 0.5, 0.5, 0.5) },
                                    });
    end
end

Sleep(5000, function (time)
    local textExample = Text2D("Hello!",  Vector4(50.0, 200.0, 0.0));
    textExample:Scale(Vector4(5.0, 5.0, 5.0));
    Sleep(5000, function (time)
        textExample:Release();
    end);
end);

OnKeyDown(KeyCode["ESCAPE"], function() Quit(); end);-- Left

--lightPos = 10.0;
--OnKeyDown(KeyCode["B"], 
--    function()   
--		spotLight = SpotLight(
--					  {[Keys["Light"]["Diffuse"]]     = Vector4(0.0, 0.0, 0.8),
--                       [Keys["Light"]["Ambient"]]     = Vector4(0.0, 0.0, 0.5),
--                       [Keys["Light"]["Specular"]]    = Vector4(0.0, 0.0, 1.0),
--                       [Keys["Light"]["Position"]]    = Vector4(0.0, 10.0, lightPos),
--                       [Keys["Light"]["Direction"]]   = Vector4(0.7853, -3.14, -3.14),
--                       [Keys["Light"]["Attenuation"]] = Vector4(0.0, 0.1, 0.0),
--                       [Keys["Light"]["Spot"]]        = 0.5,
--                       [Keys["Light"]["Range"]]       = 20,
--                       [Keys["Light"]["HasShadow"]]   = true,});    
--      lightPos = lightPos - 20.0;
--    end
----);

