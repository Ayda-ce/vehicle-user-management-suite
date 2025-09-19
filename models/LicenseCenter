#ifndef _LICENSECENTER_H_
#define _LICENSECENTER_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "../models/User.h"
#include "../models/Vehicle.h"
#include "../utils/fileprovider.h"
#include "../utils/buffer.h"

using namespace std;

class LicenseCenter 
{
public:
    vector<User> users;       // List of users
    User manager;             // The manager of the license center
    vector<Vehicle> vehicles; // List of vehicles

    // Get a user by their national ID
    User* getUserByID(const string& userId) 
    {
        for (auto& user : users) 
        {
            if (user.nationalCode == userId) 
            {
                return &user;
            }
        }
        if (manager.nationalCode == userId) 
        {
            return &manager;
        }
        return nullptr;
    }

    // Add a new user via user input
    void addUser() 
    {
        string name, password, nationalCode;

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "Enter National Code: ";
        getline(cin, nationalCode);

        User newUser(name, nationalCode, password);
        users.push_back(newUser);

        cout << "User added successfully!" << endl;
    }

    // Add a new vehicle via user input
    void addVehicle() 
    {
        string vehicleCode, brand, model;
        int passengerCapacity;

        cout << "Enter Vehicle Code: ";
        getline(cin, vehicleCode);

        cout << "Enter Brand: ";
        getline(cin, brand);

        cout << "Enter Model: ";
        getline(cin, model);

        cout << "Enter Passenger Capacity: ";
        cin >> passengerCapacity;
        cin.ignore(); // Clear newline character

        Vehicle newVehicle{vehicleCode, brand, model, passengerCapacity};
        vehicles.push_back(newVehicle);

        cout << "Vehicle added successfully!" << endl;
    }

    // Assign a vehicle to a user
    void assignVehicleToUser() 
    {
        string userId, vehicleCode;
        cout << "Enter User ID: ";
        getline(cin, userId);

        User* user = getUserByID(userId);
        if (user == nullptr) 
        {
            cout << "User not found!" << endl;
            return;
        }

        cout << "Enter Vehicle Code: ";
        getline(cin, vehicleCode);

        auto it = find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& v) { return v.vehicleCode == vehicleCode; });
        if (it == vehicles.end()) 
        {
            cout << "Vehicle not found!" << endl;
            return;
        }

        user->assignedVehicles.push_back(*it);
        cout << "Vehicle assigned to user successfully!" << endl;
    }

    // Overload << operator for LicenseCenter
    friend ostream& operator<<(ostream& os, const LicenseCenter& center) 
    {
        os << "\n******************************\n";
        os << "| License Center Statistics: |\n";
        os << "******************************\n";
        os << "Total Users: " << center.users.size() << "\n";
        os << "Total Vehicles: " << center.vehicles.size() << "\n";

        os << "\n******************************\n";
        os << "Manager:\n";
        os << "Name: " << center.manager.name << "\n";
        os << "National Code: " << center.manager.nationalCode << "\n";
        os << "Password: " << center.manager.password << "\n";
        os << "Assigned Vehicles:\n";

        if (!center.manager.assignedVehicles.empty()) 
        {
            for (const auto& vehicle : center.manager.assignedVehicles) 
            {
                os << "- " << vehicle << "\n";
            }
        } 
        else 
        {
            os << "None\n";
        }

        os << "\n******************************\n";
        os << "Users:\n";
        os << "__________\n";
        for (size_t i = 0; i < center.users.size(); ++i) 
        {
            os << "Id: " << i << "\n";
            os << "Name: " << center.users[i].name << "\n";
            os << "National Code: " << center.users[i].nationalCode << "\n";
            os << "Password: " << center.users[i].password << "\n";
            os << "Assigned Vehicles:\n";
            if (!center.users[i].assignedVehicles.empty()) 
            {
                for (const auto& vehicle : center.users[i].assignedVehicles) 
                {
                    os << "- " << vehicle << "\n";
                }
            } 
            else 
            {
                os << "None\n";
            }
            os << "__________\n";
        }

        os << "\n******************************\n";
        os << "Vehicles:\n";
        os << "__________\n";
        for (size_t i = 0; i < center.vehicles.size(); ++i) 
        {
            os << "Id: " << i << "\n";
            os << center.vehicles[i] << "\n";
        }

        os << "\n******************************\n";
        return os;
    }
};

// // Function to add sample data to LicenseCenter
// void add_temp_data(LicenseCenter& center) 
// {
//     User manager("Ayda", "100", "10");
//     center.manager = manager;
// }

#endif /* _LICENSECENTER_H_ */
