//
// Created by Asmita Tamang on 5/20/25.
//

#include "../include/Car.h"

Car::Car(int reg) : Vehicle(reg) {
  std::cout << "Car made" << std::endl;
}

VehicleType Car::getType() const {
  return car;
}