#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <iostream>


class Car : public Vehicle {
public:
    Car(int reg);
    VehicleType getType() const override;
};



#endif
