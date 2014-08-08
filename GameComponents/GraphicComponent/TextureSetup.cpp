#include "TextureSetup.h"

#include <D3DCompiler.h>

TextureSetup::TextureSetup(){}
void TextureSetup::Init(const std::vector<char>& compiledShader)
{
	ID3D11ShaderReflection* pReflector = nullptr;
	D3DReflect(compiledShader.data(), compiledShader.size(),
			  IID_ID3D11ShaderReflection, (void**)&pReflector);

	if(pReflector == nullptr){ return; }

	D3D11_SHADER_DESC desc;
	HRESULT hr = pReflector->GetDesc(&desc);
	if(hr != S_OK){ return; }

	for(unsigned int i = 0; i < desc.BoundResources; ++i)
	{
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc;
		pReflector->GetResourceBindingDesc(i, &resourceDesc);

		if(resourceDesc.Type == D3D_SIT_TEXTURE)
		{
			shaderTextures.push_back({resourceDesc.Name, resourceDesc.BindPoint});
		}
	}
	
}
std::vector<TextureInfo> TextureSetup::Setup(const GraphicCameraEntity& camera, const GraphicObjectEntity& object)
{
	std::vector<TextureInfo> returnValue;

	for(const TextureSetup::Textures& ti : this->shaderTextures)
	{
		if(std::shared_ptr<BasicTexture> tx = object.FindTexture(ti.Name))
		{
			returnValue.push_back({tx, ti.Slot});
		}
		else
		{
			returnValue.push_back({nullptr, ti.Slot});
		}
	}

	return returnValue;
}

std::shared_ptr<TextureSetup> TextureSetup::Spawn(const std::vector<char>& compiledShader)
{
	std::shared_ptr<TextureSetup> newObject(new TextureSetup());
	newObject->Init(compiledShader);
	return newObject;
}