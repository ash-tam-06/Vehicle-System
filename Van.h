//
// Created by Asmita Tamang on 5/20/25.
//

#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"
#include <iostream>

class Van : public Vehicle {
public:
    Van(int reg);
    VehicleType getType() const override;
};



#endif //VAN_H
