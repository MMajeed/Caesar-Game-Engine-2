#include "CBufferSetup.h"

#include <D3DCompiler.h>
#include "CBHardVariables.h"

CBufferSetup::CBufferSetup(){}
void CBufferSetup::Init(const std::vector<char>& compiledShader, unsigned int bufferNum)
{
	ID3D11ShaderReflection* pReflector = NULL;
	D3DReflect(compiledShader.data(), compiledShader.size(),
			   IID_ID3D11ShaderReflection, (void**)&pReflector);

	ID3D11ShaderReflectionConstantBuffer* cBufferRefl = pReflector->GetConstantBufferByIndex(bufferNum);

	if(cBufferRefl)
	{
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		cBufferRefl->GetDesc(&bufferDesc);
		
		this->cbufferData.resize(bufferDesc.Size);

		for(unsigned int i = 0; i < bufferDesc.Variables; ++i)
		{
			ID3D11ShaderReflectionVariable* variableRefl = cBufferRefl->GetVariableByIndex(i);

			if(variableRefl)
			{
				D3D11_SHADER_VARIABLE_DESC varDesc;
				variableRefl->GetDesc(&varDesc);

				std::string name = varDesc.Name;
				auto spawnFunc = VariableTypes[name];
				if(spawnFunc)
				{
					std::shared_ptr<CBufferVariables> newCBVariable = spawnFunc(this->cbufferData, varDesc.StartOffset);
					this->variables.push_back(newCBVariable);
				}
			}
		}
	}
}
void CBufferSetup::Run(std::shared_ptr<ObjectEntity> object, const SceneInfo& si)
{
	for(auto variableIter = this->variables.begin();
		variableIter != this->variables.end();
		++variableIter)
	{
		(*variableIter)->Update(object, si);
	}
}
const std::vector<char>& CBufferSetup::GetCBData()
{
	return this->cbufferData;
}
unsigned int CBufferSetup::GetCBSize()
{
	return this->cbufferData.size();
}
std::shared_ptr<CBufferSetup> CBufferSetup::Spawn(const std::vector<char>& compiledGeometryShader, unsigned int bufferNum)
{
	std::shared_ptr<CBufferSetup> newObject(new CBufferSetup());

	newObject->Init(compiledGeometryShader, bufferNum);

	return newObject;
}