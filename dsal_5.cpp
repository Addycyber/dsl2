/*


Convert given binary tree into threaded binary tree. Analyze time and space
complexity of the algorithm.
*/

#include <iostream>
#include <queue>
using namespace std;

class node 
{
	public :
		int data;
		node *right,*left;
        bool isThreaded;
        node(int val){
            data = val;
            left = NULL;
            right = NULL;
            isThreaded = false;
        }
};

class TBT 
{
	
	public:
        node *root;
        TBT(){
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
                    if(temp->data > x){
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

        //putting the inorder pattern into a queue
        void convert_queue(node* root, std::queue<node*>* q){
            if (root == NULL)
                return;
            if (root->left)
                convert_queue(root->left, q);
            q->push(root);
            if (root->right)
                convert_queue(root->right, q);
        }


        //traversing the queue and making threaded tree
        void create_threadedtree(node* root, std::queue<node*>* q){
            if (root == NULL)
                return;
            if (root->left)
                create_threadedtree(root->left, q);
            q->pop();
            if (root->right)
                create_threadedtree(root->right, q);
            //if right pointer in NUll, point it to inorder successor
            else {
                root->right = q->front();
                root->isThreaded = true;
            }
        }

        //taking the tree and converting it into threaded
        void createThreaded(node* root){
            queue<node*> q;
            convert_queue(root, &q);
            create_threadedtree(root, &q);
        }

        node* min_node(node* root) {
			node* current = root;
			while (current && current->left != NULL)
				current = current->left;
			return current;
		}

        //performing inorder traversal of threaded tree
        void inOrder(node* root){
            if (root == NULL)
                return;
            node* curr = min_node(root);
            while (curr != NULL) {
                cout << curr->data << " ";
                //if threaded node, move to inorder successor
                if (curr->isThreaded)
                    curr = curr->right;
                else
                    curr = min_node(curr->right);
            }
        }
};

int main()
{
    TBT t;
    int op, n, data;
    do{
        cout<<"\n------------------**MENU**-----------------";
		cout << "\n1 - Create binary tree";
		cout<<"\n2 = Convert to Threaded binary tree";
		cout <<"\n3 = Display inorder traversal";
		cout << "\n4 = Exit\n";
        cin >> op;
        switch(op){
            case 1:
                cout << "Enter number of objects to enter: ";
                cin >> n;
                for(int i = 0; i < n; i++){
                    cout << "Enter data: ";
                    cin >> data;
                    t.insert_node(data);
                }
                break;
            case 2:
                t.createThreaded(t.root);
                cout << "Binary tree converted to threaded binary tree." << endl;
                break;
            case 3:
                cout<<"Traversing threaded binary tree: " << endl;
                t.inOrder(t.root);
                break;
            case 4:
                break;
            default:
                cout<<"Invalid input."<<endl;
                break;
        }
    }while(op != 4);
	return 0;
}

