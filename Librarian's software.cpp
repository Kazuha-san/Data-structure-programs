#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node* createNode(int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }

    if (val < root->data)
        root->left = insertNode(root->left, val);
    else if (val > root->data)
        root->right = insertNode(root->right, val);

    return root;
}

bool searchNode(Node* root, int val) {
    if (root == NULL) return false;

    if (root->data == val){
            return true;
    }else if (val < root->data){
        return searchNode(root->left, val);
    }else{
        return searchNode(root->right, val);
    }
}

void inorder(Node* root) {
    if (root == NULL) return;

    inorder(root->left);
    cout << root->data << "\n";
    inorder(root->right);
}

// Menu
int main() {
    Node* root = NULL;
    int choice, id;

    while (true) {
        cout << "\nSMART BOOK TRACKING SYSTEM\n---------------------------\n";
        cout << "1. Insert Returned Book ID\n";
        cout << "2. Search Book ID\n";
        cout << "3. Display All Book IDs\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID to insert: ";
            cin >> id;
            root = insertNode(root, id);
            cout << "Book ID inserted successfully!\n";
            break;

        case 2:
            cout << "Enter Book ID to search: ";
            cin >> id;
            if (searchNode(root, id))
                cout << "Book ID " << id << " has been returned.\n";
            else
                cout << "Book ID " << id << " NOT found.\n";
            break;

        case 3:
            if (root == NULL) {
                cout << "No books have been returned yet!\n";
            } else {
                cout << "Returned Book IDs in sorted order:-\n";
                inorder(root);
                cout << endl;
            }
            break;

        case 4:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}
