#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Structure for Employee
struct Employee {
    int id;
    string name;
    int age;
    string department;
};

// Node for AVL Tree
struct AVLNode {
    Employee data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// Function to get the height of the node
int getHeight(AVLNode* node) {
    return (node == nullptr) ? 0 : node->height;
}

// Function to calculate the balance factor
int getBalance(AVLNode* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Utility function to create a new AVLNode
AVLNode* createNode(Employee emp) {
    AVLNode* node = new AVLNode();
    node->data = emp;
    node->left = node->right = nullptr;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Right rotate
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotate
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert function
AVLNode* insert(AVLNode* node, Employee emp) {
    if (node == nullptr)
        return createNode(emp);

    if (emp.id < node->data.id)
        node->left = insert(node->left, emp);
    else if (emp.id > node->data.id)
        node->right = insert(node->right, emp);
    else
        return node; // Duplicate IDs not allowed

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Check balance
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && emp.id < node->left->data.id)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && emp.id > node->right->data.id)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && emp.id > node->left->data.id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && emp.id < node->right->data.id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Search function
AVLNode* search(AVLNode* root, int id) {
    if (root == nullptr || root->data.id == id)
        return root;

    if (id < root->data.id)
        return search(root->left, id);

    return search(root->right, id);
}

// In-order traversal
void inOrderTraversal(AVLNode* root) {
    if (root == nullptr)
        return;

    inOrderTraversal(root->left);
    cout << "ID: " << root->data.id << ", Name: " << root->data.name
         << ", Age: " << root->data.age << ", Department: " << root->data.department << endl;
    inOrderTraversal(root->right);
}

// Main program
int main() {
    AVLNode* root = nullptr;
    queue<Employee> taskQueue;

    // Insert employees
    root = insert(root, {101, "Alice", 30, "HR"});
    root = insert(root, {102, "Bob", 35, "Finance"});
    root = insert(root, {103, "Charlie", 28, "IT"});

    // Display all employees
    cout << "Employees in Database:" << endl;
    inOrderTraversal(root);

    // Search for an employee
    int searchID = 102;
    AVLNode* result = search(root, searchID);
    if (result)
        cout << "\nFound Employee: ID " << result->data.id << ", Name " << result->data.name << endl;
    else
        cout << "\nEmployee with ID " << searchID << " not found!" << endl;

    return 0;
}
