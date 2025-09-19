#ifndef _USER_H_  
#define _USER_H_  

#include <iostream>  
#include <string>  
#include <vector>  
#include "Vehicle.h"  

using namespace std;  

// Class representing a user in the system  
class User   
{  
public:  
    string name;                // User's name  
    string nationalCode;        // National ID (also used as system ID)  
    string password;            // User's password  
    vector<Vehicle> assignedVehicles; // List of vehicles assigned to the user  

    // Default constructor  
    User() {}  

    // Parameterized constructor  
    User(const string& name, const string& nationalCode, const string& password)  
        : name(name), nationalCode(nationalCode), password(password) {}  

    // Overload << operator to display user information  
    friend ostream &operator<<(ostream &os, const User &user)   
    {  
        os << "Name: " << user.name << endl;  
        os << "National Code: " << user.nationalCode << endl;  
        os << "Password: " << user.password << endl;  
        os << "Assigned Vehicles: " << endl;  
        if (user.assignedVehicles.empty())   
        {  
            os << "None" << endl;  
        }   
        else   
        {  
            for (const auto &vehicle : user.assignedVehicles)   
            {  
                os << vehicle << endl;  
            }  
        }  
        return os;  
    }  
};  

#endif /* _USER_H_ */