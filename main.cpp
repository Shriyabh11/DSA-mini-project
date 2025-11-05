#include "utils.h"

void arrayMenu();
void linkedListMenu();
void stackQueueMenu();
void treeMenu();
void graphMenu();

int main() {
    int choice;
    do {
        system("cls");
        cout << BOLD << WHITE << "SMART DIABETES DATA MANAGER (C++)" << RESET << endl;
        line();
        cout << "1. Glucose Log (Arrays)\n";
        cout << "2. Meal Log (Linked List)\n";
        cout << "3. Task Manager (Stack & Queue)\n";
        cout << "4. Glucose Trend Tree (AVL)\n";
        cout << "5. Lifestyle Graph (Graph Algorithms)\n";
        cout << "6. Exit\n";
        line();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: arrayMenu(); break;
            case 2: linkedListMenu(); break;
            case 3: stackQueueMenu(); break;
            case 4: treeMenu(); break;
            case 5: graphMenu(); break;
            case 6:
                cout << YELLOW << "Exiting... Stay consistent with your tracking!" << RESET << endl;
                break;
            default:
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }

        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 6);
    return 0;
}
