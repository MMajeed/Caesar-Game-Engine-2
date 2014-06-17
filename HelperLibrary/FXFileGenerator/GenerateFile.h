#ifndef __GenerateFile__
#define __GenerateFile__

#include <vector>
#include <string>

namespace GenerateFile
{
	void GenerateSuccessFile(const std::string& directory,
							 const std::string& fileName,
							 const std::string& ext,
							 const std::vector<char>& bytes);
	void GenerateFailedFile(const std::string& directory,
							const std::string& fileName,
							const std::string& ext,
							const std::string& error);
}

#endif //__GenerateFile__

