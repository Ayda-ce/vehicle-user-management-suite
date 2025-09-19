#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "models/LicenseCenter.h"
#include "models/User.h"
#include "models/Vehicle.h"
#include "utils/fileprovider.h"

using namespace std;

// Displays the main menu
void showMenu() 
{
    cout << "\n--- Main Menu ---\n";
    cout << "1. Display All Users\n";
    cout << "2. Add New User\n";
    cout << "3. Display All Vehicles\n";
    cout << "4. Add New Vehicle\n";
    cout << "5. Assign Vehicle to User\n";
    cout << "6. Save Manager Information\n";
    cout << "7. Display Users and Assigned Vehicles\n";
    cout << "0. Exit\n";
    cout << "Select an option: ";
}

// Adds a new user to the list and prompts user input
void addNewUser(vector<User>& users) 
{
    string name, nationalCode, password;
    cout << "Enter user name: ";
    cin >> name;
    cout << "Enter national code: ";
    cin >> nationalCode;
    cout << "Enter password: ";
    cin >> password;

    users.emplace_back(name, nationalCode, password); // Add user to list
    cout << "User added successfully!\n";
}

// Displays the list of users
void displayUsers(const vector<User>& users) 
{
    int size = 25;

    cout << "\n--- Users List ---\n";
    cout << left << "\n| " << setw(size) << "Name:" 
         << "| " << setw(size) << "NationalCode:" 
         << "| " << setw(size) << "Password:" << "|\n" << string(3*size+7, '-') << endl;
    for (const auto& user : users) 
    {
        cout << "| " << setw(size) << user.name
             << "| " << setw(size) << user.nationalCode
             << "| " << setw(size) << user.password << "|" << endl << string(3*size+7, '-') << endl;
    }
}

// Adds a new vehicle to the list and prompts user input
void addNewVehicle(vector<Vehicle>& vehicles) 
{
    string vehicleCode, brand, model;
    int passengerCapacity;

    cout << "Enter vehicle code: ";
    cin >> vehicleCode;
    cout << "Enter vehicle brand: ";
    cin >> brand;
    cout << "Enter vehicle model: ";
    cin >> model;
    cout << "Enter passenger capacity: ";
    cin >> passengerCapacity;

    vehicles.emplace_back(vehicleCode, brand, model, passengerCapacity); // Add vehicle to list
    cout << "Vehicle added successfully!\n";
}

// Displays the list of vehicles
void displayVehicles(const vector<Vehicle>& vehicles) 
{
    int size = 10;

    cout << "\n--- Vehicles List ---\n";
    cout << left << "\n| " << setw(size) << "Code:" 
         << "| " << setw(size) << "Brand:" 
         << "| " << setw(size) << "Model:" 
         << "| " << setw(size) << "Capacity:" << "|\n" << string(4*size+9, '-') << endl;
    for (const auto& vehicle : vehicles) 
    {
        if (vehicle.vehicleCode.empty()) continue; // Skip empty entries
        cout << "| " << setw(size) << vehicle.vehicleCode
             << "| " << setw(size) << vehicle.brand
             << "| " << setw(size) << vehicle.model
             << "| " << setw(size) << vehicle.passengerCapacity << "|" << endl << string(4*size+9, '-') << endl;
    }
}

// Assigns a vehicle to a user
void assignVehicleToUser(vector<User>& users, vector<Vehicle>& vehicles) 
{
    string userId, vehicleCode;
    cout << "Enter User ID: ";
    getline(cin, userId);

    auto userIt = find_if(users.begin(), users.end(), [&](const User& u) { return u.nationalCode == userId; });
    if (userIt == users.end()) 
    {
        cout << "User not found!" << endl;
        return;
    }

    cout << "Enter Vehicle Code: ";
    getline(cin, vehicleCode);

    auto vehicleIt = find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& v) { return v.vehicleCode == vehicleCode; });
    if (vehicleIt == vehicles.end()) 
    {
        cout << "Vehicle not found!" << endl;
        return;
    }

    userIt->assignedVehicles.push_back(*vehicleIt);
    cout << "Vehicle assigned to user successfully!" << endl;
}

// Saves manager information to file after user input
void saveManager(FileProvider& fileProvider) 
{
    string name, nationalCode, password;
    cout << "Enter manager's name: ";
    cin >> name;
    cout << "Enter manager's national code: ";
    cin >> nationalCode;
    cout << "Enter manager's password: ";
    cin >> password;

    User manager(name, nationalCode, password); // Create manager object
    fileProvider.saveManager(manager); // Save manager to file
    cout << "Manager information saved successfully!\n";
}

// Displays users who have assigned vehicles
void displayUsersWithVehicles(const vector<User>& users) 
{
    cout << "\n--- Users with Assigned Vehicles ---\n";
    
    int userSize = 25;
    int vehicleSize = 10;
    bool foundAny = false;

    for (const auto& user : users) 
    {
        if (user.assignedVehicles.empty()) continue; // Skip users without assigned vehicles

        foundAny = true;

        cout << "\nUser: " << user.name << " (ID: " << user.nationalCode << ")\n";
        cout << left << "\n| " << setw(vehicleSize) << "Vehicle Code:" 
             << "| " << setw(vehicleSize) << "Brand:" 
             << "| " << setw(vehicleSize) << "Model:" 
             << "| " << setw(vehicleSize) << "Capacity:" << "|\n" << string(4*vehicleSize+9, '-') << endl;
        
        for (const auto& vehicle : user.assignedVehicles) 
        {
            cout << "| " << setw(vehicleSize) << vehicle.vehicleCode
                 << "| " << setw(vehicleSize) << vehicle.brand
                 << "| " << setw(vehicleSize) << vehicle.model
                 << "| " << setw(vehicleSize) << vehicle.passengerCapacity << "|" << endl << string(4*vehicleSize+9, '-') << endl;
        }
    }
    
    if (!foundAny) 
    {
        cout << "No users with assigned vehicles.\n";
    }
}

int main() 
{
    // Load users and vehicles from respective files
    FileProvider userFile("users.txt", 25, 3);
    FileProvider vehicleFile("vehicles.txt", 10, 4);

    vector<User> users = userFile.getUsers();
    vector<Vehicle> vehicles = vehicleFile.getVehicles();

    int choice;
    do 
    {
        showMenu(); // Display menu
        cin >> choice;
        cin.ignore(); // Clear newline character

        // Perform action based on user choice
        switch (choice) 
        {
            case 1:
                displayUsers(users);
                break;
            case 2:
                addNewUser(users);
                userFile.saveUsers(users); // Save updated users list
                break;
            case 3:
                displayVehicles(vehicles);
                break;
            case 4:
                addNewVehicle(vehicles);
                vehicleFile.saveVehicles(vehicles); // Save updated vehicles list
                break;
            case 5:
                assignVehicleToUser(users, vehicles); // Assign vehicle to user
                break;
            case 6:
                saveManager(userFile);
                break;
            case 7:
                displayUsersWithVehicles(users); // Display users with assigned vehicles
                break;
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } 
    while (choice != 0); // Repeat until user chooses to exit

    return 0;
}
