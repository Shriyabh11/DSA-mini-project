#include "utils.h"

void stackQueueMenu() {
    vector<string> undoStack;
    queue<string> reminders;
    int choice;
    string task;

    do {
        line();
        cout << CYAN << "Task Manager (Stack & Queue)" << RESET << endl;
        line();
        cout << "1. Log New Task\n2. Undo Last Action\n3. Add Reminder\n4. Complete Reminder\n5. Show All\n6. Back\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter task (e.g., Checked glucose at 2PM): ";
                getline(cin, task);
                undoStack.push_back(task);
                cout << GREEN << "Task recorded." << RESET << endl;
                break;

            case 2:
                if (undoStack.empty()) cout << RED << "No actions to undo." << RESET << endl;
                else {
                    cout << "Undoing: " << undoStack.back() << endl;
                    undoStack.pop_back();
                }
                break;

            case 3:
                cout << "Enter reminder (e.g., Take insulin at 9PM): ";
                getline(cin, task);
                reminders.push(task);
                cout << GREEN << "Reminder added." << RESET << endl;
                break;

            case 4:
                if (reminders.empty()) cout << RED << "No reminders pending." << RESET << endl;
                else {
                    cout << "Completed: " << reminders.front() << endl;
                    reminders.pop();
                }
                break;

            case 5:
                cout << "Recent actions (Stack):" << endl;
                for (int i = undoStack.size() - 1; i >= 0; i--) cout << "- " << undoStack[i] << endl;
                cout << "\nUpcoming reminders (Queue):" << endl;
                {
                    queue<string> temp = reminders;
                    while (!temp.empty()) {
                        cout << "- " << temp.front() << endl;
                        temp.pop();
                    }
                }
                break;
        }
    } while (choice != 6);
}
