//
//  EvalMyEnergyItem.cpp
//  roborobo3
//
//  Created by Nicolas Bredeche on 06/12/17.
//  Copyright © 2017 Nicolas Bredeche. All rights reserved.
//

#include "EvaluationPopulations/include/EvalMyEnergyItem.h"
#include "EvaluationPopulations/include/EvaluationPopulationsController.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"
#include "WorldModels/RobotWorldModel.h"
#include "Utilities/Misc.h"


EvalMyEnergyItem::EvalMyEnergyItem( int __id ) : EnergyItem( __id )
{
    
}

void EvalMyEnergyItem::step()
{
    EnergyItem::step();
 
    if ( activeIt == 1000 * 2 ) // relocate after xxx iterations (if not harvested inbetween)
    {
        relocate(); // incl. activeIt=0
        _visible = true;
    }
}

void EvalMyEnergyItem::isTouched( int __idAgent )
{
    //EnergyItem::isTouched(__idAgent);
    EvaluationPopulationsController *c = dynamic_cast<EvaluationPopulationsController*>(gWorld->getRobot(__idAgent)->getController());
    if(c->getCanCollect() == true){
        c->setObjCollected(true);
        //std::cout << "Collected\n";
        this->setRegion(0.0,0.2);
        this->relocate();
        this->unregisterObject();
    }
    else{
        //std::cout << "Not Collected";
    }
    //std::cout << (c->getCanCollect());
}

void EvalMyEnergyItem::isWalked( int __idAgent )
{
    /*//EnergyItem::isWalked(__idAgent);
    EvaluationPopulationsController *c = dynamic_cast<EvaluationPopulationsController*>(gWorld->getRobot(__idAgent)->getController());
    //std::cout << (c->getCanCollect());
    if(c->getCanCollect() == true){
        c->setObjCollected(true);
        std::cout << "Collected";
        this->unregisterObject();
    }
    else{
       // std::cout << "Not Collected";
        _visible = true;
    }*/
}

void EvalMyEnergyItem::isPushed( int __id, std::tuple<double, double> __speed )
{
    //EnergyItem::isPushed(__id,__speed);
}

void EvalMyEnergyItem::setRegion( double offset, double range )
{
    this->_offsetRegion = offset;
    this->_range = range;
}

