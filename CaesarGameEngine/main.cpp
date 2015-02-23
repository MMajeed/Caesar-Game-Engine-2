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

#include <thread>
#include <map>
#include <iomanip>

#include <Common\Components.h>

void Print(std::string s)
{
	std::cout << s << "\n";
}

bool running = true;

int main()
{
	Logger::AddInformationLogger(Print);
	Logger::AddErrorLogger(Print);

	ScriptAnimation::GetInstance();
	ScriptEntity::GetInstance();
	ScriptGraphic::GetInstance();
	ScriptInput::GetInstance();
	ScriptPhysics::GetInstance();

	Components::Animation = std::shared_ptr<AnimationFactory>(new AnimationFactory(AnimationFactorySetup::Load()));
	if(Components::Animation == nullptr){ Logger::LogError("Failed to correctly load Animation"); }
	Components::Graphic = std::shared_ptr<GraphicFactory>(new GraphicFactory(GraphicFactorySetup::Load()));
	if(Components::Graphic == nullptr){ Logger::LogError("Failed to correctly load Graphic"); }
	Components::Script = std::shared_ptr<ScriptFactory>(new ScriptFactory(ScriptFactorySetup::Load()));
	if(Components::Script == nullptr){ Logger::LogError("Failed to correctly load Script"); }
	Components::Physics = std::shared_ptr<PhysicsFactory>(new PhysicsFactory(PhysicsFactorySetup::Load()));
	if(Components::Physics == nullptr){ Logger::LogError("Failed to correctly load Physics"); }


	std::map<std::string, std::shared_ptr<Interface>> vInterfaces;
	std::vector<std::shared_ptr<std::thread>> vThreads;

	vInterfaces["Animation"] = Components::Animation->GetComponent();
	vInterfaces["Graphic"] = Components::Graphic->GetComponent();
	vInterfaces["Script"] = Components::Script->GetComponent();
	vInterfaces["Physics"] = Components::Physics->GetComponent();
	
	std::shared_ptr<AnimationFactory> g = Components::Animation;

	for(auto iter = vInterfaces.begin();
		iter != vInterfaces.end();
		++iter)
	{
		std::shared_ptr<std::thread> thread
			= std::shared_ptr<std::thread>(new std::thread(std::bind(&Interface::Start, iter->second)));

		vThreads.push_back(thread);
	}

	while(running == true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(5000)));
	}

	return 1;
}