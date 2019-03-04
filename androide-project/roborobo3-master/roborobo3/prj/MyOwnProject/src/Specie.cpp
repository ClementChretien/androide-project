#include "MyOwnProject/include/MyOwnProjectController.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
#include "MyOwnProject/include/Specie.h"
// Load readable sensor names
#define NB_SENSORS 12 // assume 12 sensors
#include "Utilities/Sensorbelt.h"
#include <vector>
using namespace std; 


Specie::Specie(int genSize):pop(Genome(genSize))
{
    /*Genome* g = new Genome(genSize);
    this->pop = *g;*/
    this->name = "Non init";
    this->setGenSize(genSize);
    this->setFitness(0);
    //Genome g = new Genome(genSize,isPosMin,isPosMax);
    //Genome pop = Genome(genSize);
    this->initPop(name);
    
}

void Specie::initPop(std::string name){
    this->setName(name);
    this->pop.initGenome();
}
void Specie::setNucleo(int iNucleo, float value){
    this->pop.setNucleo(iNucleo,value);
}
void Specie::setGenome(std::vector<float> g){
    this->pop.setGenome(g);
}
std::vector<float> Specie::getAgent(){
    return this->pop.getGenome();
}
void Specie::setGenSize(int size){
    this->genSize = size;
}
int Specie::getGenSize(){
    return this->genSize;
}

void Specie::setFitness(int v){
    this->fitness = v;
}
int Specie::getFitness(){
    return this->fitness;
}
void Specie::setName(std::string v){
    this->name = v;
}
std::string Specie::getName(){
    return this->name;
}