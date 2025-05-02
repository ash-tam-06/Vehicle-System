# pragma once
#include <unordered_map>
#include <map>
#include <memory>
#include "vehicle_system.h"
#include "customer_system.h"

extern std::unordered_map<int, std::unique_ptr<vehicle>> fleet;
extern std::map<std::string, Customer> customers;
