/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef EVALUATIONPOPULATIONSCONTROLLER_H
#define EVALUATIONPOPULATIONSCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"
#include <vector>
using namespace std; 
#include "MyOwnProject/include/Genome.h"

class RobotWorldModel;

class EvaluationPopulationsController : public Controller
{	//[24]={-1,-1,-1,-1,-1,-1,-1,0.01,1,1,1,1,1,1,1,0.5,0,1,1,1,400,700,950,1000};
	private:
		bool objCollected;//Est ce que le robot a récupéré un objet
		bool canCollect;//Est ce que le robot peux recuperer un objet
		bool canDropSlope;//Est ce que le robot peux deposer un objet dans la zone de pente
		bool canDropNest;//Est ce que le robot peux deposer un objet dans la zone de depot final
		bool instantDrop;//Pour l'activation du dépot automatique
		bool objObserved;//Pour l'activation du dépot automatique
		std::vector<float> genome;
    	std::vector<int> layers;
	
	public:
		EvaluationPopulationsController( RobotWorldModel *__wm );
		~EvaluationPopulationsController();
    
        std::vector<double> _params;
		void reset();
		void step();
		void init();
		bool getCanCollect();
		bool getCanDropSlope();
		bool getCanDropNest();
		bool getCanInstantDrop();
		bool getObjCollected();
		bool getIsObserved();
		std::vector<int> getLayers();
		void setCanCollect(bool c);
		void setCanDropSlope(bool c);
		void setCanDropNest(bool c);
		void setCanInstantDrop(bool c);
		void setObjCollected(bool c);
		void setIsObserved(bool c);
		void setLayers(std::vector<int> l);
        void monitorSensoryInformation();

		//AG
		vector<float> definirEntree();
		vector<float> calculateSortie(vector<float>);
		std::vector<float> getGenome();
		void setGenome(std::vector<float> g);
		double calculateRotation();
		double calculateTranslation();
		double calculateDrop();
    
        std::string inspect( std::string prefix = "" );
};


#endif

