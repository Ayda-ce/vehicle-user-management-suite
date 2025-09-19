#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#include <iostream>
#include <string>

using namespace std;

// Class representing a vehicle
class Vehicle 
{
public:
    string vehicleCode;   // Unique code for the vehicle
    string brand;         // Brand of the vehicle
    string model;         // Model of the vehicle
    int passengerCapacity; // Passenger capacity of the vehicle

    // Default constructor
    Vehicle() : passengerCapacity(0) {}

    // Parameterized constructor
    Vehicle(const string& code, const string& brand, const string& model, int capacity)
        : vehicleCode(code), brand(brand), model(model), passengerCapacity(capacity) {}

    // Overload << operator to display vehicle information
    friend ostream& operator<<(ostream& os, const Vehicle& vehicle) 
    {
        os << "Vehicle Code: " << vehicle.vehicleCode << "\n";
        os << "Brand: " << vehicle.brand << "\n";
        os << "Model: " << vehicle.model << "\n";
        os << "Passenger Capacity: " << vehicle.passengerCapacity << "\n";
        return os;
    }
};

#endif /* _VEHICLE_H_ */