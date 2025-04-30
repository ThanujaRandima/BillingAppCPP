// meal hut billing system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
using namespace std;



// Structure for menu items
struct MenuItem {
    string name;
    double price = 0;
};

// Global variable to store the menu
map<int, MenuItem> menu = {
    {111, {"Plain Egg", 1.45}},
    {112, {"Bacon and Egg", 2.45}},
    {113, {"Muffin", 0.99}},
    {114, {"French Toast", 1.99}},
    {115, {"Fruit Basket", 2.49}},
    {116, {"Cereal", 0.69}},
    {117, {"Coffee", 0.50}},
    {118, {"Tea", 0.75}}
};

// Function declarations
void showMenu();
bool isValidNumber(string input);
int getValidNumberInput();
void printCheck(map<int, int>& order);
void printOrderSummary(map<int, int>& order);
void removeItem(map<int, int>& order);

int main() {
    map<int, int> order;
    int choice;

    do {
        // Main menu prompt
        cout << "\n******** Meal Hut - Main Menu ********" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. Order Items" << endl;
        cout << "3. Print Bill" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        choice = getValidNumberInput();

        switch (choice) {
        case 1:
            showMenu();
            break;

        case 2: {
            showMenu();
            char more = 'y';

            while (more == 'y') {
                cout << "\nEnter the item number you want to order: ";  // Prompt for item number
                int itemNo = getValidNumberInput();

                if (menu.find(itemNo) == menu.end()) {
                    cout << "Invalid item number. Please try again.\n";
                    continue;
                }

                cout << "Enter quantity (minimum 1): ";
                int quantity = getValidNumberInput();
                //if (quantity < 1) quantity = 1;
                //added while loop to prevent user from adding 0 items
                while (quantity < 1) {
                    cout << "Quantity must be at least 1. Please enter again: ";
                    quantity = getValidNumberInput();
                }

                order[itemNo] += quantity;
                cout << quantity << " " << menu[itemNo].name << (quantity > 1 ? "s" : "") << " added to your order!\n";

                while (true) {
                    cout << "Do you want to order more? (y/n): ";
                    cin >> more;
                    if (more == 'y' || more == 'n') break;
                    cout << "Invalid input. Please enter 'y' or 'n'.\n";
                }
            }

            // Show the current order summary before asking to remove items
            printOrderSummary(order);

            // Ask if the user wants to remove any items
            char remove = 'n';
            do {
                cout << "Do you want to remove any items from your order? (y/n): ";
                cin >> remove;
                if (remove == 'y') {
                    removeItem(order);
                    // Show updated order summary after removal
                    printOrderSummary(order);
                }
            } while (remove == 'y');  // Keep asking until they don't want to remove more

            break;
        }

        case 3:
            // Print the final bill with tax and amount due
            printCheck(order);
            break;

        case 4:
            cout << "Exiting program. Have a great day!\n";
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }

    } while (choice != 4);

    return 0;
}

// Function definitions

// Displays the menu
void showMenu() {
    cout << "\n******** Welcome to Meal Hut ********" << endl;
    cout << "        Breakfast Billing System" << endl;
    cout << "-------------------------------------------" << endl;
    cout << left << setw(10) << "Item No" << setw(25) << "Menu Item" << "Price" << endl;
    cout << "-------------------------------------------" << endl;
    for (const auto& item : menu) {
        cout << left << setw(10) << item.first << setw(25) << item.second.name << "$" << fixed << setprecision(2) << item.second.price << endl;
    }
    cout << "-------------------------------------------" << endl;
}

// Checks if input is a valid number
bool isValidNumber(string input) {
    for (char c : input) {
        if (!isdigit(c)) return false;
    }
    return !input.empty();
}

// Get valid number input from user
int getValidNumberInput() {
    string input;
    while (true) {
        cin >> input;
        if (isValidNumber(input)) return stoi(input);
        cout << "Invalid input. Please enter a valid number: ";
    }
}

// Prints the bill with tax and final amount
void printCheck(map<int, int>& order) {
    if (order.empty()) {
        cout << "\nNo items ordered. Returning to main menu.\n";
        return;
    }

    double total = 0;
    cout << "\n******** Bill ********" << endl;
    cout << left << setw(10) << "Item No" << setw(25) << "Menu Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (const auto& item : order) {
        double itemTotal = menu[item.first].price * item.second;
        cout << left << setw(10) << item.first << setw(25) << menu[item.first].name << setw(10) << item.second
            << "$" << fixed << setprecision(2) << itemTotal << endl;
        total += itemTotal;
    }

    double tax = total * 0.05;
    double finalAmount = total + tax;

    cout << "-----------------------------------------------------" << endl;
    cout << left << setw(35) << "Tax" << "$" << fixed << setprecision(2) << tax << endl;
    cout << left << setw(35) << "Amount Due" << "$" << fixed << setprecision(2) << finalAmount << endl;
    cout << "******************************************" << endl;
    cout << "Thank you for dining at Meal Hut!\n";
}

// Prints the order summary
void printOrderSummary(map<int, int>& order) {
    if (order.empty()) {
        cout << "\nNo items ordered. Returning to main menu.\n";
        return;
    }

    cout << "\n******** Order Summary ********" << endl;
    cout << left << setw(10) << "Item No" << setw(25) << "Menu Item" << setw(10) << "Quantity" << endl;
    cout << "-------------------------------------------" << endl;
    for (const auto& item : order) {
        cout << left << setw(10) << item.first << setw(25) << menu[item.first].name << setw(10) << item.second << endl;
    }
    cout << "-------------------------------------------" << endl;
}

// Removes an item from the order
void removeItem(map<int, int>& order) {
    int itemNo, removeQty;

    while (true) {
        cout << "\nEnter the item number you want to remove: ";
        itemNo = getValidNumberInput();

        if (order.find(itemNo) == order.end()) {
            cout << "Item not found in your order. Please enter a valid item number.\n";
            continue;
        }

        cout << "Enter quantity to remove: ";
        removeQty = getValidNumberInput();

        if (removeQty > order[itemNo]) {
            cout << "You cannot remove more than the ordered quantity.\n";
            continue;
        }

        order[itemNo] -= removeQty;
        if (order[itemNo] == 0) {
            order.erase(itemNo);
        }

        cout << removeQty << " " << menu[itemNo].name << (removeQty > 1 ? "s" : "") << " removed from your order!\n";
        break;
    }
}

