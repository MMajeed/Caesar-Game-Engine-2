#ifndef __FileHelper__
#define __FileHelper__

#include <vector>
#include <string>

namespace FileHelper
{
	std::vector<std::string> GetAll(const std::string& root, const std::string& ext);
	std::string WorkingDirectory();
	std::string GetFileNameWithoutPath(const std::string& path);
	std::string RemoveFileExt(const std::string& path);
}

#endif //__FileHelper__