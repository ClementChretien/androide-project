/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#include <vector>
#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"
#include "MyOwnProject/include/Genome.h"

class Specie
{
	
    //

    private: 
        int nbAgent;
        int genSize;
        int isPosMin;
        int isPosMax;
        int fitness;
        std::vector<Genome> pop;
	
    public : 
        Specie(int nbAgent, int genSize,int isPosMin,int isPosMax);
        void initPop();
        void initAgent(int ag);
        void setAgent(std::vector<float> g,int iAgent);
        std::vector<float> getAgent(int iAgent);
        void setNucleotideAgent(int iAgent, int iNucleo, float value);
        void setNbAgent(int nb);
        int getNbAgent();
        void setGenSize(int size);
        int getGenSize();
        void setPosMin(int p);
        int getPosMin();
        void setPosMax(int p);
        int getPosMax();
        void setFitness(int v);
        int getFitness();
};