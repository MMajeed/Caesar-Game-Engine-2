local File3DLoader = {}

function LoadDefaultModel(FileName)
    return LoadScene(FileName)[1];
end

function LoadDefaultAnimation(FileName)
    local model, animation = LoadScene(FileName);
    return animation[1];
end

return File3DLoader;

