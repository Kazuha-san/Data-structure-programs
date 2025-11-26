#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node* CreateNode(int val) {
    Node* newnode = new Node();
    newnode->data = val;
    newnode->left = newnode->right = NULL;
    return newnode;
}

Node* insertBST(Node* root, int val) {
    if (root == NULL) return CreateNode(val);

    if (val < root->data)
        root->left = insertBST(root->left, val);
    else if (val > root->data)
        root->right = insertBST(root->right, val);

    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void FreeTree(Node* root) {
    if (!root) return;
    FreeTree(root->left);
    FreeTree(root->right);
    delete root;
}

int main() {
    Node* root = NULL;
    int n, val;

    cout << "How many values do you want to insert? ";
    cin >> n;

    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insertBST(root, val);
    }

    cout << "\nInorder: ";
    inorder(root);
    cout << "\nPreorder: ";
    preorder(root);
    cout << "\nPostorder: ";
    postorder(root);
    cout << "\n";

    FreeTree(root);
    return 0;
}
