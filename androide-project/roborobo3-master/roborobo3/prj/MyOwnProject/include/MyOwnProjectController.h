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
		bool objCollected;//Est ce que le robot a récupéré un objet
		bool canCollect;//Est ce que le robot peux recuperer un objet
		bool canDropSlope;//Est ce que le robot peux deposer un objet dans la zone de pente
		bool canDropNest;//Est ce que le robot peux deposer un objet dans la zone de depot final
		bool instantDrop;//Pour l'activation du dépot automatique

	public:
		MyOwnProjectController( RobotWorldModel *__wm );
		~MyOwnProjectController();
    
        std::vector<double> _params;
		void reset();
		void step();
		bool getCanCollect();
		bool getCanDropSlope();
		bool getCanDropNest();
		bool getCanInstantDrop();
		bool getObjCollected();
		void setCanCollect(bool c);
		void setCanDropSlope(bool c);
		void setCanDropNest(bool c);
		void setCanInstantDrop(bool c);
		void setObjCollected(bool c);
        void monitorSensoryInformation();
    
        std::string inspect( std::string prefix = "" );
};


#endif

