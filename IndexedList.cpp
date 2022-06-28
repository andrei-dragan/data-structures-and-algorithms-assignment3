#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

using namespace std;

IndexedList::SLLNode::SLLNode(TElem e, PNode n) {
    this->info = e;
    this->next = n;
} // Theta(1)

IndexedList::IndexedList() {
    this->head = nullptr;
} // Theta(1)

int IndexedList::size() const {
    int size = 0;
    PNode node = this->head;

    while (node != nullptr) {
        size++;
        node = node->next;
    }

	return size;
} // Theta(n)


bool IndexedList::isEmpty() const {
    if (this->head == nullptr)
        return true;
	return false;
} // Theta(1)

TElem IndexedList::getElement(int pos) const {
    if (pos < 0)
        throw exception();

    int index = 0;
    PNode node = this->head;

    while (node != nullptr && index != pos) {
        index++;
        node = node->next;
    }

    if (node == nullptr)
        throw exception();

    return node->info;
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)

TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0)
        throw exception();
    
    int index = 0;
    PNode node = this->head;

    while (node != nullptr && index != pos) {
        index++;
        node = node->next;
    }

    if (node == nullptr)
        throw exception();

    TElem oldE = node->info;
    node->info = e;
    return oldE;

} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)

void IndexedList::addToEnd(TElem e) {
    if (this->head == nullptr) {
        this->head = new SLLNode(e, nullptr);
        return;
    }

    PNode node = this->head;
    while (node->next != nullptr)
        node = node->next;
    
    PNode newNode = new SLLNode(e, nullptr);
    node->next = newNode;
} // Theta(n)

void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0)
        throw exception();
    else if (pos == 0) {
        PNode newNode = new SLLNode(e, nullptr);
        newNode->next = this->head;
        this->head = newNode;
        return;
    }
    else {
        PNode node = this->head;
        int index = 0;
        
        while (node != nullptr && index != pos - 1) {
            node = node->next;
            index++;
        }

        if (node == nullptr)
            throw exception();

        PNode newNode = new SLLNode(e, nullptr);
        newNode->next = node->next;
        node->next = newNode;
    }
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)

TElem IndexedList::remove(int pos) {
    if (pos < 0)
        throw exception();
    else if (pos == 0) {
        if (this->head == nullptr)
            throw exception();

        PNode deletedNode = this->head;
        TElem removedE = deletedNode->info;
        
        this->head = this->head->next;
        delete deletedNode;

        return removedE;
    }
    else {
        int index = 0;
        PNode node = this->head;
        while (node->next != nullptr && index != pos - 1) {
            index++;
            node = node->next;
        }

        if (node->next == nullptr)
            throw exception();

        PNode deletedNode = node->next;
        TElem removedE = deletedNode->info;
        
        node->next = node->next->next;

        delete deletedNode;
        return removedE;
    }
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)

int IndexedList::search(TElem e) const {
    
    int index = 0;
    PNode node = this->head;

    while (node != nullptr) {
        if (node->info == e)
            return index;

        index++;
        node = node->next;
    }

	return -1;
} // Best Case: Theta(1), Worst Case: Theta(n) => Total: O(n)

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
} // Theta(1)

IndexedList::~IndexedList() {
    while (this->head != nullptr) {
        PNode nodeToDestroy = this->head;
        this->head = this->head->next;
        delete nodeToDestroy;
    }
} // Theta(n)

int IndexedList::removeFromKtoK(int k) {
    if (k <= 0)
        throw exception();

    int removedElements = 0;
    if (this->head == NULL)
        return removedElements;
   
    if (k == 1) {
        while (this->head != NULL) {
            PNode nodeToDelete = this->head;
            this->head = this->head->next;
            delete nodeToDelete;
            removedElements++;
        }
        return removedElements;
    }

    PNode node = this->head;
    int index = 0;
    while (node != NULL && node->next != NULL) {
        if (((index + 1) + 1) % k == 0) {
            PNode nodeToDelete = node->next;
            node->next = node->next->next;
            removedElements++;
            index++;
            delete nodeToDelete;
        }
        node = node->next;
        index++;
    }
    return removedElements;
} // Theta(n)