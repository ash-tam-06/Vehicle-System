#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <fstream>
#include "../include/vehicle_system.h"
#include "../include/customer_system.h"
#include "../include/globals.h"

using namespace std;

void addCustomer(const string& name) {
    customers[name] = Customer{name,nullptr};
}

string validateCustomerName() {
    bool isValid=false;
    string name;
    while(!isValid){
        isValid = true;
        cout<< "Please customer name: " << endl;
        getline(cin, name);
        if(name.empty()){
            cout << "invalid input, please enter a non empty string\n" << endl;
            isValid = false;
        }
    }
    return name;
}


bool rentVehicle(const string& customerName, const int& regNum) {
    if (!fleet.contains(regNum) || !fleet[regNum]->available) {
        cout << "Vehicle unavailable." << endl;
        return false;
    }
    const auto sharedVehicle = shared_ptr<vehicle>(fleet[regNum].get(), [](vehicle*) {

    });
    fleet[regNum]->available = false;
    customers[customerName].rentedVehicle = sharedVehicle;
    cout << customerName << " rented: " << regNum << endl;
    return true;
}

bool returnVehicle(const string& customerName) {
    if (customers[customerName].rentedVehicle != nullptr) {
        customers[customerName].rentedVehicle->available = true;
        customers[customerName].rentedVehicle = nullptr;
        std::cout << customerName << " returned their vehicle.\n";
    } else {
        std::cout << "No vehicle to return.\n";
    }
    return true;
}
