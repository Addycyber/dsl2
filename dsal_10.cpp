/*


Read the marks obtained by students of second year in an online examination of
particular subject. Find out maximum and minimum marks obtained in that subject.
Use heap data structure. Analyze the algorithm.
*/

#include <iostream>

using namespace std;

// Function to build max heap
void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) { 
        //the last non-leaf node is at index n/2 - 1
        int parent = i;

        while (parent < n / 2) {

            int leftChild = 2 * parent + 1;
            //left child is at this index

            int rightChild = 2 * parent + 2;
            //right child is at this index

            int largest = parent;

            if (leftChild < n && arr[leftChild] > arr[largest])
                largest = leftChild;

            if (rightChild < n && arr[rightChild] > arr[largest])
                largest = rightChild;

            if (largest != parent) 
            {
                swap(arr[parent], arr[largest]);
                parent = largest;
            } 
            else 
            {
                break;
            }
        }
    }
}

// Function to build min heap
void buildMinHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i;
        while (parent < n / 2) {

            int leftChild = 2 * parent + 1;
            int rightChild = 2 * parent + 2;

            int smallest = parent;

            if (leftChild < n && arr[leftChild] < arr[smallest])
                smallest = leftChild;

            if (rightChild < n && arr[rightChild] < arr[smallest])
                smallest = rightChild;

            if (smallest != parent) 
            {
                swap(arr[parent], arr[smallest]);
                parent = smallest;
            } 
            else 
            {
                break;
            }
        }
    }
}

// Function to find maximum and minimum marks
void findMinMaxMarks(int marks[], int n) {
    
    buildMaxHeap(marks, n);
    int maxMark = marks[0];

    buildMinHeap(marks, n);
    int minMark = marks[0];

    cout << "Maximum Marks: " << maxMark << endl;
    cout << "Minimum Marks: " << minMark << endl;
}

int main() {
    int n;
    cout << "Enter the number of students: " << endl;
    cin >> n;

    int* marks = new int[n];
    cout << "Enter the marks obtained by the students: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Student " << i+1 << " : ";
        cin >> marks[i];
    }

    findMinMaxMarks(marks, n);

    delete[] marks;
    return 0;
}