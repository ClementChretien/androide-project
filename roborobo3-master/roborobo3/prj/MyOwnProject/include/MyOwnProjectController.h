/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef MYOWNPROJECTCONTROLLER_H
#define MYOWNPROJECTCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class MyOwnProjectController : public Controller
{
	public:
		MyOwnProjectController( RobotWorldModel *__wm );
		~MyOwnProjectController();
    
        std::vector<double> _params;
		
		void reset();
		void step();
    
        void monitorSensoryInformation();
    
        std::string inspect( std::string prefix = "" );
};


#endif

