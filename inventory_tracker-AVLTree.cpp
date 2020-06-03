//This program acts as an inventory tracker, using an AVL tree

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class AVLTree {
private:
    struct Node {               //represent a part in inventory
        int partnum;            //part number; key value that uniquely identifies the part
        string description;     //describes the part
        int qty;                //number of the part on hand
        double price;           //price of part
        Node* left, *right;     //address of left/right child node
    };
    Node* root;                 //address of root node
    void clear(Node*&);
    int height(Node*);
    void rotateRight(Node*&);
    void rotateLeft(Node*&);
    void rotateRightLeft(Node*&);
    void rotateLeftRight(Node*&);
    int difference(Node*);
    void balance(Node*&);
    void append(Node*&, int, int, double, string);
    void remove(Node*&, int);
    string getOutOfStock(Node*);
    string getPart(Node*, int);
    void print(Node*) const;

public:
    AVLTree();  //constructor
    ~AVLTree();     //destructor
    void clear();   //clears tree
    void append(int, int, double, string);  //adds nodes to tree
    void remove(int);           //remove node from tree
    string getOutOfStock();
    string getPart(int);
    void print() const;
};

/**************************************************************************************
 * ************                 MAIN()                          ***********************
 * ************************************************************************************/

int main() {
    char choice;     //user option selection in menu
    AVLTree inventory;
    string description;
    double price;
    int partNumber, quantity;


    //menu
    do
    {
        cout << "(A)dd a part\n"
            << "(R)emove a part\n"
            << "(S)earch for a part\n"
            << "(O)ut of stock\n"
            << "(Q)uit\n"
            << "[Enter your choice] >> ";
        cin >> choice;

        switch(choice)
        {
            //add a part to the database; provides an interface for adding new parts to a database;
            //      parts have a description, a part ID number, a price, and a quantity on hand
            case 'a':
            case 'A':
            {
                //add
                cout << "Enter part description: ";
                cin.ignore();
                getline(cin,description);
                cout << "Enter the price: ";
                cin >> price;
                cout << "Enter the part number: ";
                cin >> partNumber;
                cout << "Enter the quantity on hand: ";
                cin >> quantity;

                inventory.append(partNumber,quantity,price,description);
                cout << "Update of inventory:\n";

                //verify append occurred
                 inventory.print();
                break;
            }

            //remove a part from the database; provides an interface for removing a part from the inventory database
            case 'r':
            case 'R':
            {
                //remove
                cout << "Enter part number for part to remove: ";
                cin >> partNumber;

                inventory.remove(partNumber);
                cout << "Update of inventory:\n";

                //verify removal
                inventory.print();
                break;
            }

            //search for a part in the database; searches the database for a specific part by ID number, meaning
            //      the ID number is used for the search key; if found, the part's description, price, and quantity
            //      on hand is displayed; if not, an appropriate message is displayed
            case 's':
            case 'S':
            {
                //search
                cout << "Enter part number to search for: ";
                cin >> partNumber;

                cout << inventory.getPart(partNumber) << endl;
                break;
            }

            //out of stock; displays a list of all parts in the database with a quantity of 0
            case 'o':
            case 'O':
            {
                //getOutOfStock
                cout << "The following items are out of stock:\n";
                cout << inventory.getOutOfStock();
                break;
            }

            //quit; terminate the program
            case 'q':
            case 'Q':
            {
                return 0;
            }

            //invalid option
            default:
                cout << "Please select a valid option.\n";
        }

    } while (choice != 'q' || choice != 'Q');

    return 0;
}

/**************************************************************************************
 * ************                 FUNCTIONS                       ***********************
 * ************************************************************************************/

//AVLTree function: constructor; sets root to null
AVLTree::AVLTree()
{
    root = nullptr;
}

//~AVLTree function: destructor; frees all memory used by calling public clear() method
AVLTree::~AVLTree()
{
    clear();
}

//clear private function: frees all memory used by the object
void AVLTree::clear(Node*& r)
{
    if (r != nullptr)
    {
        clear(r->left);
        clear(r->right);
        delete r;
        r = nullptr;
    }
}

//clear public function: calls the private version, passing the root pointer as an argument
void AVLTree::clear()
{
    clear(root);
    root = nullptr;
}

//height function: returns the height of the (sub)tree; accepts a node pointer as an argument
int AVLTree::height(Node* r)
{
    int lh = 0, rh = 0;
    if (r == nullptr)
        return 0;

    lh = height(r->left);
    rh = height(r->right);

    if (lh > rh)
        return(1+lh);
    else
        return(1+rh);
}

//rotateRight function: performs a right rotation; accepts a node pointer as an argument
void AVLTree::rotateRight(Node*& r)
{
    Node *p = r->left;
    r->left = p->right;
    p->right = r;
    r = p;
}

//rotateLeft function: performs a left rotation; accepts a node pointer as an argument
void AVLTree::rotateLeft(Node*& r)
{
    Node *p = r->right;
    r->right = p->left;
    p->left = r;
    r = p;
}

//rotateRightLeft function: performs a right-left rotation; accepts a node pointer as an argument
void AVLTree::rotateRightLeft(Node*& r)
{
    rotateRight(r->right);
    rotateLeft(r);
}

//rotateLeftRight function: performs a left-right rotation; accepts a node pointer as an argument
void AVLTree::rotateLeftRight(Node*& r)
{
    rotateLeft(r->left);
    rotateRight(r);
}

