#include "../include/globals.h"
#include <unordered_map>
#include <map>
#include <memory>
#include "../include/vehicle_system.h"
#include "../include/customer_system.h"

std::unordered_map<int, std::unique_ptr<vehicle>> fleet;
std::map<std::string, Customer> customers;