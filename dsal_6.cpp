/*


Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list 
to perform BFS. Use the map of the area around the college as thegraph. Identify the prominent
land marks as nodes and perform DFS and BFS on that.
*/



#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class node
{
    public:
        int data;
        node* next;
        node(int val)
        {
            data = val;
            next = NULL;
        }
};

void add_edge(node* adjList[], int v1, int v2)
{
    node* new_node = new node(v2);
    new_node->next = adjList[v1];
    adjList[v1] = new_node;

    new_node = new node(v1);
    new_node->next = adjList[v2];
    adjList[v2] = new_node;
}

void print_adjacency_list(node* adjList[], int v) 
{
    cout << "\n---Adjacency List----" << endl;
    for (int i = 0; i < v; i++) {
        node* temp = adjList[i];
        cout <<  i << " --> ";
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

void print_adjacency_matrix(int* adjMat[], int v)
{
    cout << "\n----Adjacency Matrix----" << endl;
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			cout << adjMat[i][j] << " ";
		}
		cout << endl;
	}
}

void breadth_first_traversal(node* adjList[], int v, int start)
{
    bool* visited = new bool[v]; // array to keep track of visited vertices
    for (int i = 0; i < v; i++) {
        visited[i] = false; // Mark all vertices as not visited
    } 

    queue<int> bfs_queue;  //queue for bfs

    // Mark the current node as visited and enqueue it
    visited[start] = true;
    bfs_queue.push(start);

    //traverse the graph
    while (!bfs_queue.empty())
    {
        //dequeue vertex and print it
        int curr = bfs_queue.front();
        cout << curr << " ";
        bfs_queue.pop();

        node* temp = adjList[curr];
        while (temp != NULL) {
            int neighbour = temp->data;
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                bfs_queue.push(neighbour);
            }
            temp = temp->next;
        }
    }
    cout << endl;
    delete[] visited;

}

void depth_first_traversal(node* adjList[], int v, int start)
{
    bool* visited = new bool[v]; // array to keep track of visited vertices
    for (int i = 0; i < v; i++) {
        visited[i] = false; // Mark all vertices as not visited
    }  

    stack<int> dfs_stack;

    // Mark the current node as visited and push it onto the stack
    visited[start] = true;
    dfs_stack.push(start);

    // Traverse the graph
    while (!dfs_stack.empty()) 
    {
        // Pop a vertex from stack and print it
        int curr = dfs_stack.top();
        dfs_stack.pop();
        cout << curr << " ";

        node* temp = adjList[curr];
        while (temp != NULL) {
            int neighbour = temp->data;
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                dfs_stack.push(neighbour);
            }
            temp = temp->next;
        }
    }
    cout << endl;
    delete[] visited;

}

int main()
{
    int v, e, st;
	cout << "Enter the number of vertices in graph: ";
	cin >> v;
	cout << "Enter the number of edges in graph: ";
	cin >> e;

    int** adjMat = new int*[v]; // Dynamically allocate memory for adjacency matrix
    for (int i = 0; i < v; i++) {
        adjMat[i] = new int[v];
        // Initialize adjacency matrix to 0
        for (int j = 0; j < v; j++) {
            adjMat[i][j] = 0;
        }
    }

    node** adjList = new node*[v]; // Dynamically allocate memory for adjacency list
    for (int i = 0; i < v; i++) {
        // Initialize adjacency list to null
        adjList[i] = NULL;
    }

    cout << "Enter the vertices which are joined with an edge: " << endl;
	for ( int i = 0; i < e; i++)
	{
        cout << "e" << (i+1)<< " : ";
		int v1, v2;
		cin >> v1 >> v2;
		
		adjMat[v1][v2] = 1;
		adjMat[v2][v1] = 1;

        add_edge(adjList, v1, v2);	
		
	}

    print_adjacency_list(adjList, v);
    print_adjacency_matrix(adjMat, v);

    cout << "\nEnter the starting vertex for traversal: ";
    cin >> st;

    // Perform BFS from given vertex
    cout << "\nBFS traversal starting from vertex " << st << " : ";
    breadth_first_traversal(adjList, v, st);
    cout << endl;

    // Perform DFS from given vertex
    cout << "\nDFS traversal starting from vertex " << st << " : ";
    depth_first_traversal(adjList, v, st);
    cout << endl;

    // Deallocate memory
    delete[] adjList;
    delete[] adjMat;
    
    return 0;
}