#ifndef __FXCompiler__
#define __FXCompiler__

#include <vector>
#include <string>

namespace FXCompiler
{
	bool CompileShaderFromFile(const std::string& szFileName,
							   const std::string& szEntryPoint,
							   const std::string& szShaderModel,
							   std::vector<char>& bytes,
							   std::string& error);
}

#endif //__FXCompiler__