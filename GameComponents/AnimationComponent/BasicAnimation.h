#ifndef __BasicAnimation__
#define __BasicAnimation__

#include "Linker.h"

#include <memory>
#include <Animation.h>
#include <Node.h>
#include <unordered_map>

class AnimationComponentDLL_API BasicAnimation
{
protected:
	BasicAnimation();
public:
	static std::shared_ptr<BasicAnimation> Spawn(std::shared_ptr<CHL::Animation> animation);

	struct Joint
	{
		struct Key
		{
			CML::Vec3 Value;
			double Time;
		};
		struct QuaKey
		{
			CML::Vec4 Value;
			double Time;
		};
		std::vector<Joint::Key> Translation;
		std::vector<Joint::QuaKey> Rotation;
		std::vector<Joint::Key> Scale;

		std::string Name;
	};
	double Duration;
	std::unordered_map<std::string, BasicAnimation::Joint> AllNodes;
};


#endif //__BasicAnimation__