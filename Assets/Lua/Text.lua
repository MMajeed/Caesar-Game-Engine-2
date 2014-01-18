require("Helper")

local Text = {}

FontData = class(function(acc, left, right, size)
              acc.Left = left;
              acc.Right = right;
              acc.Size = size;
           end)
           
local FontDataTable = {};
FontDataTable["!"] 	= FontData(0.000000, 0.000977, 1);
FontDataTable["\""] = FontData(0.001953, 0.004883, 3);
FontDataTable["#"] 	= FontData(0.005859, 0.013672, 8);
FontDataTable["$"] 	= FontData(0.014648, 0.019531, 5);
FontDataTable["%"] 	= FontData(0.020508, 0.030273, 10);
FontDataTable["&"] 	= FontData(0.031250, 0.039063, 8);
FontDataTable["'"] 	= FontData(0.040039, 0.041016, 1);
FontDataTable["("] 	= FontData(0.041992, 0.044922, 3);
FontDataTable[")"] 	= FontData(0.045898, 0.048828, 3);
FontDataTable["*"] 	= FontData(0.049805, 0.054688, 5);
FontDataTable["+"] 	= FontData(0.055664, 0.062500, 7);
FontDataTable[","] 	= FontData(0.063477, 0.064453, 1);
FontDataTable["-"] 	= FontData(0.065430, 0.068359, 3);
FontDataTable["."] 	= FontData(0.069336, 0.070313, 1);
FontDataTable["/"] 	= FontData(0.071289, 0.075195, 4);
FontDataTable["0"] 	= FontData(0.076172, 0.082031, 6);
FontDataTable["1"] 	= FontData(0.083008, 0.085938, 3);
FontDataTable["2"] 	= FontData(0.086914, 0.092773, 6);
FontDataTable["3"] 	= FontData(0.093750, 0.099609, 6);
FontDataTable["4"] 	= FontData(0.100586, 0.106445, 6);
FontDataTable["5"] 	= FontData(0.107422, 0.113281, 6);
FontDataTable["6"] 	= FontData(0.114258, 0.120117, 6);
FontDataTable["7"] 	= FontData(0.121094, 0.126953, 6);
FontDataTable["8"] 	= FontData(0.127930, 0.133789, 6);
FontDataTable["9"] 	= FontData(0.134766, 0.140625, 6);
FontDataTable[":"] 	= FontData(0.141602, 0.142578, 1);
FontDataTable[";"] 	= FontData(0.143555, 0.144531, 1);
FontDataTable["<"] 	= FontData(0.145508, 0.151367, 6);
FontDataTable["="] 	= FontData(0.152344, 0.159180, 7);
FontDataTable[">"] 	= FontData(0.160156, 0.166016, 6);
FontDataTable["?"] 	= FontData(0.166992, 0.171875, 5);
FontDataTable["@"] 	= FontData(0.172852, 0.184570, 12);
FontDataTable["A"] 	= FontData(0.185547, 0.194336, 9);
FontDataTable["B"] 	= FontData(0.195313, 0.202148, 7);
FontDataTable["C"] 	= FontData(0.203125, 0.209961, 7);
FontDataTable["D"] 	= FontData(0.210938, 0.217773, 7);
FontDataTable["E"] 	= FontData(0.218750, 0.225586, 7);
FontDataTable["F"] 	= FontData(0.226563, 0.232422, 6);
FontDataTable["G"] 	= FontData(0.233398, 0.241211, 8);
FontDataTable["H"] 	= FontData(0.242188, 0.249023, 7);
FontDataTable["I"] 	= FontData(0.250000, 0.250977, 1);
FontDataTable["J"] 	= FontData(0.251953, 0.256836, 5);
FontDataTable["K"] 	= FontData(0.257813, 0.265625, 8);
FontDataTable["L"] 	= FontData(0.266602, 0.272461, 6);
FontDataTable["M"] 	= FontData(0.273438, 0.282227, 9);
FontDataTable["N"] 	= FontData(0.283203, 0.290039, 7);
FontDataTable["O"] 	= FontData(0.291016, 0.298828, 8);
FontDataTable["P"] 	= FontData(0.299805, 0.306641, 7);
FontDataTable["Q"] 	= FontData(0.307617, 0.315430, 8);
FontDataTable["R"] 	= FontData(0.316406, 0.323242, 7);
FontDataTable["S"] 	= FontData(0.324219, 0.331055, 7);
FontDataTable["T"] 	= FontData(0.332031, 0.338867, 7);
FontDataTable["U"] 	= FontData(0.339844, 0.346680, 7);
FontDataTable["V"] 	= FontData(0.347656, 0.356445, 9);
FontDataTable["W"] 	= FontData(0.357422, 0.370117, 13);
FontDataTable["X"] 	= FontData(0.371094, 0.377930, 7);
FontDataTable["Y"] 	= FontData(0.378906, 0.385742, 7);
FontDataTable["Z"] 	= FontData(0.386719, 0.393555, 7);
FontDataTable["["] 	= FontData(0.394531, 0.396484, 2);
FontDataTable["\\"] = FontData(0.397461, 0.401367, 4);
FontDataTable["]"] 	= FontData(0.402344, 0.404297, 2);
FontDataTable["^"] 	= FontData(0.405273, 0.410156, 5);
FontDataTable["_"] 	= FontData(0.411133, 0.417969, 7);
FontDataTable["`"] 	= FontData(0.418945, 0.420898, 2);
FontDataTable["a"] 	= FontData(0.421875, 0.426758, 5);
FontDataTable["b"] 	= FontData(0.427734, 0.432617, 5);
FontDataTable["c"] 	= FontData(0.433594, 0.438477, 5);
FontDataTable["d"] 	= FontData(0.439453, 0.444336, 5);
FontDataTable["e"] 	= FontData(0.445313, 0.450195, 5);
FontDataTable["f"] 	= FontData(0.451172, 0.455078, 4);
FontDataTable["g"] 	= FontData(0.456055, 0.460938, 5);
FontDataTable["h"] 	= FontData(0.461914, 0.466797, 5);
FontDataTable["i"] 	= FontData(0.467773, 0.468750, 1);
FontDataTable["j"] 	= FontData(0.469727, 0.472656, 3);
FontDataTable["k"] 	= FontData(0.473633, 0.478516, 5);
FontDataTable["l"] 	= FontData(0.479492, 0.480469, 1);
FontDataTable["m"] 	= FontData(0.481445, 0.490234, 9);
FontDataTable["n"] 	= FontData(0.491211, 0.496094, 5);
FontDataTable["o"] 	= FontData(0.497070, 0.501953, 5);
FontDataTable["p"] 	= FontData(0.502930, 0.507813, 5);
FontDataTable["q"] 	= FontData(0.508789, 0.513672, 5);
FontDataTable["r"] 	= FontData(0.514648, 0.517578, 3);
FontDataTable["s"] 	= FontData(0.518555, 0.523438, 5);
FontDataTable["t"] 	= FontData(0.524414, 0.527344, 3);
FontDataTable["u"] 	= FontData(0.528320, 0.533203, 5);
FontDataTable["v"] 	= FontData(0.534180, 0.539063, 5);
FontDataTable["w"] 	= FontData(0.540039, 0.548828, 9);
FontDataTable["x"] 	= FontData(0.549805, 0.554688, 5);
FontDataTable["y"] 	= FontData(0.555664, 0.560547, 5);
FontDataTable["z"] 	= FontData(0.561523, 0.566406, 5);
FontDataTable["{"] 	= FontData(0.567383, 0.570313, 3);
FontDataTable["|"] 	= FontData(0.571289, 0.572266, 1);
FontDataTable["}"] 	= FontData(0.573242, 0.576172, 3);
FontDataTable["~"] 	= FontData(0.577148, 0.583984, 7);

