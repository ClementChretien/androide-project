/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef RandomShapleyValueAGENTOBSERVER_H
#define RandomShapleyValueAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class RandomShapleyValueAgentObserver : public AgentObserver
{
	public:
		RandomShapleyValueAgentObserver( );
		RandomShapleyValueAgentObserver( RobotWorldModel *__wm );
		~RandomShapleyValueAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

