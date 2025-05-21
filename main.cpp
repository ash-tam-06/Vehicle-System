#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <fstream>

#include "include/vehicle_system.h"
// #include "include/vehicle_system.h"
// #include "include/customer_system.h"

using namespace std;

enum class VehicleType { Car, Van, Truck };

//base class
class Vehicle {
public:
    int regNumber;
    bool available;

    Vehicle(int reg): regNumber{reg}, available{true}{}
    virtual ~Vehicle() = default;

    int getRegNumber() const {
        return regNumber;
    }
    bool isAvailable() const {
        return available;
    }
    void setAvailable(bool status) {
        available = status;
    }

    virtual VehicleType getType() const = 0;
};

// Derived classes
class Car : public Vehicle {
public:
    Car(int reg) : Vehicle(reg) {}
    VehicleType getType() const override { return VehicleType::Car; }
};

class Van : public Vehicle {
public:
    Van(int reg) : Vehicle(reg) {}
    VehicleType getType() const override { return VehicleType::Van; }
};

class Truck : public Vehicle {
public:
    Truck(int reg) : Vehicle(reg) {}
    VehicleType getType() const override { return VehicleType::Truck; }
};


int main(){
    //User interface: gives options for user on what they could do
    // menu();
    // return 0;

}
