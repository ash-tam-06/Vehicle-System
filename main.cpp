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

using namespace std;

int main(){
    Car car{12};
    Van van{12};
    Bike bike{12};
    Customer customer{"Bob"};

    return 0;
}
