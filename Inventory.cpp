#include <utility>
#include "Inventory.h"

// Allow the compiler to define the remaining
// comparison operators
using namespace std::rel_ops;

//------------------------------------------------------------------------------
Inventory::Node::Node()
    :data(Item(0, "Air"), 0)
{
    this->next = nullptr;
}

//------------------------------------------------------------------------------
Inventory::Node::Node(ItemStack s)
    :data(s)
{
    this->next = nullptr;
}

//------------------------------------------------------------------------------
Inventory::Inventory()
{
    this->head     = nullptr;
    this->tail     = nullptr;
    this->slots    = 10;
    this->occupied = 0;

    //std::cerr << Node().data << "\n";
}

//------------------------------------------------------------------------------
Inventory::Inventory(int n)
{
    this->head     = nullptr;
    this->tail     = nullptr;
    this->slots    = n;
    this->occupied = 0;
}

//------------------------------------------------------------------------------
Inventory::Inventory(const Inventory &src){
    this->head = nullptr;
    this->tail = nullptr;
    this->slots = src.slots;
    this->occupied = 0;
   
   Node *srcItr = src.head;

   while(srcItr != nullptr){
        this->addItems(srcItr->data);

   srcItr = srcItr->next;
   }
}

//------------------------------------------------------------------------------
Inventory::~Inventory(){

    Node *currentItr = nullptr;
    Node *toDelete = nullptr;

    currentItr = this->head;

    while(currentItr != nullptr){
        toDelete = currentItr;

        currentItr = currentItr->next;
        delete toDelete;
        toDelete = nullptr; 
    }

    head = nullptr;
    tail = nullptr;
    //slots = 0;
    occupied = 0;
 }

//------------------------------------------------------------------------------
bool Inventory::isFull() const
{
    // @todo implement this function
    //
    // If this is more than one line
    // in the form "return (boolean expression);"
    // you are overthinking the problem

    //return true; // This line is a placeholder. Remove it.
     return occupied == slots; 

}

//------------------------------------------------------------------------------
void Inventory::display(std::ostream &outs) const
{
    outs << " -Used " << occupied << " of " << slots << " slots" << "\n";

    Node* it = head;
    while(it != nullptr){
        outs << "  " << it->data << "\n";

        it = it->next;
    }
}

//------------------------------------------------------------------------------
Inventory& Inventory::operator=(Inventory rhs)
{
    std::swap(*this, rhs);
    return *this;
}

//------------------------------------------------------------------------------
void swap(Inventory& lhs, Inventory& rhs)
{
    using std::swap;

    swap(lhs.head, rhs.head);
    swap(lhs.tail, rhs.tail);
    swap(lhs.slots, rhs.slots);
    swap(lhs.occupied, rhs.occupied);
}

//------------------------------------------------------------------------------
Inventory::Node* Inventory::findMatchingItemStackNode(const ItemStack& itemStack){

    Node *current = head;

    while(current != nullptr){
        if(current->data == itemStack){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//------------------------------------------------------------------------------
void Inventory::mergeStacks(ItemStack& lhs, const ItemStack& rhs){
    // Update lhs... remember rhs is read only
    lhs.addItems(rhs.size());
}

//------------------------------------------------------------------------------
void Inventory::addItemStackNoCheck(ItemStack itemStack){

    Node *newNode = nullptr;
    newNode = new Node(itemStack);

    if(this->occupied == 0){
        this->head = newNode;
        this->tail = newNode;
    } else{
        (this->tail)->next = newNode;
        this->tail = newNode;
    }
    this->occupied++;
}
