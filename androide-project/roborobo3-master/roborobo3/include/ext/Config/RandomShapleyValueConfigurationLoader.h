/*
 * RandomShapleyValueConfigurationLoader.h
 */

#ifndef RANDOMSHAPLEYVALUECONFIGURATIONLOADER_H
#define	RANDOMSHAPLEYVALUECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class RandomShapleyValueConfigurationLoader : public ConfigurationLoader
{
	public:
		RandomShapleyValueConfigurationLoader();
		~RandomShapleyValueConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
