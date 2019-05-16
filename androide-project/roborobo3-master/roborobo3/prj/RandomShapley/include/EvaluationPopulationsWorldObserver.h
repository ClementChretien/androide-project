/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef EVALUATIONPOPULATIONSWORLDOBSERVER_H
#define EVALUATIONPOPULATIONSWORLDOBSERVER_H

#include "Observers/WorldObserver.h"
#include "Observers/WorldObserver.h"
#include "MyOwnProject/include/Specie.h"
#include "MyOwnProject/include/Genome.h"
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 
using namespace std;
class World;

class EvaluationPopulationsWorldObserver : public WorldObserver
{	
	protected:

    	std::vector<int> combinaison;
		int pointCount;
		int nbAgent;
		int nbOfB;
		int nbOfH;
		int nbOfComplet;
		int nbOfRandom;
		int depotMin;
		int depotMax;
		int rampeYMin;
		int rampeYMax;
		int nestYMin;
		int nestYMax;
		int it;
        int itPop;
		int nbOfEtuPerComb;
    	string genomeHaut;
    	string genomeBas;
    	string genomeComplet;
    	string genomeRandom;
		bool set;

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


    	void initObjects();

		void writeFile(std::vector<int> s);
		void readGenomeFile(std::string f,int iAgent);
		void addResultFile(std::string f, std::string r);
		
};

#endif

