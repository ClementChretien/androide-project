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
	public:
		MyOwnProjectWorldObserver( World *__world );
		~MyOwnProjectWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
		void addPoint();
		void addPoint(int p);
		int getPoint();
		void resetPoint();

		void initAgents(int nbAgent,Specie p);

        void selectionTournoi(std::vector<Specie> s,int nbAgent,std::vector<Specie> newS);
        void ajouterCroisement(std::vector<Specie> s,std::vector<Specie> newS,int iMin,int iMax);
        void remplirRandom(std::vector<Specie> newS,int iMin);
    	void initObjects();
		void analyseSpecie(int specie);
		
};

#endif

