require("Text")

local mousePositionText = Text2D("", Vector4(0.0, 0.0, 0.0));
local windowPositionText = Text2D("", Vector4(0.0, 20.0, 0.0));
local windowSizeText = Text2D("", Vector4(0.0, 40.0, 0.0));
local clientSizeText = Text2D("", Vector4(0.0, 60.0, 0.0));
local frameRate = Text2D("", Vector4(0.0, 80.0, 0.0));

MoveWindow(100, 100);
ReizeClient(768, 1366);
ResizeRender(768, 1366);
-- FullScreen();
VSync(true);

function ResizeFunction(ID, Width, Height)
	ResizeRender(Height, Width);
end
CallOnResize(ResizeFunction);

function UpdateText()
	local pos = MouseLocation();
	local textPos = "Mouse Pos: X: " .. pos["X"] .. " Y: " .. pos["Y"];
	mousePositionText:EditText(textPos);

	local pos = GetWindowLocs();
	local textPos = "Windows Location: X: " .. pos["X"] .. " Y: " .. pos["Y"];
	windowPositionText:EditText(textPos);

	local pos = GetWindowSize();
	local textPos = "Windows Size: Height: " .. pos["Height"] .. " Width: " .. pos["Width"];
	windowSizeText:EditText(textPos);

	local pos = GetClientSize();
	local textPos = "Client Size: Height: " .. pos["Height"] .. " Width: " .. pos["Width"];
	clientSizeText:EditText(textPos);
end

LoopCall(50, UpdateText);

local lastTimeCheck = 0.0;
local lastGraphicFrameCheck = GetGraphicFrame();
local lastInputFrameCheck = GetInputFrame();
local lastScriptFrameCheck = GetScriptFrame();
local lastAnimationFrameCheck = GetAnimationFrame();
local lastPhysicsFrameCheck = GetPhysicsFrame();

function UpdateFrameText()
	local currentTime = GetTimeSinceStart();
	local timeDifference = currentTime - lastTimeCheck;
	lastTimeCheck = currentTime;

	local graphicFrameCount = GetGraphicFrame();
	local graphicFrameDifference = graphicFrameCount - lastGraphicFrameCheck;
	lastGraphicFrameCheck = graphicFrameCount;
	local graphicFrame = graphicFrameDifference / timeDifference;

	local inputFrameCount = GetInputFrame();
	local inputFrameDifference = inputFrameCount - lastInputFrameCheck;
	lastInputFrameCheck = inputFrameCount;
	local inputFrame = inputFrameDifference / timeDifference;

	local scriptFrameCount = GetScriptFrame();
	local scriptFrameDifference = scriptFrameCount - lastScriptFrameCheck;
	lastScriptFrameCheck = scriptFrameCount;
	local scriptFrame = scriptFrameDifference / timeDifference;

	local animationFrameCount = GetAnimationFrame();
	local animationFrameDifference = animationFrameCount - lastAnimationFrameCheck;
	lastAnimationFrameCheck = animationFrameCount;
	local animationFrame = animationFrameDifference / timeDifference;

	local physicFrameCount = GetPhysicsFrame();
	local physicFrameDifference = physicFrameCount - lastPhysicsFrameCheck;
	lastPhysicsFrameCheck = physicFrameCount;
	local physicFrame = physicFrameDifference / timeDifference;

	local message = "Frame Rate:" ..
	" Graphic: " .. string.format("%3.2f", graphicFrame) ..
	" Input: " .. string.format("%3.2f", inputFrame) ..
	" Script: " .. string.format("%3.2f", scriptFrame) ..
	" Animation: " .. string.format("%3.2f", animationFrame) ..
	" Physics: " .. string.format("%3.2f", physicFrame);
	frameRate:EditText(message);
end
UpdateFrameText();
LoopCall(1000, UpdateFrameText);
