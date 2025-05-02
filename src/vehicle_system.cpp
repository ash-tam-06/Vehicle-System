#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <fstream>
#include "../include/vehicle_system.h"
#include "../include/customer_system.h"
#include "../include/globals.h"


using namespace std;

void addVehicle(int reg, vehicleType type) {
    fleet[reg] = make_unique<vehicle>(vehicle{type, reg, true});
}

bool saveToFile() {
    fstream file;
    file.open("fleet.csv", ios::in | ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "Failed to open file " << endl;
        return false;
    }
    for (const auto& pair : fleet) {
        file << pair.first << "," << static_cast<int>(pair.second->type) << "," << pair.second->available << "\n";
    }
    file.close();

    ofstream fileBinary("customers.dat", ios::binary);
    if (!fileBinary.is_open()) {
        cout << "Failed to open customer file." << endl;
        return false;
    }
    for (const auto& pair : customers) {
        size_t nameLength = pair.first.size();
        fileBinary.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        fileBinary.write(pair.first.c_str(), nameLength);
        fileBinary.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }
    fileBinary.close();
    return true;
}

bool loadFromFile() {
    ifstream file("fleet.csv");
    int reg;
    int typeInt;
    bool available;
    char comma;
    file.open("fleet.csv", ios::in);
    if (!file.is_open()) {
        cout << "Failed to open file " << endl;
        return false;
    }
    while (file >> reg >> comma >> typeInt >> comma >> available) {
        addVehicle(reg, static_cast<vehicleType>(typeInt));
        fleet[reg]->available = available;
    }
    cout << "Fleet loaded from CSV.\n";
    file.close();

    fstream fileBinary("customers.dat", ios::in | ios::binary);
    if (!fileBinary.is_open()) {
        cout << "Failed to open customer file." << endl;
        return false;
    }
    while (fileBinary.peek() != EOF) {
        size_t nameLength;
        fileBinary.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        string name(nameLength, ' ');
        fileBinary.read(&name[0], nameLength);

        Customer customer;
        fileBinary.read(reinterpret_cast<char*>(&customer), sizeof(customer));
        customers[name] = customer;
    }
    fileBinary.close();
    return true;
}

vehicle validateVehicle() {
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
    vehicle vehicle{static_cast<vehicleType>(type), regNum};
    return vehicle;
}


void validateReturn() {
    while (true) {
        string name = validateCustomerName();
        if (!customerList.contains(name)) {
            cout << "Please enter a registered customer name.\n";
        } else {
            returnVehicle(name);
            break;
        }
    }
}

void validateRentVehicle() {
    string name = validateCustomerName();
    int regNum;
    while (!rentVehicle(name, regNum)) {
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
}

void menu() {
    int choice;
    cout << "Please choose an option:\n";
    cout << "1. Add vehicle\n";
    cout << "2. Rent vehicle\n";
    cout << "3. Return vehicle\n";
    cout << "4. Load fleet\n";
    cout << "5. Save fleet\n";
    cout << "9. Exit\n";
    cin >> choice;

    while (choice != 9) {
        if (choice == 1) {
            vehicle vehicle = validateVehicle();
            addVehicle(vehicle.regNumber, vehicle.type);
        }else if (choice == 2) {
            validateRentVehicle();
        }else if (choice == 3) {
            validateReturn();
        }else if (choice == 4) {
            loadFromFile();
        } else if (choice == 5) {
            saveToFile();
        }
        cout << "Please choose an option:\n";
        cin >> choice;
    }
}