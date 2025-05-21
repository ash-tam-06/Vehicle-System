#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <fstream>

#include "include/Vehicle.h"
#include "include/Car.h"
#include "include/Van.h"
#include "include/Bike.h"
#include "include/Customer.h"
#include "include/FleetManager.h"

using namespace std;

int main(){
    FleetManager manager;
    manager.menu();
    return 0;
}
