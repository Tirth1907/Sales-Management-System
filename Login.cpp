#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // For output formatting
#include <limits>  // For clearing input buffer

// Use a simple data structure to represent a sales record
struct SalesRecord {
    std::string product;
    int quantity;
    double price;
};

// Function to handle adding a new sale
void addSale(const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
        return;
    }

    SalesRecord newSale;
    std::cout << "\n--- Add New Sale ---\n";
    std::cout << "Enter product name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::getline(std::cin, newSale.product);

    std::cout << "Enter quantity: ";
    std::cin >> newSale.quantity;

    std::cout << "Enter price per unit: $";
    std::cin >> newSale.price;

    file << newSale.product << "," << newSale.quantity << "," << newSale.price << "\n";
    file.close();
    std::cout << "\nSale record added successfully!\n";
}

// Function to display all sales records
void viewSales(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: No sales records found. File does not exist.\n";
        return;
    }

    std::string line;
    std::cout << "\n--- All Sales Records ---\n";
    std::cout << std::left << std::setw(20) << "Product" << std::setw(10) << "Quantity" << std::setw(10) << "Price" << "\n";
    std::cout << "------------------------------------------\n";

    while (std::getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        std::string product = line.substr(0, pos1);
        int quantity = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        double price = std::stod(line.substr(pos2 + 1));

        std::cout << std::left << std::setw(20) << product << std::setw(10) << quantity << std::setw(10) << price << "\n";
    }
    file.close();
}

// Function to search for sales records by product name
void searchSales(const std::string& filename) {
    std::string searchProduct;
    std::cout << "\n--- Search Sales ---\n";
    std::cout << "Enter product name to search: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, searchProduct);

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: No sales records found.\n";
        return;
    }

    std::string line;
    bool found = false;
    std::cout << "\n--- Search Results for '" << searchProduct << "' ---\n";

    while (std::getline(file, line)) {
        size_t pos1 = line.find(',');
        std::string product = line.substr(0, pos1);

        if (product.find(searchProduct) != std::string::npos) {
            size_t pos2 = line.find(',', pos1 + 1);
            int quantity = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            double price = std::stod(line.substr(pos2 + 1));

            std::cout << std::left << std::setw(20) << product << std::setw(10) << quantity << std::setw(10) << price << "\n";
            found = true;
        }
    }
    file.close();

    if (!found) {
        std::cout << "No sales records found for '" << searchProduct << "'.\n";
    }
}

// Main menu for the sales management system
void salesMenu() {
    int choice = 0;
    while (true) {
        std::cout << "\n--- Sales Management System Menu ---\n";
        std::cout << "1. Add a new sale\n";
        std::cout << "2. View all sales\n";
        std::cout << "3. Search for a sale\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input. Please enter a number from 1 to 4.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addSale("sales.txt");
                break;
            case 2:
                viewSales("sales.txt");
                break;
            case 3:
                searchSales("sales.txt");
                break;
            case 4:
                std::cout << "\nThank you for using the Sales Management System. Goodbye!\n";
                return;
            default:
                std::cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    }
}

// Simple main function to run the application
int main() {
    salesMenu();
    return 0;
}