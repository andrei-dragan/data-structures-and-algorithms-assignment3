#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const IndexedList& list) : list(list){
    this->currentElement = list.head;
} // Theta(1)

void ListIterator::first(){
    this->currentElement = this->list.head;
} // Theta(1)

void ListIterator::next(){
    if (!this->valid())
        throw exception();
    this->currentElement = this->currentElement->next;
} // Theta(1)

bool ListIterator::valid() const{
    return this->currentElement != nullptr;
} // Theta(1)

TElem ListIterator::getCurrent() const{
    if (!this->valid())
        throw exception();
    return this->currentElement->info;
} // Theta(1)