#include "FXCompiler.h"

#include <d3dcompiler.h>
#include <D3DX11async.h>

namespace FXCompiler
{
	bool CompileShaderFromFile(const std::string& szFileName,
							   const std::string& szEntryPoint,
							   const std::string& szShaderModel,
							   std::vector<char>& bytes,
							   std::string& error)
	{
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob;
		ID3DBlob* ppBlobOut;

		std::wstring wszFileName = std::wstring(szFileName.begin(), szFileName.end());

		HRESULT hr = D3DX11CompileFromFile(wszFileName.c_str(), NULL, NULL, szEntryPoint.c_str(), szShaderModel.c_str(),
								   dwShaderFlags, 0, NULL, &ppBlobOut, &pErrorBlob, NULL);
		if(FAILED(hr))
		{
			if(pErrorBlob != 0)
			{
				error = (char*)pErrorBlob->GetBufferPointer();
				return false;
			}
			else
			{
				error = "Failed to find file " + szFileName;
				return false;
			}
		}


		bytes.resize(ppBlobOut->GetBufferSize());
		memcpy(bytes.data(), ppBlobOut->GetBufferPointer(), ppBlobOut->GetBufferSize());

		return true;
	}
}
