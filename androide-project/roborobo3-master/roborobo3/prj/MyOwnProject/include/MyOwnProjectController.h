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
	private:
		bool objCollected;
		bool canCollect;
		bool canDropSlope;
		bool canDropNest;

	public:
		MyOwnProjectController( RobotWorldModel *__wm );
		~MyOwnProjectController();
    
        std::vector<double> _params;
		void reset();
		void step();
		bool getCanCollect();
		bool getCanDropSlope();
		bool getCanDropNest();
		bool getObjCollected();
		void setCanCollect(bool c);
		void setCanDropSlope(bool c);
		void setCanDropNest(bool c);
		void setObjCollected(bool c);
        void monitorSensoryInformation();
    
        std::string inspect( std::string prefix = "" );
};


#endif

