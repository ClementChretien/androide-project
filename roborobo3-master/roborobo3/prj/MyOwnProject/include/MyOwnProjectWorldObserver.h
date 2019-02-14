/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef MYOWNPROJECTWORLDOBSERVER_H
#define MYOWNPROJECTWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class MyOwnProjectWorldObserver : public WorldObserver
{
	protected:
		
	public:
		MyOwnProjectWorldObserver( World *__world );
		~MyOwnProjectWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif

