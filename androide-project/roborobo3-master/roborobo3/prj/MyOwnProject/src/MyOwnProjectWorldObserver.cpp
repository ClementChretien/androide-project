/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
#define _USE_MATH_DEFINES
//Variables globales
//Zone de jeu
int rampeYMin=400;
int rampeYMax=700;
int nestYMin=950;
int nestYMax=1000;
#include <vector>
using namespace std; 
#include "MyOwnProject/include/MyOwnProjectWorldObserver.h"
#include "World/World.h"
#include "World/SquareObject.h"
#include "WorldModels/RobotWorldModel.h"
#include "Utilities/Misc.h"
#include "MyOwnProject/include/MyOwnProjectController.h"
#include "RoboroboMain/roborobo.h"
#include "MyOwnProject/include/MyEnergyItem.h"

#include <math.h>


MyOwnProjectWorldObserver::MyOwnProjectWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
    this->pointCount = 0;
    this->nbAgent = 5;
    this->nbPop = 10;
    this->popEtu = 0;
    this->genSize = 17*3;
    this->generation=0;
    this->cptName=0;
    std::vector<Specie> s(this->nbPop,Specie(this->genSize));
    this->s = s;
    for (int p = 0 ; p < this->nbPop ; p++){
        this->s[p].initPop("Pop"+std::to_string(p));
        this->cptName++;
    }
}

MyOwnProjectWorldObserver::~MyOwnProjectWorldObserver()
{
	// nothing to do.
}

void MyOwnProjectWorldObserver::initPre()
{
    int nbObjectsTotal = 50;
    for ( int i = 0 ; i < nbObjectsTotal ; i++ )
    {
        // * create a new (custom) object
        
        int id = PhysicalObjectFactory::getNextId();
        MyEnergyItem *object = new MyEnergyItem(id);
        gPhysicalObjects.push_back( object );
        object->setDisplayColor(64,192,255);
        object->setType(1);
        object->setRegion(0.0,0.3);
        object->relocate();
    }
}

void MyOwnProjectWorldObserver::initPost()
{
    
}

void MyOwnProjectWorldObserver::stepPre()
{
    //std::cout <<"New Turn \n";
    for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
    {
        //std::cout << "Drop analyse :" << i<<"\n";
        MyOwnProjectController *c = dynamic_cast<MyOwnProjectController*>(gWorld->getRobot(i)->getController());
        Point2d p =c->getPosition();
        //std::cout << "2 Drop analyse :" << i<<"\n";
        if(c->getCanInstantDrop()==true){
            c->setObjCollected(false);
            //std::cout << "Drop it";
            int id = PhysicalObjectFactory::getNextId();
            MyEnergyItem *object = new MyEnergyItem(id);
            gPhysicalObjects.push_back( object );
            object->setDisplayColor(64,192,255);
            object->setType(1);
            float ori = c->getOrientation();
            //std::cout << "One point ! #########################################################\n";
            this->addPoint();
             
            if(p.y>rampeYMin && p.y < rampeYMax){
                int ymin = 700;
                int ymax = 730;
                object->relocate(ymin,ymax,true);
            }else if(p.y>nestYMin && p.y < nestYMax)
            {                    
                //std::cout << "One point ! #########################################################\n";
                object->setRegion(0.0,0.3);    
                object->relocate();
            }else{                    
                double objX = p.x - cos(M_PI*ori)*50;
                double objY = p.y - sin(M_PI*ori)*50;
                object->relocate(objX,objY,false,0.0,0.3);
            }
        }
        
    }
    // The following code shows an example where every 100 iterations, robots are re-located to their initial positions, and parameters are randomly changed.
    //
    // REMOVE OR COMMENT THE FOLLOWING TO AVOID RESETTING POSITIONS EVERY 100 ITERATIONS
    //

    
    //Reset
    if ( gWorld->getIterations() % 2500 == 0 )
    {
        this->s[this->popEtu].setFitness(this->getPoint());
        this->resetPoint();
        this->popEtu = this->popEtu+1;
        if(this->popEtu == this->nbPop){
            this->generation = this->generation+1;
            std::cout << "Gen :" << this->generation<<"\n";
            for ( int i = 0 ; i < this->nbPop ; i ++){
                std::cout << "Fitness de : " << s[i].getName() << ":" << this->s[i].getFitness()<<"\n";
            }
            std::cout << "Evolution de populations";
            this->popEtu = 0;
            //Séléctions
            std::vector<Specie> newS(this->nbPop,Specie(this->genSize));
            newS = this->selectionTournoi(this->s,newS);
            newS = this->selectionTournoi(this->s,newS);
            //newS = this->ajouterCroisement(this->s,newS,this->nbPop*0.8,this->nbPop);
            //Mutation
            this->s=newS;
        }
        for ( int i = 0 ; i !=5 ; i++ )
        {
            Robot *robot = (gWorld->getRobot(i));
            
            (*robot).setCoordReal( random01()*800+100 , random01()*100+850  );
            
            MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
             
            std::vector<float> ga = this->s[i].getAgent();
            controller->setGenome(ga);
            controller->init();
            //std::cout << "Reset Robot Done\n";
        }
        this->initObjects();
        /*for (int i = 0 ; i != 5 ; i++){
            MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
            std::cout << controller->getCanInstantDrop() << ": Object Collected\n";
        }*/
        
    }
    
}
void MyOwnProjectWorldObserver::initObjects(){
    /*gPhysicalObjects.empty();
    for (int i = 0 ; i < gPhysicalObjects.size() ; i++){
        std::cout << i<<":"<<gPhysicalObjects.size() <<"\n";
        if(gPhysicalObjects[i]){
            std::cout << i<<":"<<gPhysicalObjects.size() <<"\n";
            gPhysicalObjects[i]->relocate();
        }
        
    }*//*
    for ( int i = 0 ; i < nbObjectsTotal ; i++ )
    {
        // * create a new (custom) object
        
        int id = PhysicalObjectFactory::getNextId();
        MyEnergyItem *object = new MyEnergyItem(id);
        gPhysicalObjects.push_back( object );
        object->setDisplayColor(64,192,255);
        object->setType(1);
        object->setRegion(OFFSET,RANGE);
        object->relocate();
    }*/
}
void MyOwnProjectWorldObserver::analyseSpecie(int iSpecie){

}

