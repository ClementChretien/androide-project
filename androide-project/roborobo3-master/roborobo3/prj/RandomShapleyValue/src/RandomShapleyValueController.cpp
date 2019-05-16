/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "RandomShapleyValue/include/RandomShapleyValueController.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"
#include <iostream>
using namespace std; 
#include <cmath> 
// Load readable sensor names
#define NB_SENSORS 12 // assume 12 sensors
#include "Utilities/Sensorbelt.h"


RandomShapleyValueController::RandomShapleyValueController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
    init();
    std::vector<float> genome{1};
    this->genome = genome;
    this->genome.resize(17*3,0);
    std::vector<int> layers{17,3};
    this->layers = layers;
    size_t nbParams = 14;
    _params.resize(nbParams,0); // initialize an array with zero values.
}
void RandomShapleyValueController::init(){
    this->setObjCollected(false);
    this->setCanInstantDrop(false);
    this->setIsObserved(false);
}
RandomShapleyValueController::~RandomShapleyValueController()
{
	// nothing to do.
}

void RandomShapleyValueController::reset()
{
	// nothing to do.
}

vector<float> RandomShapleyValueController::definirEntree(){
    vector<float> x;
    //Size 17
    //7* distance to object
    //7* distance to wall
    //ObjectCollected
    //Position [0 nest,1 nest/slope,2 slope, 3 collect]
    //Biais
    double dist_L = getDistanceAt(SENSOR_L);
    double dist_FL = getDistanceAt(SENSOR_FL);
    double dist_FFL = getDistanceAt(SENSOR_FFL);
    double dist_F = getDistanceAt(SENSOR_F);
    double dist_R = getDistanceAt(SENSOR_R);
    double dist_FR = getDistanceAt(SENSOR_FR);
    double dist_FFR = getDistanceAt(SENSOR_FFR);
    //Object
    if(getObjectAt(SENSOR_L)==1){
        x.push_back(dist_L);
    }else{
        x.push_back(0);
    }
    if(getObjectAt(SENSOR_FFL)==1){
        x.push_back(dist_FFL);
    }else{
        x.push_back(0);
    }

    if(getObjectAt(SENSOR_FL)==1){
        x.push_back(dist_FL);
    }else{
        x.push_back(0);
    }
    if(getObjectAt(SENSOR_F)==1){
        x.push_back(dist_F);
    }else{
        x.push_back(0);
    }
    if(getObjectAt(SENSOR_R)==1){
        x.push_back(dist_R);
    }else{
        x.push_back(0);
    }
    if(getObjectAt(SENSOR_FR)==1){
        x.push_back(dist_FR);
    }else{
        x.push_back(0);
    }
    if(getObjectAt(SENSOR_FFR)==1){
        x.push_back(dist_FFR);
    }else{
        x.push_back(0);
    }
    //Mur
    if(getWallAt(SENSOR_L)==1){
        x.push_back(dist_L);
    }else{
        x.push_back(0);
    }
    if(getWallAt(SENSOR_FFL)==1){
        x.push_back(dist_FFL);
    }else{
        x.push_back(0);
    }
    if(getWallAt(SENSOR_FL)==1){
        x.push_back(dist_FL);
    }else{
        x.push_back(0);
    }
    if(getWallAt(SENSOR_F)==1){
        x.push_back(dist_F);
    }else{
        x.push_back(0);
    }
    if(getWallAt(SENSOR_R)==1){
        x.push_back(dist_R);
    }else{
        x.push_back(0);
    }
    if(getWallAt(SENSOR_FR)==1){
        x.push_back(dist_FR);
    }else{
        x.push_back(0);
    }
    if(getWallAt(SENSOR_FFR)==1){
        x.push_back(dist_FFR);
    }else{
        x.push_back(0);
    }
    if(this->getObjCollected()){
        x.push_back(1);
    }
    else{
        x.push_back(0);
    }
    int depotMin = 400;
    int rampeYMin=450;
    int rampeYMax=700;
    int recupMax = 700;
    int nestYMin=950;
    int nestYMax=1000;
    Point2d p = this->getPosition();
    if(p.y>rampeYMin && p.y < rampeYMax){
        x.push_back(1);
    }
    else{
        x.push_back(0);
    }
    if(p.y>nestYMin && p.y < nestYMax)
    {                    
        x.push_back(1);
    }
    else{
        x.push_back(0);
    }
    if(p.y>depotMin && p.y < rampeYMin)
    {                    
        x.push_back(1);
    }
    else{
        x.push_back(0);
    }
    if(p.y>rampeYMax && p.y < recupMax)
    {                    
        x.push_back(1);
    }
    else{
        x.push_back(0);
    }
    if(p.y>nestYMax && p.y < rampeYMin)
    {                    
        x.push_back(1);
    }
    else{
        x.push_back(0);
    }
    if(p.y<rampeYMin){       
        x.push_back(1);
    }
    else{
        x.push_back(0);
    }
    x.push_back(this->getOrientation());
    //Biais
    x.push_back(1);
    return x;
}
std::vector<float> RandomShapleyValueController::calculateSortie(std::vector<float> x){
    //sortie : 0 = rotation 1 = translation 2 = drop
    //calcul taille genome /3 :
    int sizeGenome =0;
    

    for (int i = 0 ; i < this->layers.size()-1 ; i++){
        sizeGenome = sizeGenome+layers[i]*layers[i+1];
    }
    int posCouchePoids = 0;
    std::vector<float> xI;
    for (int lay = 1 ; lay < this->layers.size() ; lay++){
        xI.resize(layers[lay]);
        std::fill(xI.begin(), xI.end(), 0);
        for (int i = 0 ; i < layers[lay] ; i++){
            for(int j = 0 ; j < layers[lay-1] ; j++){
                xI[i]=xI[i]+x[j]*this->genome[posCouchePoids + j*layers[lay]+i];
            }
            xI[i] = tanh(xI[i]);
        }
        x = xI;
        posCouchePoids = posCouchePoids + layers[lay-1]*layers[lay];
    }
    return x;
}
//AG step
void RandomShapleyValueController::step(){
    //std::cout << "Step controller\n";
    std::vector<float> sortie = this->calculateSortie(this->definirEntree());
    /*std::cout << "Vec entrée:\n";
    for (auto i = this->genome.begin(); i != this->genome.end(); ++i)
        std::cout << *i << ' ';
    std::cout <<"\n";*/
    if(sortie.back()>0.5 && this->getObjCollected()==true){
        this->setCanInstantDrop(true);
    }
    sortie.pop_back();
    setRotation(sortie.back()*0.3);
    sortie.pop_back();
    
    Point2d p = getPosition(); 
    double normalT = abs(sortie.back());
        
    double maxRampSpeed = 0.01;
    double minRampSpeed = -0.01;
    double orientation = getOrientation();
    //std::cout << "Translation : "<<normalT<<"\n";
    if (/*p.x > 250 && p.x < 670 &&*/ p.y > 450&& p.y < 700){
        if(normalT > maxRampSpeed)
            setTranslation(maxRampSpeed);
        else if (normalT < minRampSpeed)
            setTranslation(minRampSpeed);
        else
            setTranslation(std::min((double)1,normalT));     
    }
    else{
        setTranslation(std::min((double)1,normalT));
    }   
    /*if(sortie.back()<0){
        setTranslation(-sortie.back());    
    }
    else{
        setTranslation(sortie.back());
    }*/
    sortie.pop_back();
}
//Fonctions de ramassage et dépôt d'objets
bool RandomShapleyValueController::getCanCollect(){
    return this->canCollect;
}
bool RandomShapleyValueController::getCanDropSlope(){
    return this->canDropSlope;
}
bool RandomShapleyValueController::getCanDropNest(){
    return this->canDropNest;
}
bool RandomShapleyValueController::getCanInstantDrop(){
    return this->instantDrop;
}
bool RandomShapleyValueController::getObjCollected(){
    return this->objCollected;
}
bool RandomShapleyValueController::getIsObserved(){
    return this->objObserved;
}
std::vector<int> RandomShapleyValueController::getLayers(){
    return this->layers;
}

