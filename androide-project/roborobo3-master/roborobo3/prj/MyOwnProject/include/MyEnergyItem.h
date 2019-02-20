//
//  MyEnergyItem.hpp
//  roborobo3
//
//  Created by Nicolas Bredeche on 06/12/17.
//  Copyright © 2017 Nicolas Bredeche. All rights reserved.
//

#ifndef MyEnergyItem_hpp
#define MyEnergyItem_hpp

#include "World/EnergyItem.h"

class MyEnergyItem : public EnergyItem
{
private:
    
    double _offsetRegion;
    double _range;
    int activeIt;

public :
    
    MyEnergyItem( int __id );
    ~MyEnergyItem() { }
    
    void step() override;
    void isTouched( int __idAgent ) override; // callback, triggered by agent
    void isWalked( int __idAgent ) override; // callback, triggered by agent
    void isPushed( int __id, std::tuple<double, double> __speed ) override; // callback, triggered by collision w/ agent/object
    
    void setRegion( double offset, double range );
    void relocate() override;
    bool relocate(int ymin, int ymax) override;
    void test() ;
};

#endif /* MyEnergyItem_hpp */
