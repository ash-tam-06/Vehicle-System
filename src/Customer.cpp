#include <utility>

#include "../include/Customer.h"
#include <iostream>

using namespace std;

Customer::Customer(string name) : name(move(name)), rentedVehicle(nullptr) {
    if (this->name.empty()) throw invalid_argument("Customer name cannot be empty.");
    cout << "Customer created" << endl;
}

string Customer::getName() const {
    return name;
}

void Customer::rentVehicle(shared_ptr<Vehicle> vehicle) {
    if (!vehicle) {
        throw invalid_argument("Vehicle pointer is null.");
    }
    if (!vehicle->isAvailable()) {
        throw runtime_error("Vehicle is already rented.");
    }
    rentedVehicle = vehicle;
    rentedVehicle->setAvailable(false);
}

void Customer::returnVehicle() {
    if (!rentedVehicle) {
        throw logic_error("No vehicle to return.");
    }
    rentedVehicle->setAvailable(true);
    rentedVehicle = nullptr;
}

bool Customer::hasVehicle() const {
    return rentedVehicle != nullptr;
}

shared_ptr<Vehicle> Customer::getVehicle() const {
    return rentedVehicle;
}