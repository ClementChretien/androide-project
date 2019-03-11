/*
 * EvaluationPopulationsConfigurationLoader.h
 */

#ifndef EVALUATIONPOPULATIONSCONFIGURATIONLOADER_H
#define	EVALUATIONPOPULATIONSCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class EvaluationPopulationsConfigurationLoader : public ConfigurationLoader
{
	public:
		EvaluationPopulationsConfigurationLoader();
		~EvaluationPopulationsConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
