#ifndef __BasicAnimation__
#define __BasicAnimation__

#include "Linker.h"

#include <memory>
#include <Animation.h>
#include <Node.h>

class BasicAnimation
{
public:
	BasicAnimation();

	static std::shared_ptr<BasicAnimation> Spawn(std::shared_ptr<CHL::Animation> animation, std::shared_ptr<CHL::Node> rootNode);

	struct Node
	{
		CML::Matrix4x4 Transformation;
		std::shared_ptr<BasicAnimation::Node> Parent;
		std::vector<std::shared_ptr<BasicAnimation::Node>> Childern;

		struct Key
		{
			CML::Vec3 Value;
			double Time;
		};
		std::vector<Node::Key> Translation;
		std::vector<Node::Key> Rotation;
		std::vector<Node::Key> Scale;

		std::string Name;
	};
	double Duration;
	std::shared_ptr<BasicAnimation::Node> RootNode;
};


#endif //__BasicAnimation__