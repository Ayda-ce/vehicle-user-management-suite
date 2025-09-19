#ifndef _FILEPROVIDER_H_
#define _FILEPROVIDER_H_

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../models/User.h" // Ensure correct path
#include "../models/Vehicle.h" // Ensure correct path

using namespace std;

// Utility function to split a string by a delimiter
vector<string> split(const string &s, const string &delimiter) 
{
    vector<string> tokens;
    size_t start = 1, end;
    string temp;
    while ((end = s.find(delimiter, start)) != string::npos) 
    {
        temp = s.substr(start, end - start);
        temp.erase(temp.find_last_not_of(" \n")+1);
        tokens.push_back(temp);
        start = end + delimiter.length();
    }
    return tokens;
}

// Utility function to join a vector of strings with a delimiter
string join(const vector<string> &tokens, const string &delimiter, const int size, const int columns) 
{
    stringstream result;
    for (const auto &token : tokens) 
    {
    	result << left << delimiter << setw(size) << token;
    }
    result << delimiter << endl << string(columns*size+columns+1, '-');
    return result.str();
}

// Class for managing file operations related to users and vehicles
class FileProvider 
{
private:
    string filename;
    int size,columns;
    vector<vector<string>> content;

    // Parse the file and load its content into the `content` vector
    void parse() 
    {
        ifstream file(filename);
        if (!file.is_open()) 
        {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        getline(file,line);
        getline(file,line);
        while (getline(file, line)) 
        {
            content.push_back(split(line, "|"));
            getline(file,line);
        }
        file.close();
    }

    // Save the `content` vector to the file
    void save(const string &firstOfTable) const 
    {
        ofstream file(filename);
        if (!file.is_open()) 
        {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }
        
        file << firstOfTable;

        for (const auto &line : content) {
            file << join(line, "|", size, columns) << endl;
        }
        file.close();
    }

    // Convert a User object to a vector of strings
    vector<string> fromUser(const User &user) const 
    {
        return {user.name, user.nationalCode, user.password};
    }

    // Convert a vector of strings to a User object
    User toUser(const vector<string> &line) const 
    {
        if (line.size() < 3) {
            throw runtime_error("Invalid user data");
        }
        return User(line[0], line[1], line[2]);
    }

    // Convert a Vehicle object to a vector of strings
    vector<string> fromVehicle(const Vehicle &vehicle) const 
    {
        return {vehicle.vehicleCode, vehicle.brand, vehicle.model, to_string(vehicle.passengerCapacity)};
    }

    // Convert a vector of strings to a Vehicle object
    Vehicle toVehicle(const vector<string> &line) const 
    {
        if (line.size() < 4) 
        {
            throw runtime_error("Invalid vehicle data");
        }
        return Vehicle(line[0], line[1], line[2], stoi(line[3]));
    }

public:
    // Constructor that initializes the file provider with the given filename
    FileProvider(const string &filename, const int size, const int columns) : filename(filename) , size(size) , columns(columns)
    {
        parse();
    }

    // Retrieve a list of users from the file
    vector<User> getUsers() const 
    {
        vector<User> users;
        for (const auto &line : content) 
        {
            try 
            {
                users.push_back(toUser(line));
            } 
            catch (const exception &e) 
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        return users;
    }

    // Save the list of users to the file
    void saveUsers(const vector<User> &users) 
    {
        content.clear();
        for (const auto &user : users) 
        {
            content.push_back(fromUser(user));
        }
        stringstream temp;
        temp << left << "|" << setw(size) << "Name:" 
         << "|" << setw(size) << "NationalCode:" 
         << "|" << setw(size) << "Password:" << "|\n" << string(3*size+4, '-') << endl;
        save(temp.str());
    }

    // Retrieve a list of vehicles from the file
    vector<Vehicle> getVehicles() const 
    {
        vector<Vehicle> vehicles;
        for (const auto &line : content) 
        {
            try 
            {
                vehicles.push_back(toVehicle(line));
            } 
            catch (const exception &e) 
            {
                cerr << "Error: " << e.what() << endl;
            }
        }
        return vehicles;
    }

    // Save the list of vehicles to the file
    void saveVehicles(const vector<Vehicle> &vehicles) 
    {
        content.clear();
        for (const auto &vehicle : vehicles) 
        {
            content.push_back(fromVehicle(vehicle));
        }
        stringstream temp;
        temp << left << "|" << setw(size) << "Code:" 
         << "|" << setw(size) << "Brand:" 
         << "|" << setw(size) << "Model:" 
         << "|" << setw(size) << "Capacity:" << "|\n" << string(4*size+5, '-') << endl;    
        save(temp.str());
    }

    // Save the manager's details to a separate file
    void saveManager(const User &manager) const 
    {
    	int size=15;
        ofstream file("manager.txt");
        if (!file.is_open()) 
        {
            cerr << "Error: Could not open file manager.txt" << endl;
            return;
        }
        file << left << "|" << setw(size) << "Name:" 
         << "|" << setw(size) << "NationalCode:" 
         << "|" << setw(size) << "Password:" << "|\n" << string(3*size+4, '-') << endl
         << "|" << setw(size) << manager.name
         << "|" << setw(size) << manager.nationalCode
         << "|" << setw(size) << manager.password << "|" << endl;
        file.close();
    }
};

#endif /* _FILEPROVIDER_H_ */