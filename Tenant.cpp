# Tenant-System
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::find
#include <limits>    // for std::numeric_limits

using namespace std;

// Struct to hold tenant information
struct Tenant {
    string first_name;
    string last_name;
    int age;
    string sex;
    string address;
    string phone_number;
    int months_stayed;
    int num_tenants;
    double monthly_rate;
    double deposit;
    string tenant_status;
    double total_bill; // Added total_bill field
};

// Function to display tenant information
void displayTenantInformation(const Tenant& tenant, double total_bill) {
    cout << "Tenant Information: " << endl;
    cout << "First Name: " << tenant.first_name << endl;
    cout << "Last Name: " << tenant.last_name << endl;
    cout << "Age: " << tenant.age << endl;
    cout << "Sex: " << tenant.sex << endl;
    cout << "Address: " << tenant.address << endl;
    cout << "Phone Number: " << tenant.phone_number << endl;
    cout << "Months Stayed: " << tenant.months_stayed << endl;
    cout << "Tenant Status: " << tenant.tenant_status << endl;
    cout << "Total Bill: Php " << total_bill << endl;
}

int main() {
    vector<Tenant> tenants;

    while (true) {
        cout << "                                               TENANT MANAGEMENT SYSTEM " << endl;
        cout << "\nMenu:\n 1. Add Tenant Information\n 2. Search Tenant Information\n 3. Update Tenant Information\n 4. Delete Tenant Information\n 5. Exit\n";
        cout << "Enter your choice: ";

        int choice;

        // Input validation loop for choice
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();  // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        }

        switch (choice) {
            case 1: {  // Add tenant
                Tenant new_tenant;
                string back_option;
                cin.ignore();

                cout << "You selected Add Tenant Information. Enter 'back' anytime to return to the main menu.\n";

                cout << "Enter First Name (minimum 2 characters): ";
                getline(cin, new_tenant.first_name);
                if (new_tenant.first_name == "back") break;
                while (new_tenant.first_name.length() < 2) {
                    cout << "First Name must be at least 2 characters long. Please Enter Again: ";
                    getline(cin, new_tenant.first_name);
                    if (new_tenant.first_name == "back") break;
                }
                if (new_tenant.first_name == "back") break;

                cout << "Enter Last Name (minimum 2 characters): ";
                getline(cin, new_tenant.last_name);
                if (new_tenant.last_name == "back") break;
                while (new_tenant.last_name.length() < 2) {
                    cout << "Last Name must be at least 2 characters long. Please Enter Again: ";
                    getline(cin, new_tenant.last_name);
                    if (new_tenant.last_name == "back") break;
                }
                if (new_tenant.last_name == "back") break;

                cout << "Enter Age (must be at least 18): ";
                cin >> new_tenant.age;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (new_tenant.age == -1) break; // Assuming -1 means back

                while (new_tenant.age < 18) {
                    cout << "Age must be at least 18. Please Enter Again: ";
                    cin >> new_tenant.age;
                    if (new_tenant.age == -1) break;
                }
                if (new_tenant.age == -1) break;

                while (true) {
                    cout << "Enter Sex (M/F): ";
                    cin >> new_tenant.sex;
                    if (new_tenant.sex == "back") break;
                    if (new_tenant.sex != "M" && new_tenant.sex != "F") {
                        cout << "Invalid. Please Enter 'M' for Male or 'F' for Female: ";
                    } else {
                        break;
                    }
                }
                if (new_tenant.sex == "back") break;

                cin.ignore();
                cout << "Enter Address: ";
                getline(cin, new_tenant.address);
                if (new_tenant.address == "back") break;

                cout << "Enter Phone Number: ";
                cin >> new_tenant.phone_number;
                if (new_tenant.phone_number == "back") break;
                while (new_tenant.phone_number.length() < 11 || new_tenant.phone_number.length() > 11) {
                    cout << "Invalid. The phone number should be 11 digits. Please Enter Again: ";
                    cin >> new_tenant.phone_number;
                    if (new_tenant.phone_number == "back") break;
                }
                if (new_tenant.phone_number == "back") break;

                cout << "Enter Months Stayed (Please put a number): ";
                cin >> new_tenant.months_stayed;
                if (new_tenant.months_stayed == -1) break;

                cout << "Enter Tenant Status (new or New/old or Old): ";
                cin >> new_tenant.tenant_status;
                if (new_tenant.tenant_status == "back") break;

                new_tenant.monthly_rate = 5000.00;
                cout << "Monthly Rent Rate: " << new_tenant.monthly_rate << endl; // Monthly rent amount
                new_tenant.total_bill = new_tenant.months_stayed * new_tenant.monthly_rate;

                tenants.push_back(new_tenant);
                cout << "Tenant information added successfully." << endl;
                break;
            }

            case 2: {  // Search tenant
                string search_first_name;
                cin.ignore(); // Clear the input buffer
                cout << "You selected Search Tenant Information. Enter 'back' anytime to return to the main menu.\n";
                cout << "Enter First Name to Search: ";
                getline(cin, search_first_name);
                if (search_first_name == "back") break;

                bool found = false;
                for (const auto& tenant : tenants) {
                    if (tenant.first_name == search_first_name) {
                        displayTenantInformation(tenant, tenant.total_bill);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Tenant not found." << endl;
                }
                break;
            }

            case 3: {  // Update tenant
                string update_first_name;
                cin.ignore(); // Clear the input buffer
                if (tenants.empty()) {
                    cout << "No tenants to update." << endl;
                    break;
                }
                cout << "You selected Update Tenant Information. Enter 'back' anytime to return to the main menu.\n";
                cout << "Enter First Name of the tenant to update: ";
                getline(cin, update_first_name);
                if (update_first_name == "back") break;

                auto it = find_if(tenants.begin(), tenants.end(), [&update_first_name](const Tenant& tenant) {
                    return tenant.first_name == update_first_name;
                });

                if (it != tenants.end()) {
                    Tenant& tenant = *it; // Reference to the found tenant
                    cout << "Update Options:\n 1. First Name\n 2. Last Name\n 3. Age\n 4. Sex\n 5. Address\n 6. Phone Number\n 7. Months Stayed\n 8. Tenant Status\n";
                    cout << "Enter the number corresponding to the information you want to update or enter 'back' to return: ";

                    int update_choice;
                    cin >> update_choice;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }

                    if (update_choice == 0) break;  // Assuming 0 means back
                    // Continue with the other update options like before...
                } else {
                    cout << "Tenant not found." << endl;
                }
                break;
            }

            case 4: {  // Delete tenant
                string delete_first_name;
                cin.ignore(); // Clear the input buffer
                if (tenants.empty()) {
                    cout << "No tenants to delete." << endl;
                    break;
                }
                cout << "You selected Delete Tenant Information. Enter 'back' anytime to return to the main menu.\n";
                cout << "Enter First Name of the tenant to delete: ";
                getline(cin, delete_first_name);
                if (delete_first_name == "back") break;

                auto it = find_if(tenants.begin(), tenants.end(), [&delete_first_name](const Tenant& tenant) {
                    return tenant.first_name == delete_first_name;
                });

                if (it != tenants.end()) {
                    tenants.erase(it);
                    cout << "Tenant information deleted successfully." << endl;
                } else {
                    cout << "Tenant not found." << endl;
                }
                break;
            }

            case 5: {
                cout << "Exiting program..." << endl;
                return 0;
            }

            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

        // Clear the input stream in case of any invalid input leftover
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}