//difference function: returns the difference in height between two subtrees by calling height on each subtree
//          accepts a Node pointer as an argument
int AVLTree::difference(Node* r)
{
     //check if difference is working
    int diff = 0;
    diff = (height(r->right) - height(r->left));
    cout << "difference: " << diff << endl;
    return diff;

   // return (height(r->right) - height(r->left));
}

//balance function: determines what, if any, rotation(s) should be applied to subtrees by calling difference
//                  and rotate methods; accepts a Node pointer by reference
void AVLTree::balance(Node*& r)
{
    //cout << "balance called\n";
    if (difference(r) == -2)
    {
        //if nodes are positioned as ">"
        if (difference(r->left) == -1)
            rotateRight(r);
        //if nodes are positioned as "\"
        else
            rotateLeftRight(r);
        //verify balance was done
        //cout << "balance done\n.";
    }
    else if (difference(r) == 2)
    {
        //if nodes are positioned as "<"
        if (difference(r->right) == -1)
            rotateRightLeft(r);
        //if nodes are positioned as "/"
        else
        {
            rotateLeft(r);
        }
        //cout << "balance done\n.";
    }
}

//append private function: adds part to tree
void AVLTree::append(Node*& r, int num, int qty, double price, string desc)
{
    //case: tree is empty
    if (r == nullptr)
    {
        r = new Node;
        r->partnum = num;
        r->qty = qty;
        r->price = price;
        r->description = desc;
        r->left = nullptr;
        r->right = nullptr;
    }
    //case: element to add requires movement to the left
    else if (num < r->partnum)
    {
        append(r->left, num, qty, price, desc);
        balance(r);
    }

    //case: element to add requires movement to the right
    else
    {
        append(r->right, num, qty, price, desc);
        balance(r);
    }
}

//append public function: passes info to private append method; accepts a part's number, qty, description, and price as arguments
void AVLTree::append(int num, int qty, double price, string desc)
{
    append(root, num, qty, price, desc);
}

//remove private function: causes the matching part to be removed from the tree
void AVLTree::remove(Node*& r, int num)
{
    //case: tree is empty
    if (r == nullptr)
    {
        return;
    }

    //case: move left to reach element to remove
    else if (num < r->partnum)
    {
        remove(r->left, num);
        balance(r);
    }

    //case: move right to reach element to remove
    else if (num > r->partnum)
    {
        remove(r->right, num);
        balance(r);
    }

    //case: remove node currently at
    else
    {
        Node* temp;

        //case: node has no children
        if (r->left == nullptr && r->right == nullptr)
        {
            delete r;
            r = nullptr;
        }
        //case: node has left child only
        else if (r->left != nullptr && r->right == nullptr)
        {
            temp = r;
            r = r->left;
            delete temp;
        }
        //case: node has right child only
        else if (r->left == nullptr && r->right != nullptr)
        {
            temp = r;
            r = r->right;
            delete temp;
        }
        //case: node has left and right children
        else
        {
            temp = r->right;

            while (temp->left)
            {
                temp = temp->left;
            }

            temp->left = r->left;
            temp = r;
            r = r->right;

            delete temp;
        }
    }
}

//remove public function: passes info to the private remove method; accepts a part's number
void AVLTree::remove(int num)
{
    remove(root, num);
}

//getOutOfStock private function: searches the tree for all parts with qty 0, building a string of parts as it goes;
//                                for each part, the description, qty, price, and number is added to the string
string AVLTree::getOutOfStock(Node* r)
{
    //case: tree is empty
    if (r == nullptr)
        return {};

    string str;
    
    //add elements in tree in order
     str += getOutOfStock(r->left);

    if(r->qty <= 0)
    {
        ostringstream ss;
        ss << r->partnum << ", "
                << r->description << ", "
                << r->price << ", "
                << r->qty << endl;
        str += ss.str();
        ss.clear();
    }

    str += getOutOfStock(r->right);

    return str;
}

//getOutOfStock public function: returns the string returned by the private getOutOfStock method;
//          calls the private version, passing it the root pointer as an argument
string AVLTree::getOutOfStock()
{
    return getOutOfStock(root);
}

//getPart private function: if it finds the part, returns a string consisting of the part description, price, qty,
//                          and number; if it doesn't find it, it returns an appropriate error message such as
//                          "OUT OF STOCK"
string AVLTree::getPart(Node* r, int num)
{
    //case: tree is empty
    if(r == nullptr)
    {
        return "OUT OF STOCK";
    }
    //case: element is found at current position
    else if(r->partnum == num)
    {
        ostringstream ss;
        ss << r->partnum << endl
           << r->description << endl
           << r->price << endl
           << r->qty << endl;
        return ss.str();
    }

    //case: require movement to the left to find element
    else if(num < r->partnum)
        return getPart(r->left, num);
    
    //case: require movement to the right to find element
    else
        return getPart(r->right, num);
}

//getPart public function: returns the string returned by the private getPart method; accepts a part's number as
//                          it's only argument and calls the private version, passing it the number and the root pointer
string AVLTree::getPart(int num)
{
    return getPart(root, num);
}


//print
void AVLTree::print() const
{
    print(root);
}

void AVLTree::print(Node* r) const
{
    if (r == nullptr)
        return;

    print(r->left);
    cout << r->partnum << "\t"
         << r->description << "\t"
         << r->qty << "\t"
         << r->price << endl;
    print(r->right);
}

