#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

ifstream infile;
ofstream outfile;

int collision = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////

class LNODE
{
public:
    string value;
    LNODE* next;
    LNODE* head; // not needed
};
    //------------------------
     LNODE * newNode()
    {
        LNODE *temp;
        temp = new LNODE;
        temp->value = " ";
        temp->next = NULL;
    }
    //-------------------------------------
     void insert(LNODE * head, string v)
    {
        LNODE *c, *p, *temp; // don't do c=head here in case head is empty

        if(head->value == " ") // if no data
        {
            head->value = v;
        }
        else
        {
            collision = collision + 1; // count collision
            c = head; // temp head
            while(c) // (c != NULL) // c = (linky of the last node) out of list = null, then stops
            {
                p = c;
                c = c->next;
            }
            temp = newNode();
            temp->value = v;
            temp->next = NULL;
            p->next = temp;
        }
    }
//------------------------
    void printNode(LNODE * head)
    {
        LNODE *c;
        c = head;
        while(c) // c != NULL // c = (linky of the last node) = null, then stops
        {
            cout << " -> " << c->value;
            outfile << " -> " << c->value;
            c = c->next;
        }
        cout << endl;
        outfile << endl;
    }
//------------------------
    void printOneNode(LNODE * head, int nodeNumber, bool found)
    {
        if(found == true)
        {
            LNODE *c;
            c = head;
            for(int i=0; i<nodeNumber-1; i++) // c != NULL // c = (linky of the last node) = null, then stops
            {
                c = c->next;
            }
            cout << c->value << endl;
            outfile << c->value << endl;
        }
        else
        {
            cout << "Not found." << endl;
            outfile << "Not found." << endl;
        }
    }
////////////////////////////////////////////////////////////////////////////////////
class HTItem
{
public:
    int key;
    LNODE* head;
    //---------------------
    HTItem()
    {
        key = -1;
        head = newNode();
    }
};

/////////////////////////////////////////////////////////////////////////////////
int createHkey(string s)
{
    long long key = 0;
    int len = s.length();
    for(int i=0; i<len; i++)
    {
        key = key + s[i];
    }
    return (key % 79);
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    string s, name;
    int hashKey;
    HTItem hashTable[79];
    string nameArray[79];
            infile.open("HashNamesAndPhone.txt");
            if(!infile)
            {
                cout << " Error while opening the file." << endl;
                outfile << " Error while opening the file." << endl;
            }
            outfile.open("Hash Program Output.txt");

// Print heading------------------------------------------------------------------------------------------------
    cout << setw(30) << "Name" << setw(15) << "Phone No." << setw(8) << "Key" << "\n" << endl;
    outfile << setw(30) << "Name" << setw(15) << "Phone No." << setw(8) << "Key" << "\n" << endl;

// Read input file, create key & insert in hash table-----------------------------------------------------------
    infile >> s;
    int count = 0; // index of nameArray
    while(infile)
    {
        string forName, forPhone;
            while( !(isdigit(s[0])) )
            {
                forName = forName + " " + s;
                infile >> s;
            }
            forPhone = s;
            nameArray[count] = forName;
            count++;
            hashKey = createHkey(forName);

            hashTable[hashKey].key = hashKey;
            insert(hashTable[hashKey].head, forPhone);

            cout << setw(30) << forName << setw(15) << forPhone << setw(8) << hashKey << endl;
            outfile << setw(30) << forName << setw(15) << forPhone << setw(8) << hashKey << endl;

            infile >> s;
    }

//Print hash table-----------------------------------------------------------------------------------------
     cout << "\n                Hash Table\n                ----------\n" << endl;
     outfile << "\n                 Hash Table\n                ------------\n" << endl;
    for(int i=0; i<79; i++)
    {
        cout << " index:" << setw(4) << i << "    Key:" << setw(4) << hashTable[i].key << "  Data:";
        outfile << " index:" << setw(4) << i << "    Key:" << setw(4) << hashTable[i].key << "  Data:";
        printNode(hashTable[i].head);
    }

// Print collisions------------------------------------------------------------------------------------------
    cout << "\n\n Collisions: " << collision << endl;
    outfile << "\n\n Collisions: " << collision << endl;

    for (int i=0; i<2; i++)
    {
    // get input for searching----------------------------------------------------------------------------------
        cout << "\n Enter name: ";
        outfile << "\n Enter name: ";
        getline(cin,name);
        hashKey = createHkey(" "+name); // names have space int the beginning

    // Find correct node in linked list---------------------------------------------------------------------------
        int nodeNumber = 0;
        bool found = false;
        for(int i=0; i<79; i++)
        {
            if( createHkey(nameArray[i]) == hashKey)
            {
                nodeNumber++;
            }
            if(nameArray[i] == " "+name)
            {
                found = true;
                break;
            }
        }

    // Search--------------------------------------------------------------

        outfile << name << endl;
        cout << "\n Key:" << hashTable[hashKey].key << "\n data: ";
        outfile << "\n Key:" << hashTable[hashKey].key << "\n data: ";
            printOneNode(hashTable[hashKey].head, nodeNumber, found);
    }

    cout << "\n" << endl;
    infile.close();
    outfile.close();
    return 0;
}
