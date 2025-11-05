#include "utils.h"

struct Meal {
    string name;
    int carbs;
    string time;
    Meal* next;
    Meal(string n, int c, string t): name(n), carbs(c), time(t), next(nullptr) {}
};
Meal* head = nullptr;

void linkedListMenu() {
    int choice;
    string mealName, time;
    int carbs;

    do {
        line();
        cout << CYAN << "Meal Log (Linked List)" << RESET << endl;
        line();
        cout << "1. Add Meal\n2. Delete Meal\n3. Display Meal History\n4. Back\nChoice: ";
        cin >> choice;
        cin.ignore(); // clears leftover newline before any getline()

        switch (choice) {
            case 1:
                cout << "Meal name: ";
                getline(cin, mealName); // allows full meal names like “curd rice”
                cout << "Carbs (grams): ";
                cin >> carbs;
                cin.ignore();
                cout << "Time (e.g. 08:30AM): ";
                getline(cin, time);

                {
                    Meal* newMeal = new Meal(mealName, carbs, time);
                    if (!head) head = newMeal;
                    else {
                        Meal* temp = head;
                        while (temp->next) temp = temp->next;
                        temp->next = newMeal;
                    }
                    cout << GREEN << "Meal logged successfully." << RESET << endl;
                }
                break;

            case 2:
                cout << "Enter meal name to delete: ";
                getline(cin, mealName);
                {
                    Meal *curr = head, *prev = nullptr;
                    bool found = false;
                    while (curr) {
                        if (curr->name == mealName) {
                            found = true;
                            if (!prev) head = curr->next;
                            else prev->next = curr->next;
                            delete curr;
                            cout << GREEN << "Meal deleted." << RESET << endl;
                            break;
                        }
                        prev = curr;
                        curr = curr->next;
                    }
                    if (!found) cout << RED << "Meal not found." << RESET << endl;
                }
                break;

            case 3:
                if (!head) cout << RED << "No meals logged yet." << RESET << endl;
                else {
                    cout << "Recent Meals:\n";
                    Meal* temp = head;
                    while (temp) {
                        cout << temp->time << " - " << temp->name << " (" << temp->carbs << "g carbs)\n";
                        temp = temp->next;
                    }
                }
                break;

            case 4:
                break;

            default:
                cout << RED << "Invalid choice. Try again." << RESET << endl;
        }
    } while (choice != 4);
}
