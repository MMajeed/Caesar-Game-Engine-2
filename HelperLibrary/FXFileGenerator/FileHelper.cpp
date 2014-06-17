#include "FileHelper.h"

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

namespace fs = ::boost::filesystem;

namespace FileHelper
{
	std::vector<std::string> GetAll(const std::string& root, const std::string& ext)
	{
		std::vector<std::string> returnValue;

		if(!fs::exists(root)) return returnValue;


		if(fs::is_directory(root))
		{
			fs::recursive_directory_iterator it(root);
			fs::recursive_directory_iterator endit;
			while(it != endit)
			{
				if(fs::is_regular_file(*it) && it->path().extension() == ext)
				{
					std::string fileName = it->path().string();
					returnValue.push_back(fileName);
				}
				++it;
			}
		} 
		
		return returnValue;
	}

	std::string WorkingDirectory()
	{
		return fs::current_path().string();
	}

	std::string GetFileNameWithoutPath(const std::string& path)
	{
		fs::path boostPath(path);
		return boostPath.filename().string();
	}

	std::string RemoveFileExt(const std::string& path)
	{
		int lastindex = path.find_last_of(".");
		std::string rawname = path.substr(0, lastindex);
		return rawname;
	}
}