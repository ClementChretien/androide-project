#if defined PRJ_RANDOMSHAPLEYVALUE || !defined MODULAR

#include "Config/RandomShapleyValueConfigurationLoader.h"
#include "RandomShapleyValue/include/RandomShapleyValueWorldObserver.h"
#include "RandomShapleyValue/include/RandomShapleyValueAgentObserver.h"
#include "RandomShapleyValue/include/RandomShapleyValueController.h"
#include "WorldModels/RobotWorldModel.h"


RandomShapleyValueConfigurationLoader::RandomShapleyValueConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

RandomShapleyValueConfigurationLoader::~RandomShapleyValueConfigurationLoader()
{
	//nothing to do
}

WorldObserver* RandomShapleyValueConfigurationLoader::make_WorldObserver(World* wm)
{
	return new RandomShapleyValueWorldObserver(wm);
}

RobotWorldModel* RandomShapleyValueConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* RandomShapleyValueConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new RandomShapleyValueAgentObserver(wm);
}

Controller* RandomShapleyValueConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new RandomShapleyValueController(wm);
}


#endif
