#ifndef BIKE_H
#define BIKE_H

#include "Vehicle.h"
#include <iostream>


class Bike : public Vehicle {
public:
    Bike(int reg);
    VehicleType getType() const override;
};



#endif
