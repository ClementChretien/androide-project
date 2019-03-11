/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "EvaluationPopulations/include/EvaluationPopulationsWorldObserver.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include "EvaluationPopulations/include/EvaluationPopulationsController.h"
#include "RoboroboMain/roborobo.h"
#include "World/SquareObject.h"
#include "WorldModels/RobotWorldModel.h"
#include "MyOwnProject/include/MyEnergyItem.h"



EvaluationPopulationsWorldObserver::EvaluationPopulationsWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
    this->genomeHaut = "MeilleurTypeHaut.txt";
    this->genomeBas = "MeilleurTypeBas.txt";
    this->genomeComplet = "MeilleurComplet.txt";
    this->nbOfH = 5;
    this->nbOfB = 5;
    this->nbOfComplet = 5;
    this->pointCount = 0;
    this->nbAgent = 15;
    this->depotMin = 400;
    this->depotMax = 450;
    this->rampeYMin=450;
    this->rampeYMax=700;
    this->nestYMin=950;
    this->nestYMax=1000;
}


EvaluationPopulationsWorldObserver::~EvaluationPopulationsWorldObserver()
{
	// nothing to do.
}

void EvaluationPopulationsWorldObserver::initPre()
{
    std::cout << "Test\n";
    int nbObjectsTotal = 50;
    for ( int i = 0 ; i < nbObjectsTotal ; i++ )
    {
        // * create a new (custom) object
        
        std::cout << "Test2\n";
        int id = PhysicalObjectFactory::getNextId();
        MyEnergyItem *object = new MyEnergyItem(id);
        std::cout << "Test3\n";
        object->setDisplayColor(64,192,255);
        object->setType(1);
        object->setRegion(0.0,0.2);
        object->relocate(50,300,true);
        gPhysicalObjects.push_back( object );
        std::cout << "Test4\n";
        
    }

    
    std::cout << "Test5\n";
    for(int i = 0 ; i < this->nbAgent ; i++){
        if(i>this->nbOfH+nbOfB){
            this->readGenomeFile(this->genomeComplet,i);
        }
        else if(i>this->nbOfH){
            this->readGenomeFile(this->genomeBas,i);
        }
        else{
            this->readGenomeFile(this->genomeHaut,i);
        }
    }
    std::cout << "Test\n";
}

void EvaluationPopulationsWorldObserver::initPost()
{
    
}

void EvaluationPopulationsWorldObserver::stepPre()
{
    for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
        {
            //std::cout << "Drop analyse :" << i<<"\n";
            EvaluationPopulationsController *c = dynamic_cast<EvaluationPopulationsController*>(gWorld->getRobot(i)->getController());
            Point2d p =c->getPosition();
            //std::cout << "2 Drop analyse :" << i<<"\n";
            if(c->getCanInstantDrop()==true){
                //std::cout << "Dropped \n";
                c->setObjCollected(false);
                float ori = c->getOrientation();
                
                if(p.y>depotMin && p.y < rampeYMax){

                    
                    int id = PhysicalObjectFactory::getNextId();
                    MyEnergyItem *object = new MyEnergyItem(id);
                    gPhysicalObjects.push_back( object );
                    object->setDisplayColor(64,192,255);
                    object->setType(1);
                    double objYMin = 700;
                    double objYMax = 750;
                    object->relocate(objYMin,objYMax,true);
                }else if(p.y>nestYMin && p.y < nestYMax)
                {                    
                    this->addPoint();
                }
                else{                   

                    int id = PhysicalObjectFactory::getNextId();
                    MyEnergyItem *object = new MyEnergyItem(id);
                    gPhysicalObjects.push_back( object );
                    object->setDisplayColor(64,192,255);
                    object->setType(1);
                    double objX = p.x - cos(M_PI*ori)*50;
                    double objY = p.y - sin(M_PI*ori)*50;
                    object->relocate(objX,objY,false,0.0,0.2);
                }
            }
            
        }
    
}
void EvaluationPopulationsWorldObserver::initObjects(){
    int nbObj = 50;

    for (int i = 0 ; i < gPhysicalObjects.size() ; i++){
        if(i >= gPhysicalObjects.size() - nbObj){
                
            //std::cout << i<<":"<<gPhysicalObjects.size() <<"\n";
            if(gPhysicalObjects[i]->isVisible()){
                //std::cout << i<<":"<<gPhysicalObjects.size() <<"\n";
                //gPhysicalObjects[i]->setRegion(0.0,0.2);
                MyEnergyItem *e = ((MyEnergyItem*)gPhysicalObjects[i]);
                e->setRegion(0.0,0.2);
                e->relocate(50,300,false);
            }
            else{
                std::cout << "Found\n";
            }
        
        }else{
            gPhysicalObjects[i]->hide();
            //gPhysicalObjects[i]->setDisplayColor(100,100,100);
            gPhysicalObjects[i]->unregisterObject();
        }
    }
}

