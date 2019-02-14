/*
 * MyOwnProjectConfigurationLoader.h
 */

#ifndef MYOWNPROJECTCONFIGURATIONLOADER_H
#define	MYOWNPROJECTCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class MyOwnProjectConfigurationLoader : public ConfigurationLoader
{
	public:
		MyOwnProjectConfigurationLoader();
		~MyOwnProjectConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
