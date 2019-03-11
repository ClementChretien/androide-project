#if defined PRJ_EVALUATIONPOPULATIONS || !defined MODULAR

#include "Config/EvaluationPopulationsConfigurationLoader.h"
#include "EvaluationPopulations/include/EvaluationPopulationsWorldObserver.h"
#include "EvaluationPopulations/include/EvaluationPopulationsAgentObserver.h"
#include "EvaluationPopulations/include/EvaluationPopulationsController.h"
#include "WorldModels/RobotWorldModel.h"


EvaluationPopulationsConfigurationLoader::EvaluationPopulationsConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

EvaluationPopulationsConfigurationLoader::~EvaluationPopulationsConfigurationLoader()
{
	//nothing to do
}

WorldObserver* EvaluationPopulationsConfigurationLoader::make_WorldObserver(World* wm)
{
	return new EvaluationPopulationsWorldObserver(wm);
}

RobotWorldModel* EvaluationPopulationsConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* EvaluationPopulationsConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new EvaluationPopulationsAgentObserver(wm);
}

Controller* EvaluationPopulationsConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new EvaluationPopulationsController(wm);
}


#endif