void EvaluationPopulationsWorldObserver::initAgents(int nbAgent,Specie p){
    for ( int i = 0 ; i !=nbAgent ; i++ )
    {
        EvaluationPopulationsController *controller = ((EvaluationPopulationsController*)(gWorld->getRobot(i)->getController()));
        
        controller->setGenome(p.getAgent());
    }
}

void EvaluationPopulationsWorldObserver::addPoint(){
    this->addPoint(1);
}
void EvaluationPopulationsWorldObserver::addPoint(int p){
    this->pointCount=this->pointCount +p;
}
void EvaluationPopulationsWorldObserver::removePoint(int p){
    this->pointCount=this->pointCount -p;
}
void EvaluationPopulationsWorldObserver::resetPoint(){
    this->pointCount=0;
}
int EvaluationPopulationsWorldObserver::getPoint(){
    return this->pointCount;
}
void EvaluationPopulationsWorldObserver::stepPost()
{
}

void EvaluationPopulationsWorldObserver::writeFile(std::vector<int> s){
    /*int iMin =-1;
    int vMin = -1;
    for(int j = 0 ; j < s.size() ; j++){
        if(s[j].getFitness()>vMin){
            iMin = j;
            vMin = s[j].getFitness();
        }
    }

        
    std::vector<float> ga = this->s[iMin].getAgent();
    ofstream myfile;
    myfile.open("Resultat.txt");
    myfile << "Generation :" << this->generation;
    if(this->evalType == 0){
        myfile << " type complet";
    }else if(this->evalType == 1){
        myfile << " type Haut";
    } else if(this->evalType == 2){
        myfile << " type Bas";
    }
    myfile << "\n Fitness :" << vMin << "\n";
    
    for(int l = 0 ; l < ga.size() ; l++){
        myfile <<ga[l] <<" ";
    }
    myfile.close();*/
}

void EvaluationPopulationsWorldObserver::readGenomeFile(std::string f,int iAgent){
    std::cout << "Cannot";
    Robot *robot = (gWorld->getRobot(iAgent));
            
    (*robot).setCoordReal( random01()*800+100 , random01()*100+850  );
    
    EvaluationPopulationsController *controller = ((EvaluationPopulationsController*)(gWorld->getRobot(iAgent)->getController()));
    
    controller->init();
    ifstream inFile;
    inFile.open(f);
    if(!inFile){
        std::cout << "Cannot open";
    }
    std::string s;
    int i =0;
    std::vector<int> l{};
    std::vector<float> g{};
    for( std::string s; getline( inFile, s ); )
    {
        if(i ==2){
            std::string delimiter = ",";

            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                l.push_back(std::stoi(token));
                std::cout << token << std::endl;
                s.erase(0, pos + delimiter.length());
            }
            controller->setLayers(l);
            std::cout << s << std::endl;
        }
        if(i==3){
            std::string delimiter = ",";

            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                g.push_back(std::stoi(token));
                std::cout << token << std::endl;
                s.erase(0, pos + delimiter.length());
            }
            controller->setGenome(g);
            std::cout << s << std::endl;
        }
        std::cout << s;
        std::cout << "\n";
        i=i+1;
    }
}