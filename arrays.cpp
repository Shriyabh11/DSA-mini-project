#include "utils.h"

void arrayMenu() {
    vector<int> glucose;
    int choice, value;

    do {
        line();
        cout << CYAN << "Glucose Log (Array Operations)" << RESET << endl;
        line();
        cout << "1. Add Glucose Reading\n2. Display All Readings\n3. Sort Readings\n4. Search Reading\n5. Analyze Trends\n6. Back\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter glucose reading (mg/dL): ";
                cin >> value;
                glucose.push_back(value);
                cout << GREEN << "Reading added successfully." << RESET << endl;
                break;

            case 2:
                if (glucose.empty()) cout << RED << "No readings logged yet." << RESET << endl;
                else {
                    cout << "Current readings: ";
                    for (int g : glucose) cout << g << " ";
                    cout << endl;
                }
                break;

            case 3:
                if (glucose.empty()) cout << RED << "No readings to sort." << RESET << endl;
                else {
                    sort(glucose.begin(), glucose.end());
                    cout << GREEN << "Readings sorted (low to high)." << RESET << endl;
                }
                break;

            case 4:
                if (glucose.empty()) { cout << RED << "No readings to search." << RESET << endl; break; }
                cout << "Enter reading to search: ";
                cin >> value;
                {
                    int l = 0, r = glucose.size() - 1, found = -1;
                    while (l <= r) {
                        int mid = (l + r) / 2;
                        if (glucose[mid] == value) { found = mid; break; }
                        else if (glucose[mid] < value) l = mid + 1;
                        else r = mid - 1;
                    }
                    if (found != -1)
                        cout << GREEN << "Reading found at position " << found + 1 << "." << RESET << endl;
                    else
                        cout << RED << "Reading not found." << RESET << endl;
                }
                break;

            case 5:
                if (glucose.empty()) cout << RED << "No data for trend analysis." << RESET << endl;
                else {
                    int maxVal = *max_element(glucose.begin(), glucose.end());
                    int minVal = *min_element(glucose.begin(), glucose.end());
                    double avg = accumulate(glucose.begin(), glucose.end(), 0.0) / glucose.size();
                    cout << "Average: " << avg << " mg/dL\n";
                    cout << "Lowest: " << minVal << " mg/dL, Highest: " << maxVal << " mg/dL\n";
                    if (avg > 180) cout << YELLOW << "Trend: High average — review meals or insulin." << RESET << endl;
                    else if (avg < 70) cout << YELLOW << "Trend: Low average — check hypo risks." << RESET << endl;
                    else cout << GREEN << "Trend: Stable readings overall." << RESET << endl;
                }
                break;
        }
    } while (choice != 6);
}
