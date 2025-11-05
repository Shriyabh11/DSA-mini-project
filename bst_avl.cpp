#include "utils.h"

struct Node {
    int glucose;
    Node* left;
    Node* right;
    int height;
    Node(int g) : glucose(g), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t = x->right;
    x->right = y;
    y->left = t;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* t = y->left;
    y->left = x;
    x->right = t;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insert(Node* root, int glucose) {
    if (!root) return new Node(glucose);

    if (glucose < root->glucose)
        root->left = insert(root->left, glucose);
    else if (glucose > root->glucose)
        root->right = insert(root->right, glucose);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && glucose < root->left->glucose)
        return rightRotate(root);
    if (balance < -1 && glucose > root->right->glucose)
        return leftRotate(root);
    if (balance > 1 && glucose > root->left->glucose) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && glucose < root->right->glucose) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->glucose << " ";
    inorder(root->right);
}

void treeMenu() {
    Node* root = nullptr;
    int choice, value;

    do {
        line();
        cout << CYAN << "Glucose Trend Tree (BST / AVL)" << RESET << endl;
        line();
        cout << "1. Insert New Reading\n2. Display Sorted Readings\n3. Show Trend Summary\n4. Back\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter glucose reading: ";
                cin >> value;
                root = insert(root, value);
                cout << GREEN << "Reading inserted successfully." << RESET << endl;
                break;

            case 2:
                if (!root) cout << RED << "No readings yet." << RESET << endl;
                else {
                    cout << "Sorted Glucose Readings: ";
                    inorder(root);
                    cout << endl;
                }
                break;

            case 3:
                if (!root) cout << RED << "No readings available for trend." << RESET << endl;
                else {
                    vector<int> vals;
                    function<void(Node*)> collect = [&](Node* n) {
                        if (!n) return;
                        collect(n->left);
                        vals.push_back(n->glucose);
                        collect(n->right);
                    };
                    collect(root);

                    int minVal = vals.front();
                    int maxVal = vals.back();
                    double avg = accumulate(vals.begin(), vals.end(), 0.0) / vals.size();

                    cout << "Minimum: " << minVal << " mg/dL\n";
                    cout << "Maximum: " << maxVal << " mg/dL\n";
                    cout << "Average: " << avg << " mg/dL\n";

                    if (avg > 180)
                        cout << YELLOW << "Trend: High glucose range detected." << RESET << endl;
                    else if (avg < 70)
                        cout << YELLOW << "Trend: Consistently low readings." << RESET << endl;
                    else
                        cout << GREEN << "Trend: Stable glucose control." << RESET << endl;
                }
                break;
        }
    } while (choice != 4);
}
