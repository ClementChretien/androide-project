#include <string>
#include <vector>
#include "MyOwnProject/include/Genome.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
Genome::Genome(int genSize,int isPosMin,int isPosMax)
{
    this->genSize = genSize;
    std::vector<float> gen(genSize);
    this->gene = gen;
    this->setPosMin(isPosMin);
    this->setPosMax(isPosMax);
    this->initGenome();
}
void Genome::initGenome(){
    for (int i = 0 ; i < this->getGenSize() ; i ++){
        if(i == 0){
            this->setNucleo(i,1);
        }
        else if(i == 1){
            this->setNucleo(i,0);
        }
        else if(i > this->getPosMin() && i <= this->getPosMax()){
            this->setNucleo(i,random01()*900+50);
            //this->setNucleo(i,0);
        }else{
            this->setNucleo(i,random01()*2-1);
        }
    }
}
std::vector<float> Genome::getGenome(){
    return this->gene;
}
void Genome::setNucleo(int i,float value){
    if(i < this->gene.size()){
        this->gene[i] = value;
    }    
}
void Genome::setGenome(std::vector<float> g){
    for (int i = 0 ; i < std::min(g.size(),this->gene.size()) ; i++){
        this->gene[i]=g[i];
    }
}
void Genome::setGenSize(int size){
    this->genSize = size;
}
int Genome::getGenSize(){
    return this->genSize;
}
void Genome::setPosMin(int p){
    this->isPosMin = p;
}
int Genome::getPosMin(){
    return this->isPosMin;
}
void Genome::setPosMax(int p){
    this->isPosMax = p;
}
int Genome::getPosMax(){
    return this->isPosMax;
}