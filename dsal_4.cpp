/*


A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to display
whole data sorted in ascending/ descending order. Also find how many maximum
comparisons may require for finding any keyword. Use Binary Search Tree for
implementation.
*/


#include<iostream>
#include<string.h>
using namespace std;

class node
{
	public:
		string key, mng;
		node *left;
		node *right;
		node(string k, string m)
		{	
			key = k;
			mng = m;
			left=NULL;
			right=NULL;
		}
};

class Dict
{
	public:
		node *root;
		Dict()
		{
			root=NULL;
		}

		node* get_root()
		{
			return root;
		}

		void insert(string k, string m)
		{
			node* new_node = new node(k, m);
			if(root==NULL)
			{
			    root = new_node;
				return;
			}
			else{
                node *temp = root;
                while(temp){
                    if(temp->key > k)
					{
                        if (temp->left == NULL){
                            temp->left = new_node;
                        	return;
                        }
                        else{
							temp = temp->left;
						}
                    }
                    else if (temp->key < k)
					{
                        if(temp->right == NULL){
                            temp->right = new_node;
                            return;
                        }
						else{
							temp = temp->right;
						}
                        
                    }
                    
                }
            }
		}

		void inorderTraversal(node* root)
		{
			if(root==NULL){
				return;
			}
			inorderTraversal(root->left);
			cout << root->key << " --> " << root->mng << endl;
			inorderTraversal(root->right);
    	}

		node* search(string key)
		{
			node* temp = root;
			int lvl = 0;
			while(temp){
				if(temp->key==key){
					cout << "\n Key found at level " << lvl << endl;
					cout << temp->key << " --> " << temp->mng << endl;
					return temp;
				}else if(temp->key < key){
					temp = temp->right;
					lvl++;
				}else{
					temp = temp->left;
					lvl++;
				}
			}
			cout << "\nKey not Found." << endl;
			return NULL;
    	}

		void update(string key)
		{
			node* temp = search(key);
			if(temp != NULL){
				string new_mng;
				cout<<"Enter new meaning = ";
				cin>>new_mng;
				temp->mng = new_mng;
				return;
			}
			cout<<"Key does not exist"<<endl;
			return;
		}

		node* delete_node(node *root, string k)
		{
			if (root == NULL)
			{
				cout << "Node not found." << endl;
				return NULL;
			}
			
			// Traverse the tree to find the node with the given key
			if (k < root->key)
			{
				root->left = delete_node(root->left, k);
			}

			else if (k > root->key)
			{
				root->right = delete_node(root->right, k);
			}

			else 
			{ // If k matches the root's key, this is the node to be deleted

				// Case 1: Node with no child or only one child
				if (root->left == NULL) {
					node* temp = root->right;
					delete root;
					return temp;
				}
				else if (root->right == NULL) {
					node* temp = root->left;
					delete root;
					return temp;
				}

				// Case 2: Node with two children
				// Find the inorder successor (smallest in the right subtree)
				node* temp = min_node(root->right);

				// Copy the inorder successor's content to this node
				root->key = temp->key;
				root->mng = temp->mng;

				// Delete the inorder successor
				root->right = delete_node(root->right, temp->key);
			}
			return root;			
		}

		// Function to find the node with the smallest key in a subtree
		node* min_node(node* root) {
			node* current = root;
			while (current && current->left != NULL)
				current = current->left;
			return current;
		}
};

int main(){
    Dict d;
    int op,n;
    string k, m;
    while(true){
        cout<<"\n------------------**MENU**-----------------";
		cout << "\n1 - Insert Data";
		cout<<"\n2 = Search Data";
		cout <<"\n3 = Update Data";
		cout << "\n4 = Display in Ascending order";
		cout << "\n5 = Delete";
		cout << "\n6 = Exit\n";
        cin >> op;
        switch(op){
            case 1:
                cout << "Enter number of objects to enter: ";
                cin >> n;
                for(int i = 0; i < n; i++){
                    cout << "Enter Key: ";
                    cin >> k;
                    cout << "Enter Meaning = ";
                    cin >> m;
                    d.insert(k,m);
                }
                break;
            case 2:
                cout<<"Enter key to be searched: ";
                cin>>k;
				d.search(k);
                break;
            case 3:
                cout<<"Enter key whose meaning to be updated ";
                cin >> k;
                d.update(k);
                break;
            case 4:
                d.inorderTraversal(d.root);
                break;
			case 5:
				cout << "Enter key to delete: ";
				cin >> k;
				d.delete_node(d.root, k);
				break;
            case 6:
                return 0;
            default:
                cout<<"Invalid input."<<endl;
                break;
        }
    }
	return 0;
}