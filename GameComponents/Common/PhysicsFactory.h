#ifndef __PhysicsFactory__
#define __PhysicsFactory__

#include "Linker.h"

#include "Interface.h"
#include "iCollisionShapeFactory.h"
#include "iConstraintFactory.h"
#include "iRigidBodyFactory.h"
#include <memory>
#include <string>

class CommonDLL_API PhysicsFactory
{
public:
	struct PhysicsItem
	{
		std::shared_ptr<Interface> _PhysicsInterface;
		std::shared_ptr<iCollisionShapeFactory> _CollisionShapeFactory;
		std::shared_ptr<iConstraintFactory> _ConstraintFactory;
		std::shared_ptr<iRigidBodyFactory> _RigidBodyFactory;
	};

	PhysicsFactory(const PhysicsFactory::PhysicsItem& input);

	virtual bool Verify();

	virtual void SubmitMessage(std::shared_ptr<Message> msg);
	virtual void SubmitMessage(std::function<Message::Status()> func);
	virtual std::shared_ptr<Interface> GetComponent();

	virtual std::mutex& Mutex();

	virtual std::shared_ptr<iCollisionShapeFactory> CollisionShapeFactory();
	virtual std::shared_ptr<iConstraintFactory> ConstraintFactory();
	virtual std::shared_ptr<iRigidBodyFactory> RigidBodyFactory();
protected:
	PhysicsItem _ClassItems;
};

#endif //__PhysicsFactory__