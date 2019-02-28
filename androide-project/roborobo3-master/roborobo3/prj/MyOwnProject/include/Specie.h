/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#include <list>
using namespace std; 
#include <vector>
#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"
#include "MyOwnProject/include/Genome.h"

class Specie
{
    private: 
        int genSize;
        int fitness;
        Genome pop;
        std::string name;
	
    public : 
        Specie(int genSize);
        void initPop(std::string name);
        void initAgent(int ag);
        void setGenome(std::vector<float> g);
        std::vector<float> getAgent();
        void setNucleo(int iNucleo, float value);
        void setGenSize(int size);
        int getGenSize();
        void setFitness(int v);
        int getFitness();
        void setName(std::string name);
        std::string getName();
};