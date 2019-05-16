//
//  RSVEvalMyEnergyItem.hpp
//  roborobo3
//
//  Created by Nicolas Bredeche on 06/12/17.
//  Copyright © 2017 Nicolas Bredeche. All rights reserved.
//

#ifndef RSVEvalMyEnergyItem_hppp
#define RSVEvalMyEnergyItem_hppp

#include "World/EnergyItem.h"

class RSVEvalMyEnergyItem : public EnergyItem
{
private:
    
    double _offsetRegion;
    double _range;
    int activeIt;

public :
    
    RSVEvalMyEnergyItem( int __id );
    ~RSVEvalMyEnergyItem() { }
    
    void step() override;
    void isTouched( int __idAgent ) override; // callback, triggered by agent
    void isWalked( int __idAgent ) override; // callback, triggered by agent
    void isPushed( int __id, std::tuple<double, double> __speed ) override; // callback, triggered by collision w/ agent/object
    
    void setRegion( double offset, double range );
    void relocate() override;
    bool relocate(double ymin, double ymax, bool ecart);
    bool relocate(double ymin, double ymax, bool ecart, double range, double offset);
    bool relocate(double xmin, double xmax,double ymin, double ymax);
    void test() ;
};

#endif /* RSVEvalMyEnergyItem_hpp */
