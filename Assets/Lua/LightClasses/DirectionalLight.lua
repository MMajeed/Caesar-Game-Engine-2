require("Helper")

DirectionalLight = class(
    function(self, ResourceArray)
        assert(type(ResourceArray) == 'table');

        self.CallOnUpdate = {};
        self:SetDiffuse(ResourceArray["Diffuse"]);
        self:SetAmbient(ResourceArray["Ambient"]);
        self:SetSpecular(ResourceArray["Specular"]);
        self:SetDirection(ResourceArray["Direction"]);
    end)
          
--  --------------------Start Diffuse--------------------
function DirectionalLight:SetDiffuse(value)
    if(value ~= nil) then
        self.Diffuse = value;
    else
        self.Diffuse = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Diffuse", self.Diffuse) end
end

function DirectionalLight:GetDiffuse()
    return self.Diffuse;
end
--  --------------------End Diffuse--------------------

--  --------------------Start Ambient--------------------
function DirectionalLight:SetAmbient(value)
    if(value ~= nil) then
        self.Ambient = value;
    else
        self.Ambient = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Ambient", self.Ambient) end
end

function DirectionalLight:GetAmbient()
    return self.Ambient;
end
--  --------------------End Ambient--------------------

--  --------------------Start Specular--------------------
function DirectionalLight:SetSpecular(value)
    if(value ~= nil) then
        self.Specular = value;
    else
        self.Specular = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Specular", self.Specular) end
end

function DirectionalLight:GetSpecular()
    return self.Specular;
end
--  --------------------End Specular--------------------

--  --------------------Start Direction--------------------
function DirectionalLight:SetDirection(value)
    if(value ~= nil) then
        self.Direction = value;
    else
        self.Direction = Vector4(0.0, 0.0, 0.0);
    end
    for key,value in pairs(self.CallOnUpdate) do value("Direction", self.Direction) end
end

function DirectionalLight:GetDirection()
    return self.Direction;
end
--  --------------------End Direction--------------------

local PSDirectionalLight = PixelShader("Assets/ShaderFiles/2_PS_DirectionalLight.cso");

function DirectionalLight:GetShader()
    return PSDirectionalLight;
end

function DirectionalLight:GetResource()
    local returnValue = {};
    
    returnValue["Diffuse"] = self.Diffuse;
    returnValue["Ambient"] = self.Ambient;
    returnValue["Specular"] = self.Specular;
    returnValue["Direction"] = self.Direction;
    
    return returnValue;
end


function DirectionalLight:AddToCallOnUpdate(func)
      table.insert(self.CallOnUpdate, func);
end
