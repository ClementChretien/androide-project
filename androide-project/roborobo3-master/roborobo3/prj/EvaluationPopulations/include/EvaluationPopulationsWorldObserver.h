/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef EVALUATIONPOPULATIONSWORLDOBSERVER_H
#define EVALUATIONPOPULATIONSWORLDOBSERVER_H

#include "Observers/WorldObserver.h"
#include "Observers/WorldObserver.h"
#include "MyOwnProject/include/Specie.h"
#include "MyOwnProject/include/Genome.h"

class World;

class EvaluationPopulationsWorldObserver : public WorldObserver
{
	protected:
		int pointCount;
		int nbAgent;
		int nbPop;
		int nbOfB;
		int nbOfH;
		int nbOfComplet;
		int depotMin;
		int depotMax;
		int rampeYMin;
		int rampeYMax;
		int nestYMin;
		int nestYMax;
    	std::string genomeHaut;
    	std::string genomeBas;
    	std::string genomeComplet;
	public:
		EvaluationPopulationsWorldObserver( World *__world );
		~EvaluationPopulationsWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
		void addPoint();
		void addPoint(int p);
		void removePoint(int p);
		int getPoint();
		void resetPoint();

		//Evaluation
		void evaluation();
        void evaluationNormale();
        void evaluationHaut();
        void evaluationBas();
		void initAgents(int nbAgent,Specie p);

        std::vector<Specie> selectionTournoi(std::vector<Specie> s,std::vector<Specie> newS, int nb);
        //std::vector<Specie> ajouterCroisement(std::vector<Specie> s,std::vector<Specie> newS,int iMin,int iMax);
        std::vector<Specie> remplirRandom(std::vector<Specie> newS,int iMin);
		std::vector<Specie> mutation(std::vector<Specie> newS, int nbToMutate, float pourcent);
    	void initObjects();

		void writeFile(std::vector<int> s);
		void readGenomeFile(std::string f,int iAgent);
		
};

#endif

