#include <string>
#include <vector>
#include "MyOwnProject/include/Genome.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"

Genome::Genome(int genSize)
{
    this->genSize = genSize;
    std::vector<float> gen(genSize);
    this->gene = gen;
    this->initGenome();
}
void Genome::initGenome(){
    for (int i = 0 ; i < this->getGenSize() ; i ++){
        this->setNucleo(i,random01()*2-1);
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