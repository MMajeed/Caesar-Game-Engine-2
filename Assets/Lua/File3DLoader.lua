local File3DLoader = {}

function LoadDefaultModel(FileName)
    return LoadScene(FileName)["Model"][1];
end

return File3DLoader;

