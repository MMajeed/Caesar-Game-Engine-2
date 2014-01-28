#ifndef __Animation__
#define __Animation__

#include "Linker.h"
#include <Vector.h>
#include <string>
#include <hash_map>

namespace CHL
{
	class Animation
	{
	public:
		struct Joint
		{
			struct Key
			{
				CML::Vec3 value;
				double time;
			};
			std::string name;
			std::vector<Key> Translation;
			std::vector<Key> Rotation;
			std::vector<Key> Scale;
		};
		std::hash_map<std::string, Joint> vecJoints;
		double duration;
		std::string name;

		Animation();
	};
}

#endif //__Animation__