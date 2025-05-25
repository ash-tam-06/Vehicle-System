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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< "Invalid input. Please enter a valid registration number.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(), '\n');
            break;
        }
    }
    while (true) {
        cout << "Enter vehicle type (0: Bike, 1: Car, 2: Van): " << endl;
        cin >> type;
        if(cin.fail() || (type < 0 || type > 2)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< "Invalid input. Please enter a valid vehicle type.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(), '\n');
            break;
        }
    }

    if (type == 0) {
        fleet[regNum] = make_shared<Bike>(regNum);
    } else if (type == 1) {
        fleet[regNum] = make_shared<Car>(regNum);
    } else if (type == 2) {
        fleet[regNum] = make_shared<Van>(regNum);
    } else {
        throw invalid_argument("Invalid vehicle type entered.");
    }
}

void FleetManager::addCustomer(const string& name) {
    customers[name] = Customer(name);
}

bool FleetManager::rentVehicle() {
    bool isValid = false;
    string name;
    while(!isValid) {
        isValid = true;
        cout<< "Please customer name: " << endl;
        getline(cin, name);
        if(name.empty() || name == " "){
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< "Invalid input. Please enter a valid registration number.\n";
        }else{
            cin.ignore(numeric_limits<streamsize>:: max(), '\n');
            break;
        }
    }
    if (!fleet.contains(regNum)) {
        throw out_of_range("Vehicle with given registration number does not exist.");
    }
    customers[name].rentVehicle(fleet[regNum]);
    cout << name << " rented: " << regNum << endl;
    return true;
}

bool FleetManager::returnVehicle(const string& name) {
    if (!customers.contains(name)) {
        throw invalid_argument("Customer does not exist.");
    }
    customers[name].returnVehicle();
    cout << name << " returned their vehicle.\n";
    return true;
}

void FleetManager::saveToFile() {
    ofstream fleetFile("fleet.csv", ios::trunc);
    if (!fleetFile.is_open()) throw runtime_error("Unable to open fleet.csv");

    for (const auto& [reg, vehicle] : fleet) {
        fleetFile << reg << "," << static_cast<int>(vehicle->getType()) << "," << vehicle->isAvailable() << "\n";
    }
    fleetFile.close();

    ofstream customerFile("customers.dat", ios::binary);
    if (!customerFile.is_open()) throw runtime_error("Unable to open customers.dat");

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
    if (!fleetFile.is_open()) throw runtime_error("Unable to open fleet.csv");

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

        if (typeInt == 0) fleet[reg] = make_shared<Bike>(reg);
        else if (typeInt == 1) fleet[reg] = make_shared<Car>(reg);
        else if (typeInt == 2) fleet[reg] = make_shared<Van>(reg);

        fleet[reg]->setAvailable(available);
    }
    fleetFile.close();

    ifstream customerFile("customers.dat", ios::binary);
    if (!customerFile.is_open()) throw runtime_error("Unable to open customers.dat");

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
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        try {
            if (choice == 9) break;
            else if (choice == 1) {
                addVehicle();
            } else if (choice == 2) {
                rentVehicle();
            } else if (choice == 3) {
                string name;
                cout << "Enter customer name: ";
                getline(cin, name);
                returnVehicle(name);
            } else if (choice == 4) {
                loadFromFile();
            } else if (choice == 5) {
                saveToFile();
            } else {
                cout << "Invalid option. Try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
    }
}
