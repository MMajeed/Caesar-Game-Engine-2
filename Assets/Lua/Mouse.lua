require("Text")

local Mouse = {}


local positionText = Text2D("",  Vector4(0.0, 0.0, 0.0));

function UpdateMousePosition()
    local pos = MouseLocation();
    local textPos = "X: " .. pos["X"] .. " Y: ".. pos["Y"];
    positionText:EditText(textPos);
end

LoopCall(16, UpdateMousePosition);


Sleep(5000, function (time)
    local textExample = Text2D("Hello!",  Vector4(50.0, 50.0, 0.0));
    textExample:Scale(Vector4(5.0, 5.0, 5.0));
    Sleep(5000, function (time)
        textExample:Release();
    end);
end);

return Mouse

