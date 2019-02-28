#include "MyOwnProject/include/MyOwnProjectController.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
#include "MyOwnProject/include/Specie.h"
// Load readable sensor names
#define NB_SENSORS 12 // assume 12 sensors
#include "Utilities/Sensorbelt.h"


Specie::Specie(int nbAgent,int genSize,int isPosMin,int isPosMax)
{
    this->name = "Non init";
    this->setNbAgent( nbAgent );
    this->setGenSize(genSize);
    this->setPosMin(isPosMin);
    this->setPosMax(isPosMax);
    this->setFitness(0);
    //Genome g = new Genome(genSize,isPosMin,isPosMax);
    std::vector<Genome> pop(nbAgent, Genome(genSize,isPosMin,isPosMax));
    this->pop = pop;
    this->initPop(name);


}

void Specie::initPop(std::string name){
    this->setName(name);
    for(int i = 0 ; i < this->getNbAgent() ; i++){
        this->pop[i].initGenome();
    }
}
void Specie::setNucleotideAgent(int iAgent, int iNucleo, float value){

    /*std::cout << "1Bla "<< sizeOf(pop)  <<" \n";
    pop[iAgent][iNucleo] = value;
    std::cout << "2Bla "<< iAgent <<" : " << value <<" \n";*/
}
void Specie::setAgent(std::vector<float> g,int iAgent){
    if(iAgent < this->getNbAgent()){
        this->pop[iAgent].setGenome(g);
    }
}
std::vector<float> Specie::getAgent(int iAgent){
    if(iAgent < this->getNbAgent()){
        return this->pop[iAgent].getGenome();
    }
    return std::vector<float>(24,0);
}
void Specie::setNbAgent(int nb){
    this->nbAgent = nb;
}
int Specie::getNbAgent(){
    return this->nbAgent;
}
void Specie::setGenSize(int size){
    this->genSize = size;
}
int Specie::getGenSize(){
    return this->genSize;
}
void Specie::setPosMin(int p){
    this->isPosMin = p;
}
int Specie::getPosMin(){
    return this->isPosMin;
}
void Specie::setPosMax(int p){
    this->isPosMax = p;
}
int Specie::getPosMax(){
    return this->isPosMax;
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