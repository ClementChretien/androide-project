/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
#define _USE_MATH_DEFINES
//Variables globales
#define OFFSET 0.0
#define RANGE 0.3
//Zone de jeu
int rampeYMin=400;
int rampeYMax=700;
int nestYMin=950;
int nestYMax=1000;
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
    this->genSize = 24;
    std::vector<Specie> s(this->nbPop,Specie(this->nbAgent,this->genSize,19,this->genSize));
    this->s = s;
    for (int p = 0 ; p < this->nbPop ; p++){
        //this->s[p] = new Specie(nbAgent,genSize,19,genSize);
        this->s[p].initPop();
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
        object->setRegion(OFFSET,RANGE);
        object->relocate();
    }
}

void MyOwnProjectWorldObserver::initPost()
{
    
}

void MyOwnProjectWorldObserver::stepPre()
{
    std::cout << "aaaaaaaaaaaaaaaaa\n";
    //std::cout <<"New Turn \n";
    for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
    {
        //std::cout << "Drop analyse :" << i<<"\n";
        Robot *robot = (gWorld->getRobot(i));
        MyOwnProjectController *c = dynamic_cast<MyOwnProjectController*>(gWorld->getRobot(i)->getController());
        Point2d p =c->getPosition();
        //std::cout << "2 Drop analyse :" << i<<"\n";
        if(c->getCanInstantDrop()==true){
            c->setObjCollected(false);
            std::cout << "Drop it";
            int id = PhysicalObjectFactory::getNextId();
            MyEnergyItem *object = new MyEnergyItem(id);
            gPhysicalObjects.push_back( object );
            object->setDisplayColor(64,192,255);
            object->setType(1);
            float ori = c->getOrientation();
            std::cout << "One point ! #########################################################\n";
                
            if(p.y>rampeYMin && p.y < rampeYMax){
                int ymin = 700;
                int ymax = 730;
                object->relocate(ymin,ymax,true);
            }else if(p.y>nestYMin && p.y < nestYMax)
            {                    
                double objX = p.x - cos(M_PI*ori)*50;
                double objY = p.y - sin(M_PI*ori)*50;
                std::cout << "One point ! #########################################################\n";
                object->setRegion(OFFSET,RANGE);    
                object->relocate();
            }else{                    
                double objX = p.x - cos(M_PI*ori)*50;
                double objY = p.y - sin(M_PI*ori)*50;
                object->relocate(objX,objY,false,OFFSET,RANGE);
            }
            std::cout << "End\n";
        }
        
    }
    // The following code shows an example where every 100 iterations, robots are re-located to their initial positions, and parameters are randomly changed.
    //
    // REMOVE OR COMMENT THE FOLLOWING TO AVOID RESETTING POSITIONS EVERY 100 ITERATIONS
    //

    //std::cout << "Avant analyse pop :" << ( gWorld->getIterations() % 1000 == 0 )<<"\n";
    int nbIterPerGen = 100;
    bool end = true;
    //Reset
    std::cout << gWorld->getIterations() % 2500<<"\n";
    if ( gWorld->getIterations() % 2500 == 0 )
    {
        std::cout << "balbakboaek\n";
        this->s[this->popEtu].setFitness(this->getPoint());
        this->resetPoint();
        this->popEtu = this->popEtu+1;
        if(this->popEtu == this->nbPop){
            std::cout << "Evolution de populations";
            this->popEtu = 0;
            //Séléctions
            std::vector<Specie> newS(this->nbPop,Specie(this->nbAgent,this->genSize,19,this->genSize));
            for (int p = 0 ; p < this->nbPop ; p++){
                //this->s[p] = new Specie(nbAgent,genSize,19,genSize);
                newS[p].initPop();
            }
            this->selectionTournoi(this->s,this->nbAgent*0.8,newS);
            this->ajouterCroisement(this->s,newS,this->nbAgent*0.8,this->nbAgent*0.9);
            this->remplirRandom(newS,this->nbAgent*0.9);
            this->s=newS;
        }
        for ( int i = 0 ; i !=5 ; i++ )
        {
            Robot *robot = (gWorld->getRobot(i));
            
            (*robot).setCoordReal( random01()*800+100 , random01()*100+850  );
            
            MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
             
            std::vector<float> ga = this->s[i].getAgent(i);
            controller->setGenome(ga);
            controller->init();
            //std::cout << "Reset Robot Done\n";
        }
        this->initObjects();
        for (int i = 0 ; i != 5 ; i++){
            MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
            //std::cout << controller->getCanInstantDrop() << ": Object Collected\n";
        }
        
    }
    std::cout << "bbbbbbbbbbbbbbbbbbbbbbbbbb\n";
    
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
        Robot *robot = (gWorld->getRobot(i));
        
        
        MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
        
        controller->setGenome(p.getAgent(i));
    }
}


void MyOwnProjectWorldObserver::selectionTournoi(std::vector<Specie> s,int nbAgent,std::vector<Specie> newS){
    for( int i = 0 ; i < nbAgent ; i=i+2){
        int a=1,b=1,c=1,i1=1,i2=1;
        do{
            a=int(random01()*s.size());
            b=int(random01()*s.size());
            c=int(random01()*s.size());
        }while(a==b||b==c||c==a);
        if(a <= b && a <= c){
            i1 = b;
            i2 = c;
        }else if(c <= b && c <= a){
            i1 = b;
            i2 = a;
        }else if(b <= c && b <= a){
            i1 = c;
            i2 = a;
        }
        newS[i]=s[i1];
        newS[i+1]=s[i2];
    }
}
void MyOwnProjectWorldObserver::ajouterCroisement(std::vector<Specie> s,std::vector<Specie> newS,int iMin,int iMax){
    for( int i = 0 ; i < nbAgent ; i=i+2){
        int a=1,b=1,c=1,i1=1,i2=1;
        do{
            a=int(random01()*s.size());
            b=int(random01()*s.size());
            c=int(random01()*s.size());
        }while(a==b||b==c||c==a);
        if(a <= b && a <= c){
            i1 = b;
            i2 = c;
        }else if(c <= b && c <= a){
            i1 = b;
            i2 = a;
        }else if(b <= c && b <= a){
            i1 = c;
            i2 = a;
        }
        int f1 = s[i1].getFitness();
        int f2 = s[i2].getFitness();
        for(int j = 0 ; j < s[i1].getNbAgent() ; j ++){
            if(random01()*(f1+f2) < f1){
                newS[i].setAgent(s[i1].getAgent(j),j);
            }else{
                newS[i].setAgent(s[i2].getAgent(j),j);
            }
        }
    }
}
void MyOwnProjectWorldObserver::remplirRandom(std::vector<Specie> newS,int iMin){
    for(int i = iMin ; i < s.size() ; i++){
        newS[i]=Specie(this->nbAgent,this->genSize,19,this->genSize);
    }
}
void MyOwnProjectWorldObserver::stepPost()
{
    std::cout << "Blabla\n";
}


//Mes fonctions



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