void MyOwnProjectWorldObserver::initAgents(int nbAgent,Specie p){
    for ( int i = 0 ; i !=nbAgent ; i++ )
    {
        MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
        
        controller->setGenome(p.getAgent());
    }
}


std::vector<Specie> MyOwnProjectWorldObserver::selectionTournoi(std::vector<Specie> s,std::vector<Specie> newS){
    //Prendre x pop et selectionner juste le meilleur
    int tailleRec=  s.size()/10+1;
    std::vector<int> toAdd;
    for( int i = 0 ; i < s.size() ; i++){
        toAdd.resize(0);
        while(toAdd.size()<tailleRec){
            toAdd.push_back(int(random01()*s.size()));
        }
        int iMin = -1;
        int vMin = -1;
        for (int j = 0 ; j < toAdd.size() ; j++){
            if(vMin == -1||s[j].getFitness()> vMin){
                iMin = j;
                vMin = s[j].getFitness();
            }
        }
        
        newS[i]=s[iMin];
    }
    return newS;
}
/*std::vector<Specie> MyOwnProjectWorldObserver::ajouterCroisement(std::vector<Specie> s,std::vector<Specie> newS,int iMin,int iMax){
    //Prendre x pop et selectionner juste 2
    for( int i = iMin ; i < iMax ; i++){
        std::cout << i<<"\n";
        int p1=1,p2=1;
        do{
            p1=int(random01()*s.size());
            p2=int(random01()*s.size());
        }while(p1==p2);
        for(int j = 0 ; j < s[p1].getNbAgent() ; j ++){
            if(j < j/2){
                newS[i].setAgent(s[p1].getAgent());
            }else{
                newS[i].setAgent(s[p2].getAgent());
            }
        }
        this->cptName++;
        newS[i].setName("PopC"+std::to_string(this->cptName));
    }
    return newS;
}*/
std::vector<Specie> MyOwnProjectWorldObserver::remplirRandom(std::vector<Specie> newS,int iMin){
    for(int i = iMin ; i < newS.size() ; i++){
        newS[i]=Specie(this->genSize);
        newS[i].setName("Pop"+std::to_string(i));
    }
    return newS;
}
std::vector<Specie> MyOwnProjectWorldObserver::mutation(std::vector<Specie> newS){
    for(int i = 0 ; i < newS.size() ; i++){
        for(int j = 0 ; j <3 ; j++){
            int r = newS[0].getGenSize()*random01();
            newS[i].setNucleo(r,random01()*2-1);
        }
    }
    return newS;
}
void MyOwnProjectWorldObserver::stepPost()
{
}



void MyOwnProjectWorldObserver::addPoint(){
    this->addPoint(1);
}
void MyOwnProjectWorldObserver::addPoint(int p){
    this->pointCount=this->pointCount +p;
}
void MyOwnProjectWorldObserver::resetPoint(){
    this->pointCount=0;
}
int MyOwnProjectWorldObserver::getPoint(){
    return this->pointCount;
}