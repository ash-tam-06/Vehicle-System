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
    unordered_map<int, shared_ptr<Vehicle>> fleet;
    map<string, Customer> customers;

public:
    void addVehicle();
    void addCustomer(const string& name);
    bool rentVehicle();
    bool returnVehicle(const string& name);
    void saveToFile();
    void loadFromFile();
    void menu();
};



#endif
