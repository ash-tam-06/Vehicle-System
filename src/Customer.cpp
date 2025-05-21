//
// Created by Asmita Tamang on 5/20/25.
//

#include <utility>

#include "../include/Customer.h"
#include <iostream>

using namespace std;

Customer::Customer(string name) : name(move(name)), rentedVehicle(nullptr) {
    cout << "Customer created" << endl;
}

string Customer::getName() const {
    return name;
}

void Customer::rentVehicle(shared_ptr<Vehicle> vehicle) {
    rentedVehicle = vehicle;
    rentedVehicle->setAvailable(false);
}

void Customer::returnVehicle() {
    if (rentedVehicle) {
        rentedVehicle->setAvailable(true);
        rentedVehicle = nullptr;
    }
}

bool Customer::hasVehicle() const {
    return rentedVehicle != nullptr;
}

shared_ptr<Vehicle> Customer::getVehicle() const {
    return rentedVehicle;
}