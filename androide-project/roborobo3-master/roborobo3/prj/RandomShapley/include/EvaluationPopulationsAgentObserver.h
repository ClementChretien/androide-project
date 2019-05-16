/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef EVALUATIONPOPULATIONSAGENTOBSERVER_H
#define EVALUATIONPOPULATIONSAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class EvaluationPopulationsAgentObserver : public AgentObserver
{
	public:
		EvaluationPopulationsAgentObserver( );
		EvaluationPopulationsAgentObserver( RobotWorldModel *__wm );
		~EvaluationPopulationsAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

