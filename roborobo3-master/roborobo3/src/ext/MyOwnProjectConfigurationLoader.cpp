#if defined PRJ_MYOWNPROJECT || !defined MODULAR

#include "Config/MyOwnProjectConfigurationLoader.h"
#include "MyOwnProject/include/MyOwnProjectWorldObserver.h"
#include "MyOwnProject/include/MyOwnProjectAgentObserver.h"
#include "MyOwnProject/include/MyOwnProjectController.h"
#include "WorldModels/RobotWorldModel.h"


MyOwnProjectConfigurationLoader::MyOwnProjectConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

MyOwnProjectConfigurationLoader::~MyOwnProjectConfigurationLoader()
{
	//nothing to do
}

WorldObserver* MyOwnProjectConfigurationLoader::make_WorldObserver(World* wm)
{
	return new MyOwnProjectWorldObserver(wm);
}

RobotWorldModel* MyOwnProjectConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* MyOwnProjectConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new MyOwnProjectAgentObserver(wm);
}

Controller* MyOwnProjectConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new MyOwnProjectController(wm);
}


#endif
