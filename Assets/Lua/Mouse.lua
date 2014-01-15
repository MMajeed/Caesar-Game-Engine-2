require("Text")

local Mouse = {}


local positionText = Text2D("",  Vector4(0.0, 0.0, 0.0));

function UpdateMousePosition()
    local pos = MouseLocation();
    local textPos = "X: " .. pos["X"] .. " Y: ".. pos["Y"];
    positionText:EditText(textPos);
end

LoopCall(16, UpdateMousePosition);


return Mouse

