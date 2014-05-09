#ifndef __Animation__
#define __Animation__

#include "Linker.h"
#include <Vector.h>
#include <string>
#include <hash_map>

namespace CHL
{
	class CaesarModelLibraryDLL_API Animation
	{
	public:
		struct Joint
		{
			struct Key
			{
				CML::Vec3 value;
				double time;
			};
			struct QuaKey
			{
				CML::Vec4 value;
				double time;
			};
			std::string name;
			std::vector<Key> Translation;
			std::vector<QuaKey> Rotation;
			std::vector<Key> Scale;
		};
		std::hash_map<std::string, Joint> vecJoints;
		double duration;
		std::string name;

		Animation();
	};
}

#endif //__Animation__