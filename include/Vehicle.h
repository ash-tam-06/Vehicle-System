//
// Created by Asmita Tamang on 5/20/25.
//

#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>


//enum
enum VehicleType {bike, car, van };

//base class
class Vehicle {
public:
    int regNumber;
    bool available;

    Vehicle(int reg);
    virtual ~Vehicle() = default;

    int getRegNumber() const;
    bool isAvailable() const;
    void setAvailable(bool available);

    virtual VehicleType getType() const = 0;
};



#endif //VEHICLE_H
