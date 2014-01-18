require("Text")

local Information = {}


local mousePositionText = Text2D("",  Vector4(0.0, 0.0, 0.0));
local windowPositionText = Text2D("",  Vector4(0.0, 20.0, 0.0));
local windowSizeText = Text2D("",  Vector4(0.0, 40.0, 0.0));
local clientSizeText = Text2D("",  Vector4(0.0, 60.0, 0.0));

MoveWindow(200, 100);
ReizeClient(768, 1024);
--FullScreen();

function UpdateText()
    local pos = MouseLocation();
    local textPos = "Mouse Pos: X: " .. pos["X"] .. " Y: ".. pos["Y"];
    mousePositionText:EditText(textPos);
    
    local pos = GetWindowsLocs();
    local textPos = "Windows Location: X: " .. pos["X"] .. " Y: ".. pos["Y"];
    windowPositionText:EditText(textPos);
    
    local pos = GetWindowsSize();
    local textPos = "Windows Size: Height: " .. pos["Height"] .. " Width: ".. pos["Width"];
    windowSizeText:EditText(textPos);
    
    local pos = GetClientsSize();
    local textPos = "Client Size: Height: " .. pos["Height"] .. " Width: ".. pos["Width"];
    clientSizeText:EditText(textPos);
end

LoopCall(50, UpdateText);


return Information

