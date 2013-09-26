require("camera")

ClearScreen(0.5, 0.5, 0.5)

boxDrawable = AddBasicDrawableObject({[Keys["ModelFile"]]        = "Assets/PlyFiles/1x1_2Tri_Quad_2_Sided.ply",
                                      [Keys["VertexShaderFile"]] = "Assets/ShaderFiles/VS_0_Regular.fx",
                                      [Keys["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_0_Basic.fx",})
                                      
b = AddObject({[Keys["GraphicDrawableID"]]   = boxDrawable,})



function foo() 
    h = 1234;
end

for i=1,500,1 do
    OnKeyDown(string.byte('A'), foo);
end