void RandomShapleyValueController::setCanCollect(bool c){
    this->canCollect = c;
}
void RandomShapleyValueController::setCanDropSlope(bool c){
    this->canDropSlope = c;
}
void RandomShapleyValueController::setCanDropNest(bool c){
    this->canDropNest = c;
}
void RandomShapleyValueController::setCanInstantDrop(bool c){
    this->instantDrop = c;
}
void RandomShapleyValueController::setIsObserved(bool c){
    this->objObserved=c;
}
void RandomShapleyValueController::setObjCollected(bool c){
    this->objCollected = c;
    if(c == true){
        //std::cout << "Can not collect anymore\n";
        this->setCanCollect(false);
        this->setIsObserved(false);
        //this->setCanDropSlope(true);
        //this->setCanDropNest(true);
        //this->setCanInstantDrop(true);
    }
    else if(c == false){
        //std::cout << "Can recollect\n";
        this->setCanCollect(true);
        //this->setCanDropSlope(false);
        //this->setCanDropNest(false);
        this->setCanInstantDrop(false);
    }
}
void RandomShapleyValueController::setLayers(std::vector<int> l){
    int nb = 0;
    for(int i = 0 ; i < l.size()-1 ; i++){
        nb= nb+ l[i]*l[i+1];
    }
    this->genome.resize(nb,0);
    this->layers=l;
}