Text2D = class(function(self, text, location) 
                self.Text = text;
                self.SpriteModel = Model();
                self.SpriteDrawable = BasicDrawableObject({[Keys["BasicDrawable"]["Dimension"]]        = Dimension["2D"],
                                                           [Keys["BasicDrawable"]["PixelShaderFile"]]  = "Assets/ShaderFiles/PS_1_Font.cso",
                                                          });
                self.SpriteTexture = BasicTexture("Assets/Font/font.dds");
                
                self.SpriteObj = Object({[Keys["ObjectInfo"]["Location"]]     = location,
                                         [Keys["ObjectInfo"]["DrawableObj"]]  = self.SpriteDrawable,
                                         [Keys["ObjectInfo"]["Texture2DObj"]] = self.SpriteTexture,
                                         [Keys["ObjectInfo"]["Diffuse"]]      = Vector4(1.0, 1.0, 1.0, 1.0),
                                        });
                self:Set();
             end)

function Text2D:Set()
    local Length = string.len(self.Text)
    
    local verticeArray = {};
    
    local drawX = 0.0; local drawY = 0.0;
    local index = 1;
    for i = 1, Length do
        local char = string.sub(self.Text, i, i);
        local fontChar = FontDataTable[char];
        if(fontChar ~= nil) then
            verticeArray[index] = Vertice({["Point"] = Vector4(drawX, drawY, 0.0), 
                                           ["Texture"] = Vector4(fontChar.Left, 0.0, 0.0), });
            index = index + 1;
            verticeArray[index] = Vertice({["Point"] = Vector4( (drawX + fontChar.Size), (drawY + 16), 0.0), 
                                           ["Texture"] = Vector4(fontChar.Right, 1.0, 0.0), });
            index = index + 1;
            verticeArray[index] = Vertice({["Point"] = Vector4(drawX, (drawY + 16), 0.0), 
                                           ["Texture"] = Vector4(fontChar.Left, 1.0, 0.0), });
            index = index + 1;
            verticeArray[index] = Vertice({["Point"] = Vector4(drawX, drawY, 0.0), 
                                           ["Texture"] = Vector4(fontChar.Left, 0.0, 0.0), });
            index = index + 1;
            verticeArray[index] = Vertice({["Point"] = Vector4( (drawX + fontChar.Size), drawY, 0.0), 
                                           ["Texture"] = Vector4(fontChar.Right, 0.0, 0.0), });
            index = index + 1;
            verticeArray[index] = Vertice({["Point"] = Vector4( (drawX + fontChar.Size), (drawY + 16), 0.0), 
                                           ["Texture"] = Vector4(fontChar.Right, 1.0, 0.0), });
            index = index + 1;
            drawX = drawX + fontChar.Size + 1.0;
        else
            drawX = drawX + 3;
        end        
    end
    local faces = {};
    for i = -1, index do
        table.insert(faces,i - 1);
    end
    
    local spriteModel = Model();
    spriteModel.Vertices = verticeArray;
    spriteModel.Faces = faces;
    self.SpriteDrawable:ChangeModel(spriteModel);
end

function Text2D:EditText(text)
    if(self.Text ~= text) then
        self.Text = text;
        self:Set();
    end
end

function Text2D:EditLocation(loc)
    self.SpriteObj.Location = loc;
end

function Text2D:Scale(size)
    self.SpriteObj.Scale = size;
end;

function Text2D:Release()
    self.SpriteDrawable:Release();
    self.SpriteTexture:Release();    
    self.SpriteObj:Release();
end

return Text

