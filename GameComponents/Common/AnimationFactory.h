#ifndef __AnimationFactory__
#define __AnimationFactory__

#include "Linker.h"

#include "Interface.h"
#include "iAnimationControllerFactory.h"
#include "iBasicAnimationFactory.h"
#include <memory>
#include <string>

class CommonDLL_API AnimationFactory
{
public:
	struct AnimationItem
	{
		std::shared_ptr<Interface> _AnimationInterface;
		std::shared_ptr<iAnimationControllerFactory> _AnimationControllerFactory;
		std::shared_ptr<iBasicAnimationFactory> _BasicAnimationFactory;
	};

	AnimationFactory(const AnimationFactory::AnimationItem& input);

	virtual bool Verify();

	virtual void SubmitMessage(std::shared_ptr<Message> msg);
	virtual void SubmitMessage(std::function<Message::Status()> func);
	virtual std::shared_ptr<Interface> GetComponent();

	virtual std::mutex& Mutex();

	virtual std::shared_ptr<iAnimationControllerFactory> AnimationControllerFactory();
	virtual std::shared_ptr<iBasicAnimationFactory> BasicAnimationFactory();
protected:
	AnimationItem _ClassItems;
};

#endif //__AnimationFactory__