//Fonctions
void RandomShapleyValueController::setGenome(std::vector<float> g){
    for (int i = 0 ; i< g.size() ; i++){
        //std::cout << i << g.size()<<"\n";
        this->genome[i]=g[i];
    }
    /*std::cout << "Genome set inside controller\n";
    for (auto i = this->genome.begin(); i != this->genome.end(); ++i)
        std::cout << *i << ' ';
    std::cout <<"\n";*/
}
std::vector<float> RandomShapleyValueController::getGenome(){
    return this->genome;
}



/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/*                                                                                                     */
/*    Everything after this comment can be safely ignored (and removed).                               */
/*    The two following methods illustrates how to access all information available to the robot.      */
/*                                                                                                     */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */


void RandomShapleyValueController::monitorSensoryInformation()
{
    // Note that this code is executed only for the agent which is "on focus". By default, this means agent #0.
    // When window mode:
    //      To show which agent has the focus, press 'F'
    //      To cycle through agents, press <tab> (or shift+<tab>)
    
    
    if ( gVerbose && gDisplayMode == 0 && gRobotIndexFocus == _wm->getId() )
    {
        
        std::cout << "=-= Robot #" << _wm->getId() << " : STARTING monitoring sensory information at iteration #" << gWorld->getIterations() << ".\n";
        
        inspect();
        
        double srcOrientation = _wm->_agentAbsoluteOrientation;
        
        // Landmarks
        //      - landmarks are invisible and intangible object that can act as magnetic point of interest.
        //      - usually used by providing direction and orientation wrt. the robot
        //      - example of use: magnetic compass, detection of direction to specific zone, etc.
        //      - closest landmark can be computed automatically (see below, last part)
        
        if ( gNbOfLandmarks > 0 )
        {
            // All landmarks (if any)
            
            for ( int i = 0 ; i != gNbOfLandmarks ; i++ )
            {
                Point2d posRobot(_wm->getXReal(),_wm->getYReal());
                Point2d closestPoint;
                
                double distanceToLandmark = getEuclideanDistance (posRobot,gLandmarks[0]->getCoordinates());
                double diffAngleToClosestLandmark = getAngleToTarget(posRobot,_wm->_agentAbsoluteOrientation,gLandmarks[i]->getCoordinates());
                
                std::cout << "Landmark " << i << " is at distance " << distanceToLandmark << ", angle = " << diffAngleToClosestLandmark << "\n";
            }
            
            // Closest landmark (in any)
            
            _wm->updateLandmarkSensor();
            std::cout << "Closest landmark is at distance " << std::setw(6) << _wm->getLandmarkDistanceValue() << ", angle = " << std::setw(6) << _wm->getLandmarkDirectionAngleValue() << "\n";
        }
        else
            std::cout << "No landmark.\n";
        
        // Energy (unused)
        //      - in this code: energy is ignored.
        //      - battery level can be used in some experiment. Impact of battery level is to be managed locally.
        //      - EnergyRequest can be used in some experiment with specific energy point where only part of energy can harvest.
        
        std::cout << "Battery-level  : " << std::setw(6) << _wm->getEnergyLevel() << "\n"; // useless here
        std::cout << "Energy Requested (if asked) : " << std::setw(4) << _wm->getEnergyRequestValue() << "" << std::endl;
        
        // Floor sensor
        //      - read from gFootprintImage (see gFootprintImageFilename file)
        //      - typical use: gradient written on the floor, region marker. Could also be used for pheronome.
        
        double floorSensor_redValue = (double)_wm->getGroundSensor_redValue()/255.0;
        double floorSensor_greenValue = (double)_wm->getGroundSensor_greenValue()/255.0;
        double floorSensor_blueValue = (double)_wm->getGroundSensor_blueValue()/255.0;
        
        std::cout << "Floor sensor values: red=" << std::setw(4) << floorSensor_redValue << " ; green=" << std::setw(4) << floorSensor_greenValue << " ; blue=" << std::setw(4) << floorSensor_blueValue << ".\n";
        
        // LED sensor (on the robot)
        //      -
        
        double LED_redValue = (double)_wm->getRobotLED_redValue()/255.0;
        double LED_greenValue = (double)_wm->getRobotLED_greenValue()/255.0;
        double LED_blueValue = (double)_wm->getRobotLED_blueValue()/255.0;
        
        std::cout << "LED values: red=" << std::setw(4) << LED_redValue << " ; green=" << std::setw(4) << LED_greenValue << " ; blue=" << std::setw(4) << LED_blueValue << ".\n";
        
        // Camera/distance sensors -- provide: distance to obstacle, obstacle type, orientation (if robot)
        // REMARKS:
        //      - distance sensors are actually camera rays, and provides extended information:
        //          - distance to contact
        //          - type of contact (walls, objects, or robots)
        //          - if robot: group number, LED values, absolute orientation (from which one can compute relative orientation)
        //      - Objects and walls are different.
        //          - Walls are fixed, and loaded from gEnvironmentImage (see gEnvironmentImageFilename file)
        //          - There are several types of objects. Check children of object PhysicalObject.
        //          - Note that PhysicalObjects can have a tangible part (see gEnvironmentImage) and an intangible part (see gFootprintImage. The intangible part can be spotted with the floorSensor.
        //          - Some PhysicalObject are active and react to the robot actions (e.g. disappear, give energy, ...)
        //          - examples of use of a PhysicalObject:
        //              - a tangible object onto which the robot can crash. It is seen through distance sensors.
        //              - an intangible object onto which the robot can walk upon. It is seen through the floor sensor.
        //              - a mix of the two.
        
        for(int i  = 0; i < _wm->_cameraSensorsNb; i++)
        {
            double distance = _wm->getDistanceValueFromCameraSensor(i);
            // double distanceNormalized = _wm->getDistanceValueFromCameraSensor(i) / _wm->getCameraSensorMaximumDistanceValue(i); // Similar to _wm->getNormalizedDistanceValueFromCameraSensor(i); -- unused here

            int objectId = _wm->getObjectIdFromCameraSensor(i);
            
            std::cout << "Sensor #" << i << ":";
            
            if ( PhysicalObject::isInstanceOf(objectId) ) // sensor touched an object. What type? (could be GateObject, SwitchObject, RoundObject, ... -- check descendants of PhysicalObject class)
            {
                int nbOfTypes = PhysicalObjectFactory::getNbOfTypes();
                for ( int i = 0 ; i != nbOfTypes ; i++ )
                {
                    if ( i == gPhysicalObjects[objectId - gPhysicalObjectIndexStartOffset]->getType() )
                    {
                        std::cout << "object of type " << i << " detected\n";
                        break;
                    }
                }
            }
            else
            {
                if ( Agent::isInstanceOf(objectId) )
                {
                    int targetRobotId = objectId-gRobotIndexStartOffset;

                    std::cout << " touched robot #" << gWorld->getRobot(targetRobotId) << ", at distance " << std::setw(4) << distance << ".\n";
                    
                    std::cout << "\tTouched robot information:\n";
                    std::cout << gWorld->getRobot(targetRobotId)->getController()->inspect();
                    
                    // Distance to target , orientation wrt target, target absolute orientation, target LED values
                    // Distance to target is approximated through sensor ray length before contact.
                    
                    double tgtOrientation = gWorld->getRobot(targetRobotId)->getWorldModel()->_agentAbsoluteOrientation;
                    double delta_orientation = - ( srcOrientation - tgtOrientation );
                    if ( delta_orientation >= 180.0 )
                        delta_orientation = - ( 360.0 - delta_orientation );
                    else
                        if ( delta_orientation <= -180.0 )
                            delta_orientation = - ( - 360.0 - delta_orientation );
                    
                    std::cout << "\trelative orientation wrt target robot is " <<std::setw(4) << delta_orientation/180.0 << "\n";
                    std::cout << "\tabsolute orientation of target robot is  " <<std::setw(4) << tgtOrientation << "\n";
                    
                    // same group? -- unusued as of Oct. 2015
                    
                    if ( gWorld->getRobot(targetRobotId)->getWorldModel()->getGroupId() == _wm->getGroupId() )
                        std::cout << "\trobots are from the same group.\n";
                    else
                        std::cout << "\trobots are from different group.\n";
                    
                    // LED values of other robot (can be used for communication)
                    
                    double tgt_LED_redValue = (double)_wm->getRobotLED_redValue()/255.0;
                    double tgt_LED_greenValue = (double)_wm->getRobotLED_greenValue()/255.0;
                    double tgt_LED_blueValue = (double)_wm->getRobotLED_blueValue()/255.0;
                    
                    std::cout << "\tLED values: R=" << tgt_LED_redValue << ", G=" << tgt_LED_greenValue << ", B=" << tgt_LED_blueValue << "\n";
                    
                }
                else
                {
                    // input: wall or empty?
                    if ( objectId >= 0 && objectId < gPhysicalObjectIndexStartOffset ) // not empty, but cannot be identified: this is a wall.
                    {
                        std::cout << " touched an unindentified obstacle (probably a wall, id=" << objectId << "), at distance " << std::setw(4) << distance << ".\n";
                    }
                    else
                        std::cout << " nothing (id="<< objectId << "). Returns maximum value (" << std::setw(4) << distance << ")\n";
                }
            }
        }
        std::cout << "=-= Robot #" << _wm->getId() << " : STOPPING monitoring sensory information\n";
    }
    
}


