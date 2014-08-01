#include "CBSetup.h"

#include <D3DCompiler.h>
#include "CBHardVariables.h"
#include "CBWeakVariables.h"

CBSetup::CBSetup(){}
void CBSetup::Init(const std::vector<char>& compiledShader, unsigned int bufferNum)
{
	ID3D11ShaderReflection* pReflector = nullptr;
	D3DReflect(compiledShader.data(), compiledShader.size(),
			   IID_ID3D11ShaderReflection, (void**)&pReflector);

	if(pReflector == nullptr){ return; }

	D3D11_SHADER_DESC pDesc;
	HRESULT hr = pReflector->GetDesc(&pDesc);
	if(hr != S_OK){ return; }

	if(pDesc.ConstantBuffers > bufferNum)
	{
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
					auto spawnFunc = FindCBHardVariable(name);
					if(spawnFunc)
					{
						std::shared_ptr<CBVariables> newCBVariable = spawnFunc(this->cbufferData, varDesc.StartOffset);
						this->variables.push_back(newCBVariable);
					}
					else // we didn't find it, so it must be a weak variable
					{
						std::shared_ptr<CBVariables> newCBVariable
							= CBWeakVariables::Spawn(this->cbufferData, varDesc.StartOffset, varDesc.Size, varDesc.Name);
						this->variables.push_back(newCBVariable);
					}
				}
			}
		}
	}
}
void CBSetup::Run(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	for(auto variableIter = this->variables.begin();
		variableIter != this->variables.end();
		++variableIter)
	{
		(*variableIter)->Update(camera, object);
	}
}
const std::vector<char>& CBSetup::GetCBData()
{
	return this->cbufferData;
}
unsigned int CBSetup::GetCBSize()
{
	return this->cbufferData.size();
}
std::shared_ptr<CBSetup> CBSetup::Spawn(const std::vector<char>& compiledGeometryShader, unsigned int bufferNum)
{
	std::shared_ptr<CBSetup> newObject(new CBSetup());

	newObject->Init(compiledGeometryShader, bufferNum);

	return newObject;
}