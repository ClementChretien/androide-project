/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef MYOWNPROJECTAGENTOBSERVER_H
#define MYOWNPROJECTAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class MyOwnProjectAgentObserver : public AgentObserver
{
	public:
		MyOwnProjectAgentObserver( );
		MyOwnProjectAgentObserver( RobotWorldModel *__wm );
		~MyOwnProjectAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

