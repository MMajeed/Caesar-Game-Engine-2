require("Helper")

SpotLight = class(
    function(self, ResourceArray)        
        assert(type(ResourceArray) == 'table');
        
        self.CallOnUpdate = {};
        self:SetDiffuse(ResourceArray["Diffuse"]);
        self:SetAmbient(ResourceArray["Ambient"]);
        self:SetSpecular(ResourceArray["Specular"]);
        self:SetPosition(ResourceArray["Position"]);
        self:SetDirection(ResourceArray["Direction"]);
        self:SetAttenuation(ResourceArray["Attenuation"]);
        self:SetSpot(ResourceArray["Spot"]);
        self:SetRange(ResourceArray["Range"]);
    end)
           
--  --------------------Start Diffuse--------------------
function SpotLight:SetDiffuse(value)
    if(value ~= nil) then
        self.Diffuse = value;
    else
        self.Diffuse = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Diffuse", self.Diffuse) end
end

function SpotLight:GetDiffuse()
    return self.Diffuse;
end
--  --------------------End Diffuse--------------------

--  --------------------Start Ambient--------------------
function SpotLight:SetAmbient(value)
    if(value ~= nil) then
        self.Ambient = value;
    else
        self.Ambient = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Ambient", self.Ambient) end
end

function SpotLight:GetAmbient()
    return self.Ambient;
end
--  --------------------End Ambient--------------------

--  --------------------Start Specular--------------------
function SpotLight:SetSpecular(value)
    if(value ~= nil) then
        self.Specular = value;
    else
        self.Specular = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Specular", self.Specular) end
end

function SpotLight:GetSpecular()
    return self.Specular;
end
--  --------------------End Specular--------------------

--  --------------------Start Position--------------------
function SpotLight:SetPosition(value)
    if(value ~= nil) then
        self.Position = value;
    else
        self.Position = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Position", self.Position) end
end

function SpotLight:GetPosition()
    return self.Position;
end
--  --------------------End Position--------------------

--  --------------------Start Direction--------------------
function SpotLight:SetDirection(value)
    if(value ~= nil) then
        self.Direction = value;
    else
        self.Direction = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Direction", self.Direction) end
end

function SpotLight:GetDirection()
    return self.Direction;
end
--  --------------------End Direction--------------------

--  --------------------Start Attenuation--------------------
function SpotLight:SetAttenuation(value)
    if(value ~= nil) then
        self.Attenuation = value;
    else
        self.Attenuation = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Attenuation", self.Attenuation) end
end

function SpotLight:GetAttenuation()
    return self.Attenuation;
end
--  --------------------End Attenuation--------------------

--  --------------------Start Spot--------------------
function SpotLight:SetSpot(value)
    if(value ~= nil) then
        self.Spot = value;
    else
        self.Spot = 0.0;
    end
    for key,value in pairs(self.CallOnUpdate) do value("Spot", self.Spot) end
end

function SpotLight:GetSpot()
    return self.Spot;
end
--  --------------------End Spot--------------------

--  --------------------Start Range--------------------
function SpotLight:SetRange(value)
    if(value ~= nil) then
        self.Range = value;
    else
        self.Range = 0.0;
    end
    for key,value in pairs(self.CallOnUpdate) do value("Range", self.Range) end
end

function SpotLight:GetRange()
    return self.Range;
end
--  --------------------End Range--------------------

local PSSpotLight = PixelShader("Assets/ShaderFiles/4_PS_SpotLight.cso");

function SpotLight:GetShader()
    return PSSpotLight;
end

function SpotLight:GetResource()
    local returnValue = {};
    
    returnValue["Diffuse"] = self.Diffuse;
    returnValue["Ambient"] = self.Ambient;
    returnValue["Specular"] = self.Specular;
    returnValue["Position"] = self.Position;
    returnValue["Direction"] = self.Direction;
    returnValue["Attenuation"] = self.Attenuation;
    returnValue["Spot"] = self.Spot;
    returnValue["Range"] = self.Range;
    
    return returnValue;
end


function SpotLight:AddToCallOnUpdate(func)
      table.insert(self.CallOnUpdate, func);
end
