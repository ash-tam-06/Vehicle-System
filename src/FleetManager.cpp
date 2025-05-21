//
// Created by Asmita Tamang on 5/20/25.
//

#include "../include/FleetManager.h"
#include "../include/Customer.h"
#include "../include/Vehicle.h"
#include "../include/Bike.h"
#include "../include/Car.h"
#include "../include/Van.h"
#include "fstream"

using namespace std;

void FleetManager::addVehicle() {
    int regNum;
    int type;
    while (true) {
        cout << "Enter vehicle registration number: " << endl;
        cin >> regNum;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<< "invalid input. please enter a valid registration number.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(),'\n');
            break;
        }
    }
    while (true) {
        cout << "Enter vehicle type: " << endl;
        cin >> type;
        if(cin.fail() || (type < 0 || type > 2)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<< "invalid input. please enter a valid vehicle type.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(),'\n');
            break;
        }
    }

    if (type == 0) {
        fleet[regNum] = make_unique<Bike>(bike);
    } else if (type == 1) {
        fleet[regNum] = make_unique<Car>(car);
    } else if (type == 2) {
        fleet[regNum] = make_unique<Van>(van);
    }
}

void FleetManager::addCustomer(const string& name) {
    customers[name] = Customer(name);
}

bool FleetManager::rentVehicle() {
    bool isValid=false;
    string name;
    while(!isValid) {
        isValid = true;
        cout<< "Please customer name: " << endl;
        getline(cin, name);
        if(name.empty()){
            cout << "invalid input, please enter a non empty string\n" << endl;
            isValid = false;
        }
    }
    int regNum;
    while (true) {
        cout << "Enter vehicle registration number: " << endl;
        cin >> regNum;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<< "invalid input. please enter a valid registration number.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(),'\n');
            break;
        }
    }
    if (!fleet.contains(regNum) || !fleet[regNum]->available) {
        cout << "Vehicle unavailable." << endl;
        return false;
    }
    const auto sharedVehicle = shared_ptr<Vehicle>(fleet[regNum].get(), [](Vehicle*) {

    });
    fleet[regNum]->available = false;
    customers[name].rentedVehicle = sharedVehicle;
    cout << name << " rented: " << regNum << endl;
    return true;
}

bool FleetManager::returnVehicle(const string& name) {
    if (!customers[name].hasVehicle()) {
        cout << "No vehicle to return.\n";
        return false;
    }
    customers[name].returnVehicle();
    cout << name << " returned their vehicle.\n";
    return true;
}

void FleetManager::saveToFile() {
    ofstream fleetFile("fleet.csv", ios::trunc);
    for (const auto& [reg, vehicle] : fleet) {
        fleetFile << reg << "," << static_cast<int>(vehicle->getType()) << "," << vehicle->isAvailable() << "\n";
    }
    fleetFile.close();

    ofstream customerFile("customers.dat", ios::binary);
    for (const auto& [name, customer] : customers) {
        size_t len = name.size();
        customerFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
        customerFile.write(name.c_str(), len);

        bool has = customer.hasVehicle();
        customerFile.write(reinterpret_cast<const char*>(&has), sizeof(has));
        if (has) {
            int reg = customer.getVehicle()->getRegNumber();
            customerFile.write(reinterpret_cast<const char*>(&reg), sizeof(reg));
        }
    }
    customerFile.close();
}

void FleetManager::loadFromFile() {
    ifstream fleetFile("fleet.csv");
    int reg, typeInt;
    bool available;
    char comma;

    while (fleetFile >> reg >> comma >> typeInt >> comma >> available) {
        addVehicle(reg, static_cast<VehicleType>(typeInt));
        fleet[reg]->setAvailable(available);
    }
    fleetFile.close();

    ifstream customerFile("customers.dat", ios::binary);
    while (customerFile.peek() != EOF) {
        size_t len;
        customerFile.read(reinterpret_cast<char*>(&len), sizeof(len));
        string name(len, ' ');
        customerFile.read(&name[0], len);

        bool has;
        customerFile.read(reinterpret_cast<char*>(&has), sizeof(has));

        addCustomer(name);
        if (has) {
            int reg;
            customerFile.read(reinterpret_cast<char*>(&reg), sizeof(reg));
            if (fleet.contains(reg))
                customers[name].rentVehicle(fleet[reg]);
        }
    }
    customerFile.close();

    cout << "Data loaded.\n";
}

void FleetManager::menu() {

    int choice;
    while (true) {
        cout << "1. Add Vehicle\n2. Rent Vehicle\n3. Return Vehicle\n4. Load\n5. Save\n9. Exit\n";
        cin >> choice;
        cin.ignore();

        if (choice == 9) break;
        else if (choice == 1) {
            int reg, type;
            cout << "Enter registration number: ";
            cin >> reg;
            cout << "Enter type (0: Car, 1: Van, 2: Truck): ";
            cin >> type;
            addVehicle(reg, static_cast<VehicleType>(type));
        } else if (choice == 2) {
            string name;
            int reg;
            cin.ignore();
            cout << "Enter customer name: ";
            getline(cin, name);
            if (!customers.contains(name)) addCustomer(name);
            cout << "Enter vehicle registration: ";
            cin >> reg;
            rentVehicle(name, reg);
        } else if (choice == 3) {
            string name;
            cin.ignore();
            cout << "Enter customer name: ";
            getline(cin, name);
            returnVehicle(name);
        } else if (choice == 4) {
            loadFromFile();
        } else if (choice == 5) {
            saveToFile();
        }
    }
}
