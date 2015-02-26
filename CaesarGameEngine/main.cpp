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

	int state = 0;

	if(state == 0)
	{
		StraightForwardWorker worker;
		worker.AddComponent(Components::Script->GetComponent(), 0);
		worker.AddComponent(Components::Animation->GetComponent(), 1);
		worker.AddComponent(Components::Physics->GetComponent(), 2);
		worker.AddComponent(Components::Graphic->GetComponent(), 3);
		worker.Run();
	}
	else if(state == 1)
	{
		ParallelWorker worker;
		worker.AddComponent(Components::Graphic->GetComponent(), 12000);
		worker.AddComponent(Components::Physics->GetComponent(), 12000);
		worker.AddComponent(Components::Animation->GetComponent(), 12000);
		worker.AddComponent(Components::Script->GetComponent(), 12000);
		worker.Run();
	}
	else if(state == 2)
	{
		HalfAndHalfWorker worker;
		worker.AddFirstComponent(Components::Graphic->GetComponent(), 0);
		worker.AddParallelComponent(Components::Physics->GetComponent());
		worker.AddParallelComponent(Components::Animation->GetComponent());
		worker.AddLastComponent(Components::Script->GetComponent(), 0);
		worker.Run();
	}

	return 1;
}