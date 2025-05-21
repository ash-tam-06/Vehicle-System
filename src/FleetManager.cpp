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
#include "sstream"

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
            cout<< "Invalid input. Please enter a valid registration number.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(),'\n');
            break;
        }
    }
    while (true) {
        cout << "Enter vehicle type (0: Bike, 1: Car, 2: Van): " << endl;
        cin >> type;
        if(cin.fail() || (type < 0 || type > 2)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<< "Invalid input. Please enter a valid vehicle type.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(),'\n');
            break;
        }
    }

    if (type == 0) {
        fleet[regNum] = make_unique<Bike>(regNum);
    } else if (type == 1) {
        fleet[regNum] = make_unique<Car>(regNum);
    } else if (type == 2) {
        fleet[regNum] = make_unique<Van>(regNum);
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
            cout << "Invalid input. Please enter a non-empty string.\n" << endl;
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
            cout<< "Invalid input. Please enter a valid registration number.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(),'\n');
            break;
        }
    }
    if (!fleet.contains(regNum) || !fleet[regNum]->available) {
        cout << "Vehicle unavailable." << endl;
        return false;
    }
    const auto sharedVehicle = shared_ptr<Vehicle>(fleet[regNum].get(), [](Vehicle*) {});
    fleet[regNum]->available = false;
    if (customers.find(name) == customers.end()) {
        cout << "Customer does not exist. Adding customer: " << name << endl;
        addCustomer(name);
    }
    customers[name].rentVehicle(sharedVehicle);
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
    string line;
    while (getline(fleetFile, line)) {
        istringstream iss(line);
        string regStr, typeStr, availStr;
        getline(iss, regStr, ',');
        getline(iss, typeStr, ',');
        getline(iss, availStr);

        int reg = stoi(regStr);
        int typeInt = stoi(typeStr);
        bool available = stoi(availStr);

        if (typeInt == 0) fleet[reg] = make_unique<Bike>(reg);
        else if (typeInt == 1) fleet[reg] = make_unique<Car>(reg);
        else if (typeInt == 2) fleet[reg] = make_unique<Van>(reg);

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
                customers[name].rentVehicle(shared_ptr<Vehicle>(fleet[reg].get(), [](Vehicle*) {}));
        }
    }
    customerFile.close();

    cout << "Data loaded.\n";
}

void FleetManager::menu() {
    int choice;
    while (true) {
        cout << "1. Add Vehicle\n2. Rent Vehicle\n3. Return Vehicle\n4. Save Data\n5. Load Data\n9. Exit\n";
        cin >> choice;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid choice. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        if (choice == 9) break;
        if (choice == 1) {
            addVehicle();
        } else if (choice == 2) {
            rentVehicle();
        } else if (choice == 3) {
            string name;
            cout << "Enter customer name: ";
            getline(cin, name);
            returnVehicle(name);
        } else if (choice == 4) {
            saveToFile();
        } else if (choice == 5) {
            loadFromFile();
        } else {
            cout << "Invalid option. Try again.\n";
        }
    }
}
