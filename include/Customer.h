//
// Created by Asmita Tamang on 5/20/25.
//

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Vehicle.h"

using namespace std;

class Customer {
private:
    string name;
    shared_ptr<Vehicle> rentedVehicle;

public:
    Customer(string name);

    Customer() : name(""), rentedVehicle(nullptr) {}

    string getName() const;

    void rentVehicle(shared_ptr<Vehicle> vehicle);

    void returnVehicle();

    bool hasVehicle() const;

    shared_ptr<Vehicle> getVehicle() const ;
};



#endif //CUSTOMER_H
