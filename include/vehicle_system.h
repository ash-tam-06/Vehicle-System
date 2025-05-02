# pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>

using namespace std;

enum vehicleType {bike, car, van};
struct vehicle {
    vehicleType type;
    int regNumber;
    bool available;

    void printInfo() const {
        cout << "Registration Number: "<< regNumber << endl;
        cout << "Vehicle type: " <<(type == bike ? "Bike" : type == car ? "Car" : "Van") << endl;
        cout << "Available: " << (available == true ? "Available" : "Rented" ) << endl;
    }
};


void addVehicle(int reg, vehicleType type);

bool saveToFile();

bool loadFromFile();

vehicle validateVehicle();

void validateReturn();

void validateRentVehicle();

void menu();