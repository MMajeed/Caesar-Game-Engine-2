#include <string>
#include <iostream>

#include "FileHelper.h"
#include "FXCompiler.h"
#include "GenerateFile.h"
#include <vector>
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while(std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
std::vector<std::string> split(const std::string &s, char delim) 
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

int main(int argc, char **argv)
{
	//Cheak to see if the user entered atleast one paremtor but no more then two
	if(argc < 4 )
	{
		std::cout << "Error: Incorrect Number of Parameters \n"
			"Usage: FXFileGenerator [File] [OutputDirectory] [EntryPoint/ShaderModel](0..Infinity)" << std::endl;
		return -1;
	}

	std::string fxFile = argv[1];
	std::string directory = argv[2];
	std::cout << fxFile;
	
	struct ShaderInfo{ std::string entryPoint; std::string shaderModel; };
	std::vector<ShaderInfo> TypeOfShaders;
	for(unsigned int i = 3; i < argc; ++i)
	{
		std::string info = argv[i];
		std::vector<std::string> infoSplit = split(info, '/');
		if(infoSplit.size() == 2)
		{
			TypeOfShaders.push_back({infoSplit[0], infoSplit[1]});
		}
	}

	std::cout << "\n\tStart: Working on file " << fxFile << "\n";
	for(auto& type : TypeOfShaders)
	{
		std::cout << "\t\tStart: Generating " << type.entryPoint << " file for " << fxFile << "\n";

		std::string fileName = FileHelper::GetFileNameWithoutPath(fxFile);
		std::string fileNameWithoutExt = FileHelper::RemoveFileExt(fileName);
			
		std::string GeneratedFileName = fileNameWithoutExt + type.entryPoint;


		std::vector<char> fxVSBytes;
		std::string errorMessage;
		bool result = FXCompiler::CompileShaderFromFile(fxFile, type.entryPoint, type.shaderModel, fxVSBytes, errorMessage);

		if(result == true)
		{
			GenerateFile::GenerateSuccessFile(directory, GeneratedFileName, ".h", fxVSBytes);
		}
		else
		{
			GenerateFile::GenerateFailedFile(directory, GeneratedFileName, ".h", errorMessage);
		}

		std::cout << "\t\tEnd: Generating " << type.entryPoint << " file for " << fxFile << "\n";
	}

	std::cout << "\tEnd: Working on file " << fxFile << "\n";
}

