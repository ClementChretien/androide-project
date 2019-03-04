/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
#define _USE_MATH_DEFINES
//Variables globales
//Zone de jeu
int zoneCollectMin = 50;
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
    this->nbAgent = 1;
    this->nbPop = 50;
    std::vector<int>l{20,3};
    this->layers = l;
    this->popEtu = 0;
    this->genSize = 20*3;
    this->generation=0;
    this->cptName=0;
    this->evalType = 1;
    this->numberMaxOfGen = 250;
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
        object->relocate(50,400,true);
    }
}

void MyOwnProjectWorldObserver::initPost()
{
    
}

void MyOwnProjectWorldObserver::stepPre()
{
    if(this->numberMaxOfGen> this->generation){
        
        //std::cout <<"New Turn \n";
        for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
        {
            //std::cout << "Drop analyse :" << i<<"\n";
            MyOwnProjectController *c = dynamic_cast<MyOwnProjectController*>(gWorld->getRobot(i)->getController());
            Point2d p =c->getPosition();
            //std::cout << "2 Drop analyse :" << i<<"\n";
            if(c->getCanInstantDrop()==true){
                c->setObjCollected(false);
                float ori = c->getOrientation();
                
                if(p.y>rampeYMin && p.y < rampeYMax){

                    //
                    if(this->evalType == 1){
                        std::cout << "Dropped in slope!\n";
                        this->addPoint(500);
                    }
                }else if(p.y>nestYMin && p.y < nestYMax)
                {                    
                    //std::cout << "Dropped in nest!\n";
                    if(this->evalType == 2||this->evalType == 0){
                        this->addPoint(10000);
                    }
                }
                else{                   

                    int id = PhysicalObjectFactory::getNextId();
                    MyEnergyItem *object = new MyEnergyItem(id);
                    gPhysicalObjects.push_back( object );
                    object->setDisplayColor(64,192,255);
                    object->setType(1);
                    double objX = p.x - cos(M_PI*ori)*50;
                    double objY = p.y - sin(M_PI*ori)*50;
                    object->relocate(objX,objY,false,0.0,0.3);
                    this->removePoint(100);
                }
            }
            
        }
        // The following code shows an example where every 100 iterations, robots are re-located to their initial positions, and parameters are randomly changed.
        //
        // REMOVE OR COMMENT THE FOLLOWING TO AVOID RESETTING POSITIONS EVERY 100 ITERATIONS
        //

        evaluation();
        //Reset
        if ( gWorld->getIterations() % 5000 == 0 )
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
                std::cout << "Evolution de populations\n";
                this->popEtu = 0;
                //Séléctions
                std::vector<Specie> newS(this->nbPop,Specie(this->genSize));
                newS = this->selectionTournoi(this->s,newS,s.size()*0.7);
                newS = this->remplirRandom(newS,s.size()*0.9);
                //newS = this->ajouterCroisement(this->s,newS,this->nbPop*0.8,this->nbPop);
                //Mutation
                newS = this->mutation(newS,3);
                this->s=newS;
            }
            for ( int i = 0 ; i !=this->nbAgent ; i++ )
            {
                Robot *robot = (gWorld->getRobot(i));
                
                (*robot).setCoordReal( random01()*800+100 , random01()*100+850  );
                
                MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
                
                std::vector<float> ga = this->s[this->popEtu].getAgent();
                /*std::cout << "\n ";
                for(int l = 0 ; l < ga.size() ; l++){
                    std::cout <<ga[l] <<" ";
                }
                std::cout << "\n ";*/
                controller->setLayers(this->layers);
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
    else if(this->generation == this->numberMaxOfGen){
        std::cout << "Fin\n";
        this->generation++;
        int iMin =-1;
        int vMin = -1;
        for(int j = 0 ; j < s.size() ; j++){
            if(s[j].getFitness()>vMin){
                iMin = j;
                vMin = s[j].getFitness();
            }
        }
        for ( int i = 0 ; i !=this->nbAgent ; i++ )
        {
            Robot *robot = (gWorld->getRobot(i));
            
            (*robot).setCoordReal( random01()*800+100 , random01()*100+850  );
            
            MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
            
            std::vector<float> ga = this->s[iMin].getAgent();
            /*std::cout << "\n ";
            for(int l = 0 ; l < ga.size() ; l++){
                std::cout <<ga[l] <<" ";
            }
            std::cout << "\n ";*/
            controller->setLayers(this->layers);
            controller->setGenome(ga);
            controller->init();
            //std::cout << "Reset Robot Done\n";
        }
        std::cout << "Fitness meilleur : " << s[iMin].getFitness()<<"\n";
        if(this->evalType == 0){
            std::cout << "Meilleure pop pour le type Normale\n";
        }
        else if(this->evalType == 1){
            std::cout << "Meilleure pop pour le type Haut\n";
        }
        else if(this->evalType == 2){
            std::cout << "Meilleure pop pour le type Bas\n";
        }
    }
    
}
void MyOwnProjectWorldObserver::initObjects(){
    for (int i = 0 ; i < gPhysicalObjects.size() ; i++){
        if(i<=50){
                
            //std::cout << i<<":"<<gPhysicalObjects.size() <<"\n";
            if(gPhysicalObjects[i]->isVisible()){
                //std::cout << i<<":"<<gPhysicalObjects.size() <<"\n";
                //gPhysicalObjects[i]->setRegion(0.0,0.3);
                MyEnergyItem *e = ((MyEnergyItem*)gPhysicalObjects[i]);
                e->relocate(50,400,false);
            }
        
        }else{
            gPhysicalObjects[i]->unregisterObject();
        }
    }
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

void MyOwnProjectWorldObserver::initAgents(int nbAgent,Specie p){
    for ( int i = 0 ; i !=nbAgent ; i++ )
    {
        MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
        
        controller->setGenome(p.getAgent());
    }
}


std::vector<Specie> MyOwnProjectWorldObserver::selectionTournoi(std::vector<Specie> s,std::vector<Specie> newS, int nb){
    //Prendre x pop et selectionner juste le meilleur
    int tailleRec=  s.size()/20+1;
    std::vector<int> toAdd;
    for( int i = 0 ; i < s.size() ; i++){
        if(random01()*s.size()<nb){
                
            toAdd.resize(0);
            while(toAdd.size()<tailleRec){
                toAdd.push_back(int(random01()*s.size()));
            }
            int iMin = int(random01()*s.size());
            int vMin = s[iMin].getFitness();
            for (int j = 0 ; j < toAdd.size() ; j++){
                if(vMin == -1||s[j].getFitness()> vMin){
                    iMin = j;
                    vMin = s[j].getFitness();
                }
            }
            //std::cout <<" Pop choisie : " << s[iMin].getName()<<"\n";
            
            newS[i]=s[iMin];
        }else{
            newS[i]=s[i];
        }
    }
    int iMin = int(random01()*s.size());
    int vMin = s[iMin].getFitness();
    for (int j = 0 ; j < s.size() ; j++){
        if(vMin == -1||s[j].getFitness()> vMin){
            iMin = j;
            vMin = s[j].getFitness();
        }
    }
    newS[0]=s[iMin];
    return newS;
}

std::vector<Specie> MyOwnProjectWorldObserver::remplirRandom(std::vector<Specie> newS,int iMin){
    for(int i = iMin ; i < newS.size() ; i++){
        newS[i]=Specie(this->genSize);
        newS[i].setName("RPop"+std::to_string(i));
    }
    return newS;
}
std::vector<Specie> MyOwnProjectWorldObserver::mutation(std::vector<Specie> newS, int nbToMutate){
    for(int i = 0 ; i < newS.size() ; i++){
        for(int j = 0 ; j < nbToMutate ; j++){
            int r = newS[0].getGenSize()*random01();
            newS[i].setNucleo(r,random01()*2-1);
        }
    }
    return newS;
}
void MyOwnProjectWorldObserver::evaluationNormale(){
    for ( int i = 0 ; i !=this->nbAgent ; i++ )
    {
        MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
        
        Point2d p = controller->getPosition();
        if(controller->getObjCollected() == true && controller->getIsObserved() == false){
            this->addPoint(100);
            controller->setIsObserved(true);
        }
        if(p.y>nestYMin && p.y<nestYMax && controller->getObjCollected()){
            this->addPoint(1);
        }
        if(p.y>zoneCollectMin && p.y<rampeYMin && !controller->getObjCollected()){
            this->addPoint(1);
        }
    }
}
void MyOwnProjectWorldObserver::evaluationHaut(){
    for ( int i = 0 ; i !=this->nbAgent ; i++ )
    {
        MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
        
        Point2d p = controller->getPosition();
        if(p.y>nestYMin && p.y<nestYMax){
            this->addPoint();
        }
    }
}
void MyOwnProjectWorldObserver::evaluationBas(){
    for ( int i = 0 ; i !=this->nbAgent ; i++ )
    {
        MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
        
        Point2d p = controller->getPosition();
        if(p.y<rampeYMin ){
            this->addPoint();
        }
    }

}
void MyOwnProjectWorldObserver::evaluation(){
    if(this->evalType == 0){
        this->evaluationNormale();
    }
    else if(this->evalType == 1){
        this->evaluationHaut();
    }
    else if(this->evalType == 2){
        this->evaluationBas();
    }
}

void MyOwnProjectWorldObserver::addPoint(){
    this->addPoint(1);
}
void MyOwnProjectWorldObserver::addPoint(int p){
    this->pointCount=this->pointCount +p;
}
void MyOwnProjectWorldObserver::removePoint(int p){
    this->pointCount=this->pointCount -p;
}
void MyOwnProjectWorldObserver::resetPoint(){
    this->pointCount=0;
}
int MyOwnProjectWorldObserver::getPoint(){
    return this->pointCount;
}
void MyOwnProjectWorldObserver::stepPost()
{
}