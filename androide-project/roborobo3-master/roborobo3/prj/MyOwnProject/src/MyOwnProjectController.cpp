/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "MyOwnProject/include/MyOwnProjectController.h"
#include "RoboroboMain/roborobo.h"
#include "WorldModels/RobotWorldModel.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // assume 12 sensors
#include "Utilities/Sensorbelt.h"

MyOwnProjectController::MyOwnProjectController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
    this->setObjCollected(false);
    this->setCanDropSlope(false);
    this->setCanInstantDrop(false);
    double genome[24]={0.5,1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,0,1,1,1,400,700,950,1000};
    for (int i = 0; i < 19 ; i++){
        genome[i] = random01()*2-1;
    }
    size_t nbParams = 14;
    _params.resize(nbParams,0); // initialize an array with zero values.
}

MyOwnProjectController::~MyOwnProjectController()
{
	// nothing to do.
}

void MyOwnProjectController::reset()
{
	// nothing to do.
}
/*Old Step
void MyOwnProjectController::step()
{


    Point2d p = getPosition(); 
    double normalT = sin( ( ( getDistanceAt(SENSOR_FFL) + getDistanceAt(SENSOR_FFR) ) / 2.0 )* M_PI / 2.0);
    if (normalT > 0.2)
        normalT -= 0.2;
    else if (normalT < -0.2)
        normalT += 0.2;
        
    double maxRampSpeed = 0.3;
    double minRampSpeed = -0.3;
    double orientation = getOrientation();

    if (p.y > 450&& p.y < 700 && orientation < 0.0){
        if(normalT > maxRampSpeed)
            setTranslation(maxRampSpeed);
        else if (normalT < minRampSpeed)
            setTranslation(minRampSpeed);
        else
            setTranslation(normalT);     
    }
    else if (p.y > 450 && p.y < 700 && orientation >= 0.0){
            if (normalT <= 0.9)
                normalT += 0.2;
            else if (normalT >= -0.9)
                normalT -= 0.2;
            setTranslation(normalT);     
    }
    else{
        setTranslation(normalT);
    }
    
    
    double dist_L = getDistanceAt(SENSOR_L);
    double dist_FL = getDistanceAt(SENSOR_FL);
    double dist_FFL = getDistanceAt(SENSOR_FFL);
    double dist_R = getDistanceAt(SENSOR_R);
    double dist_FR = getDistanceAt(SENSOR_FR);
    double dist_FFR = getDistanceAt(SENSOR_FFR);
    int objectId = -2;
    bool objDetected = false;


    
    objectId = _wm->getObjectIdFromCameraSensor(SENSOR_R);
    if ( PhysicalObject::isInstanceOf(objectId) ){

        if (gVerbose and 1 == gPhysicalObjects[objectId - gPhysicalObjectIndexStartOffset]->getType()){
            objDetected = true;
            std::cout << "TYPE 1 R\n";
            dist_R = 0;
        }
    }

    double distanceOnMyLeft = getDistanceAt(SENSOR_L) + getDistanceAt(SENSOR_FL) + getDistanceAt(SENSOR_FFL);
    double distanceOnMyRight = getDistanceAt(SENSOR_R) + getDistanceAt(SENSOR_FR) + getDistanceAt(SENSOR_FFR);
    
    
    double rotationDelta = 0.3;
    double noiseAmplitude = 0.01;
    if(!objDetected){
            
        if ( distanceOnMyLeft < distanceOnMyRight )
            setRotation( +rotationDelta );
        else if ( distanceOnMyRight < distanceOnMyLeft )
            setRotation( -rotationDelta );
        else
            //setRotation( 0.1 - (double)(random01()*0.2));
            setRotation( noiseAmplitude * ( 1.0 - (double)(random01()*2.0) ) );    
        
    }
    else{
        //setRotation()
    }
    
    //monitorSensoryInformation();
    //std::cout << inspect("TEST ");
    //std::cout << _wm->_actualTranslationalValue << "\n";
    //std::cout << _wm->_actualRotationalVelocity << "\n";
}*/

//AG step
void MyOwnProjectController::step(){
    std::cout << "\ntest\n";
    for(int i = 0; i < 24; i++){
        std::cout << genome[i]<<":";
    }
    double t = calculateTranslation();
    setTranslation(t);
    std::cout <<"\nTranslation : " << t<<"\n";
    //setTranslation(calculateTranslation());
    t = calculateRotation();
    setRotation(t);
    std::cout << "\nRotation :" << t<<"\n";
    std::cout << "\nDrop : "<<calculateDrop()<<"\n";
    std::cout << "\ntest4\n";
    /*for(int i = 0; i < 24; i++){
        std::cout << genomegggg[i]<<":";
    }*/
    std::cout << "\n";
    
}
//Fonctions de ramassage et dépôt d'objets
bool MyOwnProjectController::getCanCollect(){
    return this->canCollect;
}
bool MyOwnProjectController::getCanDropSlope(){
    return this->canDropSlope;
}
bool MyOwnProjectController::getCanDropNest(){
    return this->canDropNest;
}
bool MyOwnProjectController::getCanInstantDrop(){
    return this->instantDrop;
}
bool MyOwnProjectController::getObjCollected(){
    return this->objCollected;
}

