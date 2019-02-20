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
		bool canDrop;

	public:
		MyOwnProjectController( RobotWorldModel *__wm );
		~MyOwnProjectController();
    
        std::vector<double> _params;
		void reset();
		void step();
		bool getCanCollect();
		bool getCanDrop();
		bool getObjCollected();
		void setCanCollect(bool c);
		void setCanDrop(bool c);
		void setObjCollected(bool c);
        void monitorSensoryInformation();
    
        std::string inspect( std::string prefix = "" );
};


#endif

