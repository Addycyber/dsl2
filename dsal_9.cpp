/*


A Dictionary stores keywords and its meanings. Provide facility for adding
new keywords, deleting keywords, updating values of any entry. Provide facility to
display whole data sorted in ascending/ Descending order. Also find how many
maximum comparisons may require for finding any keyword. Use Height balance tree
and find the complexity for finding a keyword.
*/

#include <iostream>
#include <string>
using namespace std;

// Node structure for AVL tree
class Node {
public:
    string key, mng;
    int height;
    Node *left, *right;
    Node(string k, string m)
    {
        key = k;
        mng = m;
        height = 1;
        left = right = NULL;
    }
};


class AVLTree {
private:
    Node* root;

    // Helper functions
    int getHeight(Node* node) 
    {
        return (node == NULL) ? 0 : node->height;
    }

    int getBalanceFactor(Node* node) 
    {
        return (node == NULL) ? 0 : ( getHeight(node->left) - getHeight(node->right) );
    }

    Node* rotate_right(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* rotate_left(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, string k, string v) {
        if (node == NULL) return new Node(k, v);

        if (k < node->key)
            node->left = insert(node->left, k, v);

        else if (k > node->key)
            node->right = insert(node->right, k, v);

        else 
        { // Update meaning if key already exists
            node->mng = v;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && k < node->left->key)
            return rotate_right(node);

        // Right Right Case
        if (balance < -1 && k > node->right->key)
            return rotate_left(node);

        // Left Right Case
        if (balance > 1 && k > node->left->key) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        // Right Left Case
        if (balance < -1 && k < node->right->key) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, string k) {
        if (root == NULL) return root;

        if (k < root->key)
            root->left = deleteNode(root->left, k);
        else if (k > root->key)
            root->right = deleteNode(root->right, k);
        else {
            if (root->left == NULL || root->right == NULL) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == NULL) return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotate_right(root);

        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotate_left(root);

        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }

        return root;
    }

    void inorder(Node* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->key << ": " << node->mng << endl;
        inorder(node->right);
    }

    void reverseInorder(Node* node) {
        if (node == NULL) return;
        reverseInorder(node->right);
        cout << node->key << ": " << node->mng << endl;
        reverseInorder(node->left);
    }

    int maxComparisons(Node* node, string k, int& count) {
        if (node == NULL) return count;
        count++;
        if (k < node->key)
            return maxComparisons(node->left, k, count);
        else if (k > node->key)
            return maxComparisons(node->right, k, count);
        else
            return count;
    }

public:
    AVLTree() : root(NULL) {}

    void insert(string key, string val) {
        root = insert(root, key, val);
    }

    void remove(string key) {
        root = deleteNode(root, key);
    }

    void update(string key, string val) {
        remove(key);
        insert(key, val);
    }

    void displayAscending() {
        inorder(root);
    }

    int findMaxComparisons(string key) {
        int count = 0;
        return maxComparisons(root, key, count);
    }
};

int main() {
    AVLTree dict;
    string key, value;
    int choice;
    while (true) {
        cout << "--------**MENU**--------" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Delete" << endl;
        cout << "4. Display" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "\nEnter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                cout << "Key '" << key << "' with value '" << value << "' inserted successfully." << endl;
                break;
            case 2:
                cout << "\nEnter key to search: ";
                cin >> key;
                if (dict.findMaxComparisons(key) > 0){
                    cout << "Key '" << key << "' found." << endl;
                    cout << "No. of comparisons: " << dict.findMaxComparisons(key) << endl;
                }       
                else
                    cout << "Key '" << key << "' not found." << endl;
                break;
            case 3:
                cout << "\nEnter key to delete: ";
                cin >> key;
                if (dict.findMaxComparisons(key) > 0) {
                    dict.remove(key);
                    cout << "Key '" << key << "' deleted successfully." << endl;
                } else {
                    cout << "Key '" << key << "' not found." << endl;
                }
                break;
            case 4:
                cout << "\nData sorted in ascending order:" << endl;
                dict.displayAscending();
                break;
            case 5:
                exit(0);
            default:
                cout << "\nInvalid imput." << endl;
        }
        cout << endl;
    }
    return 0;
}
