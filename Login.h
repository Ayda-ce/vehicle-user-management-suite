#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "LicenseCenter.h" // Include header for LicenseCenter class
#include "User.h"          // Include header for User class
#include <iostream>        // Include for input/output stream operations

using namespace std; // Use the standard namespace for convenience

// Login class handles user authentication
class Login 
{
private:
    /* private data members or methods, if needed */
public:
    User user; // The currently logged-in user

    // Function to get login information and authenticate the user
    bool getLoginInfo(LicenseCenter &center) 
    {
        string nationalCode, password; // Variables to store user input

        // Prompt user for National ID and password
        cout << "Enter National ID: ";
        getline(cin, nationalCode);

        cout << "Enter Password: ";
        getline(cin, password);
 
        cout << "\n******************************\n";

        // Retrieve the user by national ID from the LicenseCenter
        User *foundUser = center.getUserByID(nationalCode);

        // Check if the user is found and if the password matches
        if (foundUser == nullptr || foundUser->password != password) 
        {
            cout << "Invalid National ID or Password" << endl;
            return false; // Authentication failed
        }

        // Populate the user object with the found user's details
        user = *foundUser;
        cout << "Login successful!" << endl;
        return true; // Authentication successful
    }
};

#endif /* __LOGIN_H__ */