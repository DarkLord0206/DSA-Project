1
#include <iostream>
    2 using namespace std;
3 4 class DLinkedList;
5 6 typedef int DataType;
// list element type
7 class DNode
{
    // doubly linked list node
    8 private : 9 DataType elem;
    // node element value
    10 DNode *prev;
    // previous node in list
    11 DNode *next;
    // next node in list
    12 friend class DLinkedList;
    // allow DLinkedList access
    13
};
14 15 class DLinkedList
{
    // doubly linked list
    16 public : 17 DLinkedList();
    // constructor
    18 ~DLinkedList();
    // destructor
    19 bool empty() const;
    // is list empty?
    20 const DataType &front() const;
    // get front element
    21 const DataType &back() const;
    // get back element
    22 void addFront(const DataType &e);
    // add to front of list
    23 void addBack(const DataType &e);
    // add to back of list
    24 void removeFront();
    // remove from front
    25 void removeBack();
    // remove from back
    26 void listReverse();
    // reverse the list
    27 private :
        // local type definitions
        28 DNode *header;
    // list sentinels
    29 DNode *trailer;
    30 protected :
        // local utilities
        31 void
        add(DNode *v, const DataType &e);
    // insert new node before v
    32 void remove(DNode *v);
    // remove node v
    33
};
34 35 DLinkedList::DLinkedList()
{
    // constructor
    36 header = new DNode;
    // create sentinels
    37 trailer = new DNode;
    38 header->next = trailer;
    // have them point to each other
    39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 trailer->prev = header;
}
DLinkedList::~DLinkedList()
{
    while (!empty())
        removeFront();
    delete header;
    delete trailer;
}
bool DLinkedList::empty() const
{
    return (header->next == trailer);
}
const DataType &DLinkedList::front() const
{
    return header->next->elem;
}
const DataType &DLinkedList::back() const
{
    return trailer->prev->elem;
}
void DLinkedList::add(DNode* v, const DataType&DNode* u = new DNode;
u->elem = e;
u->next = v->next;
u->prev = v;
v->next->prev = u;
v->next = u;
}
void DLinkedList::addFront(const DataType &e)
{
    add(header, e);
}
void DLinkedList::addBack(const DataType &e)
{
    add(trailer->prev, e);
}
void DLinkedList::remove(DNode *v)
{
    DNode *u = v->prev;
    DNode *w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}
void DLinkedList::removeFront()
{
    remove(header->next);
}
void DLinkedList::removeBack()
{
    remove(trailer->prev);
}
// destructor
// remove all but sentinels
// remove the sentinels
// is list empty?
// get front element
// get back element
e)
{
    // insert new node before v
    // create a new node for e
    // link u in between v
    // add to front of list
    // add to back of list
    // remove node v
    // predecessor
    // successor
    // unlink v from list
    // remove from font
    // remove from back
    5 87 void DLinkedList::listReverse()
    {
        // reverse a list
        88 DLinkedList T;
        // temporary list
        89 while (!this->empty())
        {
            // reverse L into T
            90 int s = this->front();
            this->removeFront();
            91 T.addFront(s);
            92
        }
        93 while (!T.empty())
        {
            // copy T back to L
            94 int s = T.front();
            T.removeFront();
            95 this->addBack(s);
            96
        }
        97
    }
    98 99 typedef int DataType;
    // deque element type
    100 class LinkedDeque
    {
        // deque as doubly linked list
        101 public : 102 LinkedDeque();
        // constructor
        103 int size() const;
        // number of items in the deque
        104 bool empty() const;
        // is the deque empty?
        105 const DataType &front();
        // the first element
        106 const DataType &back();
        // the last element
        107 void insertFront(const DataType &e);
        // insert new first element
        108 void insertBack(const DataType &e);
        // insert new last element
        109 void removeFront();
        // remove first element
        110 void removeBack();
        // remove last element
        111 private :
            // member data
            112 DLinkedList D;
        // linked list of elements
        113 int n;
        // number of elements
        114
    };
    115 116
        // Another way to initialize values in a constructor. The brackets next to the variable
        117
        // signify the value that it gets initialized to.
        118 LinkedDeque::LinkedDeque() : D(), n(0)
    {
    }
    119 120 void LinkedDeque::insertFront(const DataType &e)
    {
        121 D.addFront(e);
        122 n++;
        123
    }
    124 125 void LinkedDeque::insertBack(const DataType &e)
    {
        // insert new last element
        126 D.addBack(e);
        127 n++;
        128
    }
    129 130 void LinkedDeque::removeFront()
    {
        // remove first element
        131 if (empty()) 132 cout << "removeFront of empty deque\n";
        133 else
        {
            134 D.removeFront();
            6 135 n--;
            136
        }
        137
    }
    138 139 void LinkedDeque::removeBack()
    {
        // remove last element
        140 if (empty()) cout << "removeBack of empty deque\n";
        141 else
        {
            142 D.removeBack();
            143 n--;
            144
        }
        145
    }
    146 147 int LinkedDeque::size() const
    {
        148 return n;
        149
    }
    150 151 bool LinkedDeque::empty() const
    {
        152 return n == 0;
        153
    }
    154 155 const DataType &LinkedDeque::front()
    {
        // get the front element
        156 if (empty()) 157 cout << "front of empty queue\n";
        158 return D.front();
        // list front is queue front
        159
    }
    160 161 const DataType &LinkedDeque::back()
    {
        // get the back element
        162 if (empty()) cout << "back of empty queue\n";
        163 return D.back();
        // list front is queue front
        164
    }