#include "BasicAnimation.h"
#include <Node.h>

BasicAnimation::BasicAnimation()
{
	this->Duration = 0.0;
}

std::shared_ptr<BasicAnimation> BasicAnimation::Spawn(std::shared_ptr<CHL::Animation> animation)
{
	std::shared_ptr<BasicAnimation> newObject(new BasicAnimation());
	newObject->Duration = animation->duration;

	for(auto jointIter = animation->vecJoints.begin();
		jointIter != animation->vecJoints.end();
		++jointIter)
	{
		BasicAnimation::Joint newJoint;

		newJoint.Name = jointIter->second.name;

		for(auto jointTranslationIter = jointIter->second.Translation.begin();
			jointTranslationIter != jointIter->second.Translation.end();
			++jointTranslationIter)
		{
			newJoint.Translation.push_back({jointTranslationIter->value, jointTranslationIter->time});
		}

		for(auto jointRotationIter = jointIter->second.Rotation.begin();
			jointRotationIter != jointIter->second.Rotation.end();
			++jointRotationIter)
		{
			newJoint.Rotation.push_back({jointRotationIter->value, jointRotationIter->time});
		}

		for(auto jointScaleIter = jointIter->second.Scale.begin();
			jointScaleIter != jointIter->second.Scale.end();
			++jointScaleIter)
		{
			newJoint.Scale.push_back({jointScaleIter->value, jointScaleIter->time});
		}

		newObject->AllNodes[newJoint.Name] = newJoint;
	}

	return newObject;
}