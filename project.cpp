#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <stdexcept>
#include <utility>

#include "Data.h"
#include "Property.h"
#include "Agent.h"

using namespace std;

// --- Helper Functions ---

void addProperty(list<Data>& l) {
    Data newProperty;
    string agentId, contact, size, roomType, location, sellingPrice;

    cout << "Welcome to the property adding menu." << endl;
    cout << "Please insert your Agent ID: ";
    cin >> agentId;
    newProperty.setAgentId(agentId);

    cout << "Please insert your Contact: ";
    cin >> contact;
    newProperty.setContact(contact);

    cout << "Please insert your Property Size: ";
    cin >> size;
    newProperty.setPropertySize(size);

    cout << "Please insert your Room Type: ";
    cin >> roomType;
    newProperty.setRoomType(roomType);

    cout << "Please insert your Location: ";
    cin >> location;
    newProperty.setLocation(location);

    cout << "Please insert your Selling Price: ";
    cin >> sellingPrice;
    newProperty.setSellingPrice(sellingPrice);

    l.push_back(newProperty);
    cout << "\nProperty added successfully!\n" << endl;
}

void orderList(list<Data>& l) {
    char orderChoice;
    do {
        cout << "What order do you want? (a) ascending or (d) descending: ";
        cin >> orderChoice;
        if (orderChoice != 'a' && orderChoice != 'd') {
            cout << "ERROR: Invalid choice. Please enter 'a' or 'd'." << endl;
        }
    } while (orderChoice != 'a' && orderChoice != 'd');

    l.sort();
    if (orderChoice == 'd') {
        l.reverse();
    }
    cout << "\nList ordered successfully!\n" << endl;
}

bool findPass(const string& password, const string& agentId) {
    ifstream passwordsFile("passwords.in");
    if (!passwordsFile.is_open()) {
        cerr << "Error: Could not open passwords file." << endl;
        return false;
    }

    string filePass, fileAgentId;
    while (passwordsFile >> filePass >> fileAgentId) {
        if (password == filePass && agentId == fileAgentId) {
            passwordsFile.close();
            return true;
        }
    }
    passwordsFile.close();
    return false;
}

bool login(const string& agentId, const string& password) {
    if (findPass(password, agentId)) {
        cout << "\nAccess granted! Welcome, " << agentId << ".\n" << endl;
        return true;
    } else {
        cout << "\nLogin Failed! Invalid Agent ID or password.\n" << endl;
        return false;
    }
}

void changePass(const string& agentId) {
    vector<pair<string, string>> credentials;
    ifstream passwordsFile("passwords.in");

    if (!passwordsFile.is_open()) {
        cerr << "Error: Could not open passwords file." << endl;
        return;
    }

    string filePass, fileAgentId;
    while (passwordsFile >> filePass >> fileAgentId) {
        credentials.push_back({filePass, fileAgentId});
    }
    passwordsFile.close();

    string currentPass;
    cout << "To change your password, please re-login." << endl;
    cout << "What is your current password? ";
    cin >> currentPass;

    if (login(agentId, currentPass)) {
        string newPass;
        cout << "Access granted. Please input the new password: ";
        cin >> newPass;

        ofstream outFile("passwords.in");
        if (!outFile.is_open()) {
            cerr << "Error: Could not open passwords file for writing." << endl;
            return;
        }

        for (auto const& cred : credentials) {
            if (cred.second == agentId) {
                outFile << newPass << " " << agentId << endl;
            } else {
                outFile << cred.first << " " << cred.second << endl;
            }
        }
        outFile.close();
        cout << "\nPassword changed successfully!\n" << endl;
    }
}

char displayMenu() {
    char option;
    cout << "--- Menu ---" << endl;
    cout << "(a) Add new property" << endl;
    cout << "(b) Remove property" << endl;
    cout << "(c) Edit sales entries" << endl;
    cout << "(d) Inquire or search property sales" << endl;
    cout << "(e) Monthly property sales transaction report" << endl;
    cout << "(f) List property sale items in ascending or descending order" << endl;
    cout << "(g) Administration - add / remove property agent" << endl;
    cout << "(h) Administration - change password" << endl;
    cout << "(i) Quit" << endl;
    cout << "Enter your choice: ";
    cin >> option;
    return option;
}

void loadData(list<Data>& l) {
    l.clear(); 
    ifstream infile("data.in");
    if (!infile.is_open()) {
        cerr << "Error: Could not open data file." << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string segment;
        vector<string> segments;

        while (getline(ss, segment, ':')) {
            segments.push_back(segment);
        }

        if (segments.size() == 6) {
            Data datos(segments[0], segments[1], segments[2], segments[3], segments[4], segments[5]);
            l.push_back(datos);
        }
    }
    infile.close();
}

void showList(const list<Data>& l) {
    if (l.empty()) {
        cout << "The list is empty." << endl;
        return;
    }
    cout << "\n--- Property Sales List ---\n" << endl;
    for (const auto& data : l) {
        cout << "Agent ID: " << data.getAgentId()
             << ", Contact: " << data.getContact()
             << ", Size: " << data.getPropertySize()
             << ", Room Type: " << data.getRoomType()
             << ", Location: " << data.getLocation()
             << ", Price: " << data.getSellingPrice() << endl;
    }
    cout << "---------------------------\n" << endl;
}

// --- Main Program ---

int main() {
    list<Data> propertyList;
    string agentId, password;

    cout << "Please insert your Agent ID: ";
    cin >> agentId;
    cout << "Please insert your password: ";
    cin >> password;

    if (login(agentId, password)) {
        loadData(propertyList);
        char option;
        do {
            option = displayMenu();

            switch (option) {
                case 'a':
                    addProperty(propertyList);
                    break;
                case 'b':
                    cout << "Remove property functionality not implemented yet." << endl;
                    break;
                case 'c':
                    cout << "Edit sales entries functionality not implemented yet." << endl;
                    break;
                case 'd':
                    cout << "Inquire or search functionality not implemented yet." << endl;
                    break;
                case 'e':
                    cout << "Monthly report functionality not implemented yet." << endl;
                    break;
                case 'f':
                    orderList(propertyList);
                    showList(propertyList);
                    break;
                case 'g':
                    cout << "Agent administration functionality not implemented yet." << endl;
                    break;
                case 'h':
                    changePass(agentId);
                    break;
                case 'i':
                    cout << "Goodbye! 👋" << endl;
                    break;
                default:
                    cout << "Wrong selection. Please try again." << endl;
            }
        } while (option != 'i');
    }

    return 0;
}