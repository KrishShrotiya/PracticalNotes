#include <iostream>
using namespace std;

class avlnode {
    int value;
    avlnode *left, *right;

public:
    avlnode(int val) {
        value = val;
        left = right = nullptr;
    }

    friend class avltree;
};

class avltree {
private:
    avlnode* root;

    int height(avlnode*);
    int diff(avlnode*);

    avlnode* rr_rotation(avlnode*);
    avlnode* ll_rotation(avlnode*);
    avlnode* lr_rotation(avlnode*);
    avlnode* rl_rotation(avlnode*);

    avlnode* balance(avlnode*);
    avlnode* insert(avlnode*, int);

    void inorder(avlnode*);
    void preorder(avlnode*);
    void postorder(avlnode*);

public:
    avltree() { root = nullptr; }

    void insert();
    void inorder();
    void preorder();
    void postorder();
};

avlnode* avltree::ll_rotation(avlnode* parent) {
    avlnode* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avlnode* avltree::rr_rotation(avlnode* parent) {
    avlnode* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avlnode* avltree::lr_rotation(avlnode* parent) {
    parent->left = rr_rotation(parent->left);
    return ll_rotation(parent);
}

avlnode* avltree::rl_rotation(avlnode* parent) {
    parent->right = ll_rotation(parent->right);
    return rr_rotation(parent);
}

int avltree::height(avlnode* temp) {
    if (temp == nullptr)
        return 0;
    return max(height(temp->left), height(temp->right)) + 1;
}

int avltree::diff(avlnode* temp) {
    if (temp == nullptr)
        return 0;
    return height(temp->left) - height(temp->right);
}

avlnode* avltree::balance(avlnode* temp) {
    int balance_factor = diff(temp);

    if (balance_factor > 1) {
        if (diff(temp->left) >= 0) {
            temp = ll_rotation(temp);
        } else {
            temp = lr_rotation(temp);
        }
    } else if (balance_factor < -1) {
        if (diff(temp->right) <= 0) {
            temp = rr_rotation(temp);
        } else {
            temp = rl_rotation(temp);
        }
    }
    return temp;
}

avlnode* avltree::insert(avlnode* node, int value) {
    if (node == nullptr)
        return new avlnode(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);

    return balance(node);
}

void avltree::insert() {
    int n;
    cout << "Enter the number of nodes to insert: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int value;
        cout << "Enter value " << (i + 1) << ": ";
        cin >> value;
        root = insert(root, value);
    }

    char ch;
    do {
        int value;
        cout << "Enter another value to insert (or -1 to stop): ";
        cin >> value;

        if (value == -1)
            break;

        root = insert(root, value);

        cout << "Do you want to insert another value? (y/N): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}


void avltree::inorder(avlnode* node) {
    if (node == nullptr)
        return;

    inorder(node->left);
    cout << node->value << " ";
    inorder(node->right);
}

void avltree::preorder(avlnode* node) {
    if (node == nullptr)
        return;

    cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
}

void avltree::postorder(avlnode* node) {
    if (node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->value << " ";
}

void avltree::inorder() {
    cout << "Inorder Traversal: ";
    inorder(root);
    cout << endl;
}

void avltree::preorder() {
    cout << "Preorder Traversal: ";
    preorder(root);
    cout << endl;
}

void avltree::postorder() {
    cout << "Postorder Traversal: ";
    postorder(root);
    cout << endl;
}

int main() {
    avltree tree;
    int choice;

    do {
        cout << "\nAVL Tree Operations:\n";
        cout << "1. Insert Node\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Postorder Traversal\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tree.insert();
                break;
            case 2:
                tree.inorder();
                break;
            case 3:
                tree.preorder();
                break;
            case 4:
                tree.postorder();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
