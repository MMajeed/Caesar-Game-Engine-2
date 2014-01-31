#include "BasicAnimation.h"
#include <Node.h>

BasicAnimation::BasicAnimation()
{
	this->Duration = 0.0;
}

std::shared_ptr<BasicAnimation> BasicAnimation::Spawn(std::shared_ptr<CHL::Animation> animation, std::shared_ptr<CHL::Node> rootNode)
{
	std::shared_ptr<BasicAnimation> newObject(new BasicAnimation());
	newObject->Duration = animation->duration;
	struct LoadNodesRecursive
	{
		static void Run(std::shared_ptr<BasicAnimation::Node>& BANodes,
					    const std::shared_ptr<CHL::Node>& CHLNode,
						const std::shared_ptr<CHL::Animation>& fullCHLAnimation)
		{
			BANodes->Name = CHLNode->Name;
			BANodes->Transformation = CHLNode->Transformation;
			
			auto findJoint = fullCHLAnimation->vecJoints.find(BANodes->Name);
			if(findJoint != fullCHLAnimation->vecJoints.end())
			{
				for(auto iter = findJoint->second.Translation.begin();
					iter != findJoint->second.Translation.end();
					++iter)
				{
					BasicAnimation::Node::Key newKey{{iter->value(0), iter->value(1), iter->value(2)}, iter->time};
					BANodes->Translation.push_back(newKey);
				}
				for(auto iter = findJoint->second.Rotation.begin();
					iter != findJoint->second.Rotation.end();
					++iter)
				{
					BasicAnimation::Node::QuaKey newKey{{iter->value(0), iter->value(1), iter->value(2), iter->value(3)}, iter->time};
					BANodes->Rotation.push_back(newKey);
				}
				for(auto iter = findJoint->second.Scale.begin();
					iter != findJoint->second.Scale.end();
					++iter)
				{
					BasicAnimation::Node::Key newKey{{iter->value(0), iter->value(1), iter->value(2)}, iter->time};
					BANodes->Scale.push_back(newKey);
				}
			}

			for(auto iter = CHLNode->Childern.begin();
				iter != CHLNode->Childern.end();
				++iter)
			{
				std::shared_ptr<BasicAnimation::Node> BAChildNode(new BasicAnimation::Node);
				BAChildNode->Parent = BANodes;
				LoadNodesRecursive::Run(BAChildNode, (*iter), fullCHLAnimation);
				BANodes->Childern.push_back(BAChildNode);
			}
		}
	};
	newObject->RootNode = std::shared_ptr<BasicAnimation::Node>(new BasicAnimation::Node);
	LoadNodesRecursive::Run(newObject->RootNode, rootNode, animation);
	return newObject;
}