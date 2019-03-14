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
#include "EvaluationPopulations/include/EvalMyEnergyItem.h"



EvaluationPopulationsWorldObserver::EvaluationPopulationsWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
    this->genomeHaut = "Comportements/MeilleurTypeHaut.txt";
    this->genomeBas = "Comportements/MeilleurTypeBas.txt";
    this->genomeComplet = "Comportements/MeilleurComplet.txt";
    this->nbOfH = 8;
    this->nbOfB = 2;
    this->nbOfComplet = 0;
    this->pointCount = 0;
    this->nbAgent = 10;
    this->depotMin = 400;
    this->depotMax = 450;
    this->rampeYMin=450;
    this->rampeYMax=700;
    this->nestYMin=950;
    this->nestYMax=1000;
    this->it =0;
    this->itPop = 0;
    this->set = false;/*
    this->nbIter = 10000;
    this->nbPop = this->nbAgent;
    std::vector<int>l{};
    this->resultats = l;
    std::vector<std::string>l2{};
    this->type = l2;*/
    std::cout << "Init\n";
}


EvaluationPopulationsWorldObserver::~EvaluationPopulationsWorldObserver()
{
	// nothing to do.
}

void EvaluationPopulationsWorldObserver::initPre()
{
    int nbObjectsTotal = 50;
    for ( int i = 0 ; i < nbObjectsTotal ; i++ )
    {
        // * create a new (custom) object
        
        int id = PhysicalObjectFactory::getNextId();
        EvalMyEnergyItem *object = new EvalMyEnergyItem(id);
        object->setDisplayColor(64,192,255);
        object->setType(1);
        object->setRegion(0.0,0.2);
        object->relocate(50,300,true);
        gPhysicalObjects.push_back( object );        
    }

    
    
}

void EvaluationPopulationsWorldObserver::initPost()
{
    std::cout<< "init post\n";
}

void EvaluationPopulationsWorldObserver::stepPre()
{
    this->it++;
    if(this->it%10000 == 9999){
        std :: cout << "Nb H " << this->nbOfH<< " Nb B " << this->nbOfB <<"\n";
        std :: cout << "Point : "<<this->getPoint() <<"\n";
        this->resetPoint();
        this->itPop ++;
        if(this->nbOfH > 0  && this->itPop == 5){
            this->itPop = 0;
            this->nbOfH--;
            this->nbOfB++;
        }
        this->set = false;
        if(this->nbOfH ==0){
            char str [80];
            int i;

            printf (".: ");
            scanf ("%79s",str);
        }
    }
    /*if(this->it %this->nbIter == 0){
        this->result.push_back(this->getPoint())*/
        if(!this->set){
            int nbBas = 0;
            int nbHaut = 0;
            int nbComp = 0;
            for ( int i = this->nbAgent-1 ; i !=-1 ; i-- )
            {
                if(nbComp<this->nbOfComplet){
                    this->readGenomeFile(this->genomeComplet,i);
                    nbComp++;
                }
                else if(nbBas < this->nbOfB){
                    this->readGenomeFile(this->genomeBas,i);
                    nbBas++;
                }
                else if(nbHaut < this->nbOfH){
                    this->readGenomeFile(this->genomeHaut,i);
                    nbHaut++;
                }
                Robot *robot = (gWorld->getRobot(i));
                
                (*robot).setCoordReal(random01()*800+100 , random01()*100+850  );
                EvaluationPopulationsController *controller = ((EvaluationPopulationsController*)(gWorld->getRobot(i)->getController()));
                /*std::cout << "Genome set :\n";
                for (auto i = controller->getGenome().begin(); i != controller->getGenome().end(); ++i)
                    std::cout << *i << ' ';
                std::cout <<"\n";*/
            }
            this->set = true;
                
        }
    //}
    //cout << "aa\n";
    for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
    {
        //std::cout << "Drop analyse :" << i<<"\n";
        EvaluationPopulationsController *c = dynamic_cast<EvaluationPopulationsController*>(gWorld->getRobot(i)->getController());
        Point2d p =c->getPosition();
        if(c->getCanInstantDrop()==true){
            //std::cout << "Dropped \n";
            c->setObjCollected(false);
            float ori = c->getOrientation();
            
            if(p.y>depotMin && p.y < rampeYMax){

                
                int id = PhysicalObjectFactory::getNextId();
                EvalMyEnergyItem *object = new EvalMyEnergyItem(id);
                gPhysicalObjects.push_back( object );
                object->setDisplayColor(64,192,255);
                object->setType(1);
                double objYMin = 700;
                double objYMax = 750;
                object->relocate(objYMin,objYMax,true);
                int id2 = PhysicalObjectFactory::getNextId();
                EvalMyEnergyItem *object2 = new EvalMyEnergyItem(id2);
                gPhysicalObjects.push_back( object2 );
                object2->setDisplayColor(64,192,255);
                object2->setType(1);
                objYMin = 50;
                objYMax = 300;
                object2->relocate(objYMin,objYMax,true);
            }else if(p.y>nestYMin && p.y < nestYMax)
            {                    
                this->addPoint();
            }
            else{                   

                int id = PhysicalObjectFactory::getNextId();
                EvalMyEnergyItem *object = new EvalMyEnergyItem(id);
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
                EvalMyEnergyItem *e = ((EvalMyEnergyItem*)gPhysicalObjects[i]);
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
    
    EvaluationPopulationsController *controller = ((EvaluationPopulationsController*)(gWorld->getRobot(iAgent)->getController()));
    
    controller->init();
    std::ifstream inFile(f);
    //inFile.open(f);
    if(!inFile){
        std::cout << "Cannot open";
    }
    std::string s="";
    int i =0;
    int nb = -1;


    std::vector<int> l{};
    std::vector<float> g{};
    while(std::getline(inFile,s)){
        /*std::cout << "debut boucle\n";
        std::cout << s <<":::\n";*/
        if(i == 2){
            vector<string> result={}; 
            boost::split(result, s, boost::is_any_of(",")); 
        
            for (int i = 0; i < result.size(); i++){
                l.push_back(std::stoi(result[i])); 
            }
            controller->setLayers(l);
            for(int i = 0 ; i < l.size()-1 ; i++){
                nb= nb+ l[i]*l[i+1];
            }
            //std::cout << "Layer set\n";
        }
        if(i==3){
            vector<string> result={}; 
            boost::split(result, s, boost::is_any_of(" ")); 
            //cout << "Génome : \n";
            for (int i = 0; i < result.size(); i++){
                if(result[i] != ""){
                    //cout << result[i]<<"-";
                    g.push_back(std::stof(result[i]));
                }
            }
            if(g.size() <nb){
                //std::cout << "size : " << g.size() << "instead of :" << nb<<"\n";
                //cout << "Error\n";
            }
            else if(g.size()>nb){
                //std::cout << "size : " << g.size() << "instead of :" << nb<<"\n";
                //cout << "Error\n";
            }
            controller->setGenome(g);
        }
            
        i=i+1;
        if( i>3){
            break;
        }
    }
    inFile.close();
    controller->init();
}