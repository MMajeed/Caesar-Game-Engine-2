#include "GenerateFile.h"

#include <fstream>
#include <map>

namespace GenerateFile
{
	void GenerateSuccessFile(const std::string& directory,
							 const std::string& fileName,
							 const std::string& ext,
							 const std::vector<char>& bytes)
	{
		std::ofstream myfile(directory + fileName + ext);
		myfile.clear();

		if(myfile.is_open())
		{
			myfile << "#ifndef __" << fileName << "_FX__" << "\n";
			myfile << "#define __" << fileName << "_FX__" << "\n";

			myfile << "#include <vector> \n";

			myfile << "static const std::vector<char> " << fileName << " = {";

			for(auto& byte : bytes)
			{
				myfile << (int)byte << ", ";
			}

			myfile << "};" << "\n";

			myfile << "#endif //__" << fileName << "_FX__" << "\n";
		}
	}
	void GenerateFailedFile(const std::string& directory,
							const std::string& fileName,
							const std::string& ext,
							const std::string& error)
	{
		std::ofstream myfile(directory + fileName + ext);
		if(myfile.is_open())
		{
			myfile << "#ifndef __" << fileName << "_FX__" << "\n";
			myfile << "#define __" << fileName << "_FX__" << "\n";

			myfile << "#error " << error << "\n";

			myfile << "#endif //__" << fileName << "_FX__" << "\n";
		}
	}
}