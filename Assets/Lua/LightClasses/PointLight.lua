require("Helper")

PointLight = class(
    function(self, ResourceArray)        
        assert(type(ResourceArray) == 'table');

        self.CallOnUpdate = {};
        self:SetDiffuse(ResourceArray["Diffuse"]);
        self:SetAmbient(ResourceArray["Ambient"]);
        self:SetSpecular(ResourceArray["Specular"]);
        self:SetPosition(ResourceArray["Position"]);
        self:SetRange(ResourceArray["Range"]);
        self:SetAttenuation(ResourceArray["Attenuation"]);
    end)
           
--  --------------------Start Diffuse--------------------
function PointLight:SetDiffuse(value)
    if(value ~= nil) then
        self.Diffuse = value;
    else
        self.Diffuse = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Diffuse", self.Diffuse) end
end

function PointLight:GetDiffuse()
    return self.Diffuse;
end
--  --------------------End Diffuse--------------------

--  --------------------Start Ambient--------------------
function PointLight:SetAmbient(value)
    if(value ~= nil) then
        self.Ambient = value;
    else
        self.Ambient = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Ambient", self.Ambient) end
end

function PointLight:GetAmbient()
    return self.Ambient;
end
--  --------------------End Ambient--------------------

--  --------------------Start Specular--------------------
function PointLight:SetSpecular(value)
    if(value ~= nil) then
        self.Specular = value;
    else
        self.Specular = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Specular", self.Specular) end
end

function PointLight:GetSpecular()
    return self.Specular;
end
--  --------------------End Specular--------------------

--  --------------------Start Position--------------------
function PointLight:SetPosition(value)
    if(value ~= nil) then
        self.Position = value;
    else
        self.Position = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Position", self.Position) end
end

function PointLight:GetPosition()
    return self.Position;
end
--  --------------------End Position--------------------

--  --------------------Start Range--------------------
function PointLight:SetRange(value)
    if(value ~= nil) then
        self.Range = value;
    else
        self.Range = 0.0;
    end
    for key,value in pairs(self.CallOnUpdate) do value("Range", self.Range) end
end

function PointLight:GetRange()
    return self.Range;
end
--  --------------------End Range--------------------

--  --------------------Start Attenuation--------------------
function PointLight:SetAttenuation(value)
    if(value ~= nil) then
        self.Attenuation = value;
    else
        self.Attenuation = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Attenuation", self.Attenuation) end
end

function PointLight:GetAttenuation()
    return self.Attenuation;
end
--  --------------------End Attenuation--------------------

local PSPointLight = PixelShader("Assets/ShaderFiles/3_PS_PointLight.cso");

function PointLight:GetShader()
    return PSPointLight;
end

function PointLight:GetResource()
    local returnValue = {};
    
    returnValue["Diffuse"] = self.Diffuse;
    returnValue["Ambient"] = self.Ambient;
    returnValue["Specular"] = self.Specular;
    returnValue["Position"] = self.Position;
    returnValue["Range"] = self.Range;
    returnValue["Attenuation"] = self.Attenuation;
    
    return returnValue;
end


function PointLight:AddToCallOnUpdate(func)
      table.insert(self.CallOnUpdate, func);
end
