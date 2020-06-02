//This program is to demonstrate basic components of a hash table

#include<iostream>
#include <string>
using namespace std;

class HashTable {
private:
    struct Element {
        string key;
        int mark;       //2 = used; 1 = deleted; 0 = empty
    };
    Element *table;
    int size;

    //hash: returns an index into the hash table
    int hash(string s)
    {
        int i = 0;
        char ch;
        int num;
        int total = 0;


        for (int i = 0; i<s.length(); i++)
        {
            ch = s[i];
            num = int(ch);
            //cout << total << " + (ch: " << ch << ") " << num << " = ";
            total += num;
            //cout << total << endl;
        }

        return (total % size);
    }

public:
    //constructor: creates hash table that can store s many values (dynamically allocated array of elements)
    HashTable(int s)
    {
        table = new Element[s];
        size = s;

        for (int i=0; i<s; i++)
            table[i].mark = 0;
    }

    //destructor: frees all memory used
    ~HashTable()
    {
        delete [] table;
    }

    //insert: adds string to hash table, setting the element's mark where it is stored to 2
    void insert(string s)
    {
        int hi = hash(s);
        int x = 1;


        while (table[hi].mark == 2)
        {
            //linear probing
            //hi = (hi+1) % size;

            //quadratic probing
            hi = (hi + (x*x) + 2) % size;
            x++;

            //random probing
            //hi = (hi + (rand() % 40)) % size;

            //double hashing
        }
        table[hi].key = s;
        table[hi].mark = 2;
    }

    //remove: removes string from hash table (if found) by setting it's mark to 1
    void remove(string s)
    {
        int hi = hash(s);
        int i = 0;

        while (table[hi].mark != 0 && i<size)
        {
            if (table[hi].key == s)
            {
                table[hi].mark = 1;
            }
            i++;
            hi = (hi+1) % size;
        }
    }

    //isFull: returns true if the hash table is full, false otherwise
    bool isFull()
    {
        int total = 0;
        for (int i=0; i<size; i++)
        {
            if (table[i].mark == 2)
                total++;
        }

        if (total == size)
            return true;
        else
            return false;
    }

    //isEmpty: returns true if hash table is empty, false otherwise
    bool isEmpty()
    {
        for (int i=0; i<size; i++)
        {
            if (table[i].mark == 2)
                return false;
        }
        return true;
    }

    //clear: empties hash table by setting each elements mark to 0
    void clear()
    {
        for (int i=0; i<size; i++)
        {
            table[i].mark = 0;
        }
    }

    //print: displays contents of the hash table to the screen;
    //      that is, only the elements that are being used (marked w/ 2)
    void print()
    {
        cout << "contents of hash table:\n";
        for (int i=0; i<size; i++)
        {
            if (table[i].mark == 2)
                cout << "\telement: " << i << "\tkey: " << table[i].key << endl;
        }

    }

    //find: returns true if string is found in the hash table, false otherwise
    bool find(string s)
    {
        int hi = hash(s);
        int i = 0;

        while (table[hi].mark != 0 && i<size)
        {
            if (table[hi].key == s)
                return true;
            i++;
            hi = (hi + 1) % size;
        }
        return false;
    }
};

int main()
{
    //create hash table
    HashTable h(5);
    
    //test if hash is not full and is empty
    cout << h.isFull() << ", " << h.isEmpty() << endl;
    
    //test inserting items into hash table
    h.insert("Hello!");
    h.insert("Hello!");
    h.insert("How");
    h.insert("Are");
    h.insert("You?");
    
    //print updated hash table
    h.print();
    
    //test removing items from hash table
    h.remove("Hello!");
    h.remove("Hello!");
    
    //print updated hash table
    h.print();

    //test hash table is neither full nor empty
    cout << h.isFull() << ", " << h.isEmpty() << endl;

    //test find function
    cout << h.find("How") << ", " << h.find("Hello") << endl;
    cout << h.find("Dog") << endl;

    h.remove("Dog");
    
    //print updated hash table
    h.print();
    
    //test clear function
    h.clear();
    
    //test hash table is empty
    h.print();
}
