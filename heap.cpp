/*This program demonstrates the components of a heap using an
  example of how an emergency room is run*/

#include <iostream>
#include <string>
using namespace std;

class ERHeap {
private:
    struct Node {           //store info for the patient
        int priority;       //priorities: 3 = high, 2 = medium, 1 = low
        string name;        //name of patient
        string description;     //condition
    };
    Node* heap; //memory address of an array of nodes
    int capacity;   //number of elements in array
    int bottom;     //index of element at bottom of heap; -1 if empty
    void ReHeapUp();
    void ReHeapDown();

public:
    ERHeap(int);
    ~ERHeap();
    void enqueue (string, string, int);
    void dequeue (string &);
    //void print();
};

int main() {
    char choice;            //for selecting option in menu
    string name, complaint;
    int priority;

    //create heap
    ERHeap patientList(10);

    //menu
    do
    {
        cout << "(A)dd Patient\n"
             << "(N)ext Patient\n"
             << "(Q)uit\n"
             << ":] ";
        cin >> choice;

        switch(choice)
        {
            //add patient
            case 'a':
            case 'A':
            {
                //enter patient info
                cout << "Enter a patient's name: ";
                cin.ignore();
                getline(cin,name);
                cout << "Enter complaint: ";
                cin.ignore();
                getline(cin,complaint);
                cout << "Enter priority: ";
                cin >> priority;
                
                //add patient to queue
                patientList.enqueue(name,complaint,priority);
                //patientList.print();
                break;
            }

            //next patient
            case 'n':
            case 'N':
            {
                //obtain patient at root of queue (highest priority)
                patientList.dequeue(name);
                cout << "Next patient: " << name << endl;
                //patientList.print();
                break;
            }

            //quit program
            case 'q':
            case 'Q':
                return 0;
            
            //default for all other options
            default:
                cout << "Select appropriate option.\n";
        }

    } while (choice != 'q' || choice != 'Q');   //loop through program until user selects to quit

    return 0;
}

/***********************************************************
 * ******       FUNCTIONS       *****************************
 ************************************************************/

//private function ReHeapUp: reorder queue to move the last element up into
//                          its rightful position
void ERHeap::ReHeapUp()
{
    int c = bottom;     //begin at last element
    int p;              //holds element to compare
    
    //loop until last element added is in its correct position
    while (c <= bottom)
    {
        //if root of the queue has been compared, exit function
        if (c == 0)
            return;
            
        //otherwise, move element up the queue if applicable
        p = (c-1)/2;

        if (heap[p].priority > heap[c].priority)
            break;
        else
            swap(heap[p], heap[c]);
            
        //update position to last compared
        c = p;
    }
}

//private function ReHeapDown: reorder queue to move the first element down
//                              to its rightful position
void ERHeap::ReHeapDown()
{
    int p = 0;
    int lc, rc, bc;
    
    //loop until last element has been compared to
    while (p <= capacity)
    {
        //calculate positions of left and right children
        lc = (2*p) + 1;
        rc = (2*p) + 2;
        
        //if there is no left child, exit function
        if (lc > bottom)
            return;
            
        //if there is no right child, then it is its bigger child
        if (rc > bottom)
            bc = lc;
            
        //if there element has children, identify its bigger child
        else
        {
            if (heap[rc].priority > heap[lc].priority)
                bc = rc;
            else
                bc = lc;

        }
        
        //move element to correct position if applicable
        if (heap[p].priority < heap[bc].priority)
            swap(heap[p],heap[bc]);
        else
            return;

        //update position value of element
        p = bc;
    }
}

//public function constructor: dynamically allocates an array of Nodes and stores the memory address in heap;
//                              sets capacity to its argument; initializes bottom to -1
ERHeap::ERHeap(int s)
{
    heap = new Node[s];     //create heap of size s
    /*
    for (int i=0; i<s; i++)
    {
        heap[i].name = " ";
        heap[i].description = " ";
        heap[i].priority = 0;
    }
     */
    capacity = s;       //holds value of size of heap
    bottom = -1;        //holds position of last element in heap
}

//public function destructor: frees all memory used by the object
ERHeap::~ERHeap()
{
    delete [] heap;
}

//public function enqueue: stores the patient's info in the heap; calls ReHeapUp to rebuild the heap as needed
void ERHeap::enqueue (string name, string desc, int pri)
{
    //if heap is full, exit function
    if (bottom == capacity-1)
        return;
    
    //otherwise, add element to queue
    bottom++;
    heap[bottom].name = name;
    heap[bottom].description = desc;
    heap[bottom].priority = pri;
    ReHeapUp();
}

//public function dequeue: removes the patient's info from the heap; calls ReHeapDown to rebuild the heap as needed
void ERHeap::dequeue (string &name)
{
    //if heap is empty, exit function
    if (bottom == -1)
    {
        name = {};
        return;
    }

    //otherwise, remove element from heap
    name = heap[0].name;
    swap(heap[0],heap[bottom]);
    bottom--;
    ReHeapDown();
}

/*
void ERHeap::print()
{
    for (int i=0; i<=bottom; i++)
        cout << heap[i].name << "\t" << heap[i].priority << endl;
}
*/