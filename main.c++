#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// User structure to hold user data
struct User {
    string username;
    string password;
};

// Function to read user data from a file
vector<User> readUserDataFromFile() {
    vector<User> users;
    ifstream file("users.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(",");
            if (pos != string::npos) {
                User user;
                user.username = line.substr(0, pos);
                user.password = line.substr(pos + 1);
                users.push_back(user);
            }
        }
        file.close();
    }
    return users;
}

// Function to write user data to a file
void writeUserDataToFile(const vector<User>& users) {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (const User& user : users) {
            file << user.username << "," << user.password << endl;
        }
        file.close();
    }
}

// Function to register a new user
void registerUser(vector<User>& users) {
    User newUser;
    cout << "Enter a username: ";
    cin >> newUser.username;
    cout << "Enter a password: ";
    cin >> newUser.password;
    users.push_back(newUser);
    writeUserDataToFile(users);
    cout << "Registration successful!" << endl;
}

// Function to authenticate a user
bool authenticateUser(const vector<User>& users, const string& username, const string& password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<User> users = readUserDataFromFile();

    while (true) {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            registerUser(users);
        } else if (choice == 2) {
            string username, password;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;

            if (authenticateUser(users, username, password)) {
                cout << "Login successful!" << endl;
            } else {
                cout << "Login failed. Invalid username or password." << endl;
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
