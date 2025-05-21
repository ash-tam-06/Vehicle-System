#include "../include/Car.h"

Car::Car(int reg) : Vehicle(reg) {
  if (reg < 0) throw std::invalid_argument("Registration number cannot be negative.");
  std::cout << "Car made" << std::endl;
}

VehicleType Car::getType() const {
  return car;
}