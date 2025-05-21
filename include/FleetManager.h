//
// Created by Asmita Tamang on 5/20/25.
//

#ifndef FLEETMANAGER_H
#define FLEETMANAGER_H
#include <iostream>
#include <unordered_map>
#include <map>
#include "Vehicle.h"
#include "Customer.h"

using namespace std;

class FleetManager {
private:
    unordered_map<int, std::unique_ptr<Vehicle>> fleet;
    map<std::string, Customer> customers;


//    shared_ptr<Vehicle> createVehicle(VehicleType type, int reg) {
//        switch (type) {
//            case VehicleType::car: return shared_ptr<car>(reg);
//            case VehicleType::van: return make_shared<van>(reg);
//            case VehicleType::bike: return make_shared<bike>(reg);
//        }
//        return nullptr;
//    }

public:
    void addVehicle();

    void addCustomer(const string& name);

    bool rentVehicle();

    bool returnVehicle(const string& name);

    void saveToFile();

    void loadFromFile();

    void menu();
};



#endif //FLEETMANAGER_H
