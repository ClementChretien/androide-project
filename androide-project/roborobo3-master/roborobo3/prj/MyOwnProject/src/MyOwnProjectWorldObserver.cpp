/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "MyOwnProject/include/MyOwnProjectWorldObserver.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include "MyOwnProject/include/MyOwnProjectController.h"
#include "RoboroboMain/roborobo.h"


MyOwnProjectWorldObserver::MyOwnProjectWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

MyOwnProjectWorldObserver::~MyOwnProjectWorldObserver()
{
	// nothing to do.
}

void MyOwnProjectWorldObserver::initPre()
{
    // nothing to do.
}

void MyOwnProjectWorldObserver::initPost()
{
    // nothing to do.
}

void MyOwnProjectWorldObserver::stepPre()
{
    
    // The following code shows an example where every 100 iterations, robots are re-located to their initial positions, and parameters are randomly changed.
    //
    // REMOVE OR COMMENT THE FOLLOWING TO AVOID RESETTING POSITIONS EVERY 100 ITERATIONS
    //
    
    /*if ( gWorld->getIterations() % 100 == 0 )
    {
        if ( gVerbose && gDisplayMode == 0 )
            std::cout << "Randomizing parameters\n";

        for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
        {
            Robot *robot = (gWorld->getRobot(i));
            
            (*robot).setCoordReal( 100 + (i*50)%800 , 100 + ( i*50/800 * 50 )  );
            
            MyOwnProjectController *controller = ((MyOwnProjectController*)(gWorld->getRobot(i)->getController()));
            
            for ( size_t j = 0 ; j != (*controller)._params.size() ; j++ )
            {
                (*controller)._params[(int)j] = random01()*2.0-1.0;
            }
        }
    }*/
    
}

void MyOwnProjectWorldObserver::stepPost()
{
    // nothing to do.
}
