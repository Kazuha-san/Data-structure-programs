#include <iostream>
#include <queue>
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

Node* BuildTree(int n) {
    if (n == 0) return NULL;

    int val;
    cout << "Enter value for root: ";
    cin >> val;

    Node* root = CreateNode(val);

    queue<Node*> q;
    q.push(root);

    int count = 1;
    while (!q.empty() && count < n) {
        Node* current = q.front();
        q.pop();

        //Left child
        cout << "Enter left child of " << current->data << " (0 for NULL): ";
        cin >> val;

        if (val != 0) {
            current->left = CreateNode(val);
            q.push(current->left);
            count++;
            if (count == n) break;
        }

        //Right child
        cout << "Enter right child of " << current->data << " (0 for NULL): ";
        cin >> val;

        if (val != 0) {
            current->right = CreateNode(val);
            q.push(current->right);
            count++;
            if (count == n) break;
        }
    }
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
    int n;
    cout << "Enter total number of nodes: ";
    cin >> n;

    cout << "BINARY TREE:\n";
    Node* root = BuildTree(n);

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
