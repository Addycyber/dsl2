/*

Beginning with an empty binary search tree, Construct binary search tree by
inserting the values in the order given. After constructing a binary tree - 
i. Insert new node ii. Find number of nodes in longest path iii. Minimum data 
value found in the tree iv. Change a tree so that the roles of the left and 
right pointers are swapped at every node v. Search a value
*/

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class node{
    public:
        int key;
        node *left, *right;
        node(int val){
            key = val;
            left = NULL;
            right = NULL;
        }
};

class BST{
    public:
        node *root;
        BST(){
            root = NULL;
        }

        void insert_node(int x){
            node *new_node = new node(x);
            if (root == NULL){
                root = new node(x);
                return;
            }
            else{
                node *temp = root;
                while(temp){
                    if(temp->key > x){
                        if (temp->left == NULL){
                            temp->left = new_node;
                        return;
                        }
                        temp = temp->left;
                    }
                    else{
                        if(temp->right == NULL){
                            temp->right = new_node;
                            return;
                        }
                        temp = temp->right;
                    }
                    
                }
            }
        }

        node* search(int x){
            node *temp = root;
            int lvl = 0;
            while (temp){
                if(temp->key == x){
                    return temp;              
                }
                else if (temp->key < x){
                    temp = temp->right;
                    lvl++;
                }
                else{
                    temp = temp->left;
                    lvl++;
                }
            }
            return NULL;
        }

        // Function to find the node with the smallest key in a subtree
		node* min_node(node* root) {
			node* current = root;
			while (current && current->left != NULL)
				current = current->left;
			return current;
		}

        void breadth_first_traversal(){
            cout << "\n";
            queue<node*> q;
            q.push(root);
            q.push(NULL);
            while(!q.empty()){
                node *temp = q.front();
                q.pop();
                if (temp == NULL){
                    cout << endl;
                    if (!q.empty()) q.push(NULL);
                }else{
                    cout << temp->key << " ";
                    if(temp->left){
                        q.push(temp->left);
                    }
                    if(temp->right){
                        q.push(temp->right);
                    }
                }
            }
        }

        void display(){
            stack<node*> s;
            s.push(root);
            int nb = 32;
            cout << "------------------------------------------------" << endl;
            bool is_row_empty = false;
            while (is_row_empty == false){
                stack<node*> s1;
                is_row_empty = true;
                for(int j = 0; j < nb; j++){
                    cout << " ";
                }
                while(s.empty() == false){
                    node *temp = s.top();
                    s.pop();
                    if (temp != NULL){
                        cout << temp->key;
                        s1.push(temp->left);
                        s1.push(temp->right);
                        if(temp->left != NULL || temp->right != NULL){
                            is_row_empty = false;
                        }
                    }
                    else{
                        cout << "--";
                        s1.push(NULL);
                        s1.push(NULL);
                    }
                    for(int j = 0; j < nb*2-2; j++){
                        cout << " ";
                    }      
                }
                cout << endl;
                nb /= 2;
                while (s1.empty() == false){
                    s.push(s1.top());
                    s1.pop();
                }
            }
            cout << "------------------------------------------------" << endl;
        }

        node* swap_children(node* temp){ 
            if(temp!=NULL){ 
            node* ptr = temp->left; 
            temp->left = swap_children(temp->right); 
            temp->right = swap_children(ptr); 
            } 
            return temp; 
        }

        void get_nodes_in_path(node* root,int count, int &max_count, int lvl, int &max_lvl){ 
            if(root==NULL){ 
                if(lvl > max_lvl){ 
                    max_lvl = lvl; 
                    max_count = count; 
                } 
                else if(lvl==max_lvl){ 
                    max_count = max(count, max_count); 
                } 
                return; 
            } 
            count += 1; 
            get_nodes_in_path(root->left,count, max_count, lvl+1, max_lvl); 
            get_nodes_in_path(root->right,count, max_count, lvl+1, max_lvl); 
        } 

        int count_nodes_in_LP(){ 
            int lvl = 0, max_lvl = 0; 
            int count = 0; 
            int max_count = 0; 
            get_nodes_in_path(root,count, max_count, lvl, max_lvl); 
            return max_count; 
        } 
};

int main(){ 
    BST b; 
    int data,op,n;
    do{
        cout << "\n--------------------**MENU**--------------------";
        cout << "\n1 = Insert a Node.";
        cout << "\n2 = Search a Node";
        cout << "\n3 = Breadth First Traversal.";
        cout << "\n4 = Display Tree.";
        cout << "\n5 = Number of Nodes in Longest Path.";
        cout << "\n6 = Minimum Value in Tree.";
        cout << "\n7 = Swap Subtrees.";
        cout << "\n8 = Exit\n";

        cin >> op;

        switch(op){ 

            case 1: 
                cout<<"How many Nodes you want to insert ? = "; cin>>n; 
                    for(int i = 0; i < n; i++){ 
                    cout<<"Enter Data for Node "<<(i+1)<<" = "; 
                    cin>>data; 
                    b.insert_node(data); 
                } 
                break; 

            case 2: 
                cout<<"Enter Node to be searched = "; 
                cin>>data;
                if (b.search(data))
                {
                    cout << "Node found." << "\nValue of node = " << b.search(data)->key << endl;
                }
                else
                {
                    cout << "Node not found." << endl;
                }
                break; 

            case 3: 
                cout<<"Breadth First Traversal "<<endl; 
                b.breadth_first_traversal(); 
                break; 
            case 4: 
                b.display(); 
                break; 
            case 5: 
                cout<<"Longest Nodes in Path = "<<b.count_nodes_in_LP()<<endl; 
                break; 
            case 6: 
                cout << " Minimun value in tree: " << b.min_node(b.root)->key << endl;; 
                break; 
            case 7: 
                cout<<"Tree After Swapping"<<endl; 
                b.swap_children(b.root); 
                b.display(); 
                b.swap_children(b.root); 
                break; 
            case 8: 
                return 0; 
            default: 
                cout<<"Invalid input."<<endl; 
                break; 
        } 
    
    }while(op != 8);
    return 0;
     
}