std::string RandomShapleyValueController::inspect( std::string prefix )
{
    // Rotational and translational speed, agent orientation wrt. upwards
    //      - *actual* and *desired* translational/rotational values are very different
    //          - actual values is what the robot is actually doing (this is measured)
    //          - desired values are set by the controller (this is set and the hardware controller tries to match it)
    //          - rational: you may ask for something (e.g. max speed) but physics and electronics may be limited
    //          - typical example: when going for max speed, the robot cannot instantaneously go at max speed.
    //      - agent orientation acts as a compass with respect the y-axis, similar to a magnetic compass where north is upward
    
    std::string s = "";
    std::stringstream out;
    
    out << prefix << "Agent identifier: " << std::setw(4) << _wm->getId() << "\n";
    out << prefix << "Agent orientation: " << std::setw(4) << _wm->_agentAbsoluteOrientation << "° wrt North (ie. upwards).\n";
    out << prefix << "Agent desired translational speed: " << _wm->_desiredTranslationalValue << std::endl;
    out << prefix << "Agent desired rotational speed: " << std::setw(4) << _wm->_desiredRotationalVelocity << std::endl;
    out << prefix << "Agent actual translational speed: " << _wm->_actualTranslationalValue << std::endl;
    out << prefix << "Agent actual rotational speed: " << std::setw(4) << _wm->_actualRotationalVelocity << std::endl;
    
    s = out.str();
    return s;
}
