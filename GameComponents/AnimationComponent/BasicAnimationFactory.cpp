#include "BasicAnimationFactory.h"
#include <GenerateGUID.h>
#include <Components.h>
#include "Resource.h"

std::string BasicAnimationFactory::Create(std::shared_ptr<CHL::Animation> animation)
{
	std::shared_ptr<CHL::Animation> cloneAnimation(new CHL::Animation(*animation));
	std::string ID = CHL::GenerateGUID();

	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());
		std::shared_ptr<BasicAnimation> newBasicAnimation = BasicAnimation::Spawn(cloneAnimation);
		Resource::AnimationsList[ID] = newBasicAnimation;

		return Message::Status::Complete;
	});

	return ID;
}

void BasicAnimationFactory::Release(std::string ID)
{
	Components::Animation->SubmitMessage([=]()
	{
		std::lock_guard<std::mutex> lock(Components::Animation->Mutex());

		Resource::AnimationsList.erase(ID);

		return Message::Status::Complete;
	});
}