void EvalMyEnergyItem::relocate()
{
    // * pick new coordinate
    
    unregisterObject();
    
    int border = 40;
    
    //double pi = atan(1)*4;
    
    do{
        
        double xPos;
        
        xPos = random01() * this->_range + this->_offsetRegion;
        
        // with a sigmoid
        //double value = random01();
        //xPos = (1/(1 + std::exp(-value*5 + 13)))*3000; // (1/(1 + Exp[-x*5 + 13])*3000) <===
        //xPos = std::pow(value,3); // x^3   <==
        //xPos = (1/(1 + std::exp(-value*5 + 5)))*2; // (1/(1 + Exp[-x*5 + 5]))
        //xPos = 1 - ( 1 / (1 + std::exp( -value * 10 + 5))); // 1 - (1/(1 + Exp[-x*10 + 5]))
        
        // with a gaussian
        //double sigma = 0.2;
        //double gaussianPeakValue = 1.0 / std::sqrt( 2. * pi * std::pow(sigma,2) );
        //xPos = sigma*randgaussian() / gaussianPeakValue;
        
        double x = random01() * ( gScreenWidth - 2*border ) + border;
        double y = xPos * ( gScreenHeight - 2*border ) + border;
        setCoordinates(x,y);
        if(y>500){
            std::cout <<"Pb";
        }
        
    } while ( canRegister() == false );
    
    registerObject();
    
    activeIt=0;
}
bool EvalMyEnergyItem::relocate(double ymin, double ymax,bool ecart)
{
    // * pick new coordinate
    
    unregisterObject();
    
    int border = 40;
    
    //double pi = atan(1)*4;
    if(!ecart){
        setCoordinates(ymin,ymax);
    }
    if(ecart || canRegister()== false){
        
        do{
            
            double yPos;
            
            yPos = random01() * (ymax-ymin) + ymin;
            
            // with a sigmoid
            //double value = random01();
            //xPos = (1/(1 + std::exp(-value*5 + 13)))*3000; // (1/(1 + Exp[-x*5 + 13])*3000) <===
            //xPos = std::pow(value,3); // x^3   <==
            //xPos = (1/(1 + std::exp(-value*5 + 5)))*2; // (1/(1 + Exp[-x*5 + 5]))
            //xPos = 1 - ( 1 / (1 + std::exp( -value * 10 + 5))); // 1 - (1/(1 + Exp[-x*10 + 5]))
            
            // with a gaussian
            //double sigma = 0.2;
            //double gaussianPeakValue = 1.0 / std::sqrt( 2. * pi * std::pow(sigma,2) );
            //xPos = sigma*randgaussian() / gaussianPeakValue;
            
            double x = random01() * ( gScreenWidth - 2*border );
            double y = yPos;// * ( gScreenHeight - 2*border ) + border;
            
            setCoordinates(x,y);
            
        } while ( canRegister() == false );
    }
    
    registerObject();
    
    activeIt=0;
}
bool EvalMyEnergyItem::relocate(double ymin, double ymax,bool ecart,double offset, double range )
{
    // * pick new coordinate
    
    unregisterObject();
    
    int border = 40;
    double x,y;
    double xPos;
    //double pi = atan(1)*4;
    if(!ecart){
        setCoordinates(ymin,ymax);
    }
    if(ecart || canRegister()== false){
        do{
            
            
            xPos = random01() * range + offset;
            
            // with a sigmoid
            //double value = random01();
            //xPos = (1/(1 + std::exp(-value*5 + 13)))*3000; // (1/(1 + Exp[-x*5 + 13])*3000) <===
            //xPos = std::pow(value,3); // x^3   <==
            //xPos = (1/(1 + std::exp(-value*5 + 5)))*2; // (1/(1 + Exp[-x*5 + 5]))
            //xPos = 1 - ( 1 / (1 + std::exp( -value * 10 + 5))); // 1 - (1/(1 + Exp[-x*10 + 5]))
            
            // with a gaussian
            //double sigma = 0.2;
            //double gaussianPeakValue = 1.0 / std::sqrt( 2. * pi * std::pow(sigma,2) );
            //xPos = sigma*randgaussian() / gaussianPeakValue;
            
            x = random01() * ( gScreenWidth - 2*border ) + border;
            y = xPos * ( gScreenHeight - 2*border ) + border;
            
            setCoordinates(x,y);
                
        } while ( canRegister() == false );
    }
    
    registerObject();
    
    activeIt=0;
}
bool EvalMyEnergyItem::relocate(double xmin, double xmax, double ymin, double ymax)
{
    // * pick new coordinate
    
    unregisterObject();
    
    int border = 40;
    
    //double pi = atan(1)*4;
    
    do{
        
        double xPos;
        
        xPos = random01() * (xmax-xmin) + xmin;

        double yPos;
        
        yPos = random01() * (ymax-ymin) + ymin;
        
        // with a sigmoid
        //double value = random01();
        //xPos = (1/(1 + std::exp(-value*5 + 13)))*3000; // (1/(1 + Exp[-x*5 + 13])*3000) <===
        //xPos = std::pow(value,3); // x^3   <==
        //xPos = (1/(1 + std::exp(-value*5 + 5)))*2; // (1/(1 + Exp[-x*5 + 5]))
        //xPos = 1 - ( 1 / (1 + std::exp( -value * 10 + 5))); // 1 - (1/(1 + Exp[-x*10 + 5]))
        
        // with a gaussian
        //double sigma = 0.2;
        //double gaussianPeakValue = 1.0 / std::sqrt( 2. * pi * std::pow(sigma,2) );
        //xPos = sigma*randgaussian() / gaussianPeakValue;
        
        double x = xPos;
        double y = yPos;// * ( gScreenHeight - 2*border ) + border;
        
        setCoordinates(x,y);
        
    } while ( canRegister() == false );
    
    registerObject();
    
    activeIt=0;
}