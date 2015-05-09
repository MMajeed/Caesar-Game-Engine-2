#include <exception>
#include <iostream>
#include <sstream>
#include <Converter.h>
#include <Logger.h>

#include <GraphicComponent\GraphicFactorySetup.h>
#include <ScriptComponent\ScriptFactorySetup.h>
#include <AnimationComponent\AnimationFactorySetup.h>
#include <PhysicsComponent\PhysicsFactorySetup.h>

#include <ScriptAnimation\ScriptAnimation.h>
#include <ScriptEntity\ScriptEntity.h>
#include <ScriptGraphic\ScriptGraphic.h>
#include <ScriptInput\ScriptInput.h>
#include <ScriptPhysics\ScriptPhysics.h>

#include <Common\Components.h>
#include "StraightForwardWorker.h"
#include "ParallelWorker.h"
#include "HalfAndHalfWorker.h"

void Print(std::string s)
{
	std::cout << s << "\n";
}

bool running = true;

int main()
{
	Logger::AddInformationLogger(Print);
	Logger::AddErrorLogger(Print);

	Components::Animation = std::shared_ptr<AnimationFactory>(new AnimationFactory(AnimationFactorySetup::Load()));
	if(Components::Animation == nullptr){ Logger::LogError("Failed to correctly load Animation"); }
	Components::Graphic = std::shared_ptr<GraphicFactory>(new GraphicFactory(GraphicFactorySetup::Load()));
	if(Components::Graphic == nullptr){ Logger::LogError("Failed to correctly load Graphic"); }
	Components::Script = std::shared_ptr<ScriptFactory>(new ScriptFactory(ScriptFactorySetup::Load()));
	if(Components::Script == nullptr){ Logger::LogError("Failed to correctly load Script"); }
	Components::Physics = std::shared_ptr<PhysicsFactory>(new PhysicsFactory(PhysicsFactorySetup::Load()));
	if(Components::Physics == nullptr){ Logger::LogError("Failed to correctly load Physics"); }

	int state = 2;

	if(state == 0)
	{
		StraightForwardWorker worker(120);
		worker.AddComponent(Components::Script->GetComponent(), 0);
		worker.AddComponent(Components::Animation->GetComponent(), 1);
		worker.AddComponent(Components::Physics->GetComponent(), 2);
		worker.AddComponent(Components::Graphic->GetComponent(), 3);
		worker.Run();
	}
	else if(state == 1)
	{
		ParallelWorker worker(120);
		worker.AddComponent(Components::Graphic->GetComponent());
		worker.AddComponent(Components::Physics->GetComponent());
		worker.AddComponent(Components::Animation->GetComponent());
		worker.AddComponent(Components::Script->GetComponent());
		worker.Run();
	}
	else if(state == 2)
	{
		HalfAndHalfWorker worker(120);
		worker.AddComponent(Components::Script->GetComponent(), 0, HalfAndHalfWorker::ComponentParameter::First);
		worker.AddComponent(Components::Physics->GetComponent(), 0, HalfAndHalfWorker::ComponentParameter::Parallel);
		worker.AddComponent(Components::Animation->GetComponent(), 0, HalfAndHalfWorker::ComponentParameter::Parallel);
		worker.AddComponent(Components::Graphic->GetComponent(), 0, HalfAndHalfWorker::ComponentParameter::Last);
		worker.Run();
	}

	return 1;
}