void MyOwnProjectController::setCanCollect(bool c){
    this->canCollect = c;
}
void MyOwnProjectController::setCanDropSlope(bool c){
    this->canDropSlope = c;
}
void MyOwnProjectController::setCanDropNest(bool c){
    this->canDropNest = c;
}
void MyOwnProjectController::setCanInstantDrop(bool c){
    this->instantDrop = c;
}
void MyOwnProjectController::setObjCollected(bool c){
    this->objCollected = c;
    if(c == true){
        std::cout << "Can not collect anymore";
        this->setCanCollect(false);
        //this->setCanDropSlope(true);
        //this->setCanDropNest(true);
        //this->setCanInstantDrop(true);
    }
    else if(c == false){
        std::cout << "Can recollect";
        this->setCanCollect(true);
        //this->setCanDropSlope(false);
        //this->setCanDropNest(false);
        this->setCanInstantDrop(false);
    }
}

/*Algorithme génétique
Variables utilisées :
Senseur *7
Position*2
ObjetCollecté
Orientation

Genome:
sWX : senseur triggered wall 
sOX : senseur triggered object 
probDropSlope
probDropNest
obj 
ori
slopeMin
slopeMax
nestMin
nestMax
[translation bias, rotation bias,sW1,sW2,sW3,sW4,sW5,sW6,sW7,sO1,sO2,sO3,sO4,sO5,sO6,sO7,sbO,probDropSlope,probDropNest,obj,ori,slopeMin,slopeMax,nestMin,nestMax]
0                      1         2   3   4   5   6   7   8   9   10   11  12  13 14  15   16            17          18   19  20       21       22     23
*/
//Fonctions
void MyOwnProjectController::setGenome(double *g){
    for (int i = 0 ; i< 24 ; i++){
        genome[i]=g[i];
    }
}
double* MyOwnProjectController::getGenome(){
    return this->genome;
}

double MyOwnProjectController::calculateRotation(){
    //double genome[24]={-1,-1,-1,-1,-1,-1,-1,0.01,1,1,1,1,1,1,1,0.5,0,1,1,1,400,700,950,1000};
    double calcul = 0;
    calcul = calcul+genome[1];
    double dist_L = getDistanceAt(SENSOR_L);
    if(getObjectAt(SENSOR_L)==1){
        calcul = calcul+genome[2]*dist_L;
    }
    if(getWallAt(SENSOR_L)==1){
        calcul = calcul+genome[8+0]*dist_L;
    }
    double dist_FL = getDistanceAt(SENSOR_FL);
    if(getObjectAt(SENSOR_FL)==1){
        calcul = calcul+genome[3]*dist_FL;
    }
    if(getWallAt(SENSOR_FL)==1){
        calcul = calcul+genome[8+1]*dist_FL;
    }
    double dist_FFL = getDistanceAt(SENSOR_FFL);
    if(getObjectAt(SENSOR_FFL)==1){
        calcul = calcul+genome[4]*dist_FFL;
    }
    if(getWallAt(SENSOR_FFL)==1){
        calcul = calcul+genome[8+2]*dist_FFL;
    }
    double dist_R = getDistanceAt(SENSOR_R);
    if(getObjectAt(SENSOR_R)==1){
        calcul = calcul+genome[6]*dist_R;
    }
    if(getWallAt(SENSOR_R)==1){
        calcul = calcul+genome[8+4]*dist_R;
    }
    double dist_FR = getDistanceAt(SENSOR_FR);
    if(getObjectAt(SENSOR_FR)==1){
        calcul = calcul+genome[7]*dist_FR;
    }
    if(getWallAt(SENSOR_FR)==1){
        calcul = calcul+genome[8+5]*dist_FR;
    }
    double dist_FFR = getDistanceAt(SENSOR_FFR);
    if(getObjectAt(SENSOR_FFR)==1){
        calcul = calcul+genome[8]*dist_FFR;
    }
    if(getWallAt(SENSOR_FFR)==1){
        calcul = calcul+genome[8+6]*dist_FFR;
    }
    return calcul;
}

double MyOwnProjectController::calculateTranslation(){
    //double genome[24]={-1,-1,-1,-1,-1,-1,-1,0.01,1,1,1,1,1,1,1,0.5,0,1,1,1,400,700,950,1000};
    double calcul = 0;
    calcul = calcul + genome[0];
    double dist_F = getDistanceAt(SENSOR_F);
    if(getObjectAt(SENSOR_F)==1){
        calcul = calcul+genome[3]*dist_F;
    }
    if(getWallAt(SENSOR_F)==1){
        calcul = calcul+genome[8+3]*dist_F;
    }
    return calcul;
}
double MyOwnProjectController::calculateDrop(){
    double genome[24]={-1,-1,-1,-1,-1,-1,-1,0.01,1,1,1,1,1,1,1,0.5,0,1,1,1,400,700,950,1000};
    //Slope
    if(this->getPosition().y<genome[21] && this->getPosition().y>genome[20] && random01()<genome[16] && this->getObjCollected()==true){
        this->setCanInstantDrop(true);
        return 1;
    }
    //Nest
    if(this->getPosition().y<genome[23] && this->getPosition().y>genome[22] && random01()<genome[17] && this->getObjCollected()==true){
        this->setCanInstantDrop(true);
        return 1;
    }
    return 0;
}

/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/*                                                                                                     */
/*    Everything after this comment can be safely ignored (and removed).                               */
/*    The two following methods illustrates how to access all information available to the robot.      */
/*                                                                                                     */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */
/* **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** **** */


void MyOwnProjectController::monitorSensoryInformation()
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


std::string MyOwnProjectController::inspect( std::string prefix )
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
