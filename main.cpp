#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <fstream>
#include "include/vehicle_system.h"
#include "include/customer_system.h"

using namespace std;

//TODO: last two tests fail: fix that

int main(){
    unordered_map<int, unique_ptr<vehicle>> fleet;
    map<string, Customer> customerList;


    vehicle vehicle{car,  11, true};
    addVehicle(12, bike);
    addVehicle(13, car);

    addCustomer("Eli Smith");
    addCustomer("Adam Red");

    rentVehicle("Eli Smith", 12);
    rentVehicle("Adam Red", 10);
    rentVehicle("Adam Red", 13);
    returnVehicle("Eli Smith");
    returnVehicle("Adam Red");
    returnVehicle("Eli Smith");

    saveToFile();

    loadFromFile();

    menu();
    return 0;
}
