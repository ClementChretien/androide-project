/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef MYOWNPROJECTWORLDOBSERVER_H
#define MYOWNPROJECTWORLDOBSERVER_H

#include "Observers/WorldObserver.h"
#include "MyOwnProject/include/Specie.h"

class World;

class MyOwnProjectWorldObserver : public WorldObserver
{
	protected:
		int pointCount;
		int nbAgent;
		int nbPop;
		int popEtu;
		int genSize;
		std::vector<Specie> s;
		std::vector<int> layers;
		int generation;
		int cptName;
    	int evalType;
    	int numberMaxOfGen;
	public:
		MyOwnProjectWorldObserver( World *__world );
		~MyOwnProjectWorldObserver();
				
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

		void writeFile();
};

#endif

