#include "IndexedList.h"
#include "ListIterator.h"
#include <stdexcept>

// Constructor
IndexedList::IndexedList() {
    capacity = 10;
    elements = new SLLANode[capacity];
    head = -1;
    firstEmpty = 0;
    length = 0;

    for (int i = 0; i < capacity - 1; i++) {
        elements[i].next = i + 1;
    }
    elements[capacity - 1].next = -1;
}

// resize - dublează capacitatea
// Best case: Θ(n)
// Worst case: Θ(n)
// Total: O(n)
void IndexedList::resize() {
    int newCapacity = capacity * 2;
    SLLANode* newElems = new SLLANode[newCapacity];

    for (int i = 0; i < capacity; i++) {
        newElems[i] = elements[i];
    }

    for (int i = capacity; i < newCapacity - 1; i++) {
        newElems[i].next = i + 1;
    }
    newElems[newCapacity - 1].next = -1;

    delete[] elements;
    elements = newElems;
    firstEmpty = capacity;
    capacity = newCapacity;
}

// Best/Worst/Total: Θ(1)
int IndexedList::size() const {
    return length;
}

// Best/Worst/Total: Θ(1)
bool IndexedList::isEmpty() const {
    return length == 0;
}

// Best case: Θ(1) (primul element)
// Worst case: Θ(n)
// Total: O(n)
TElem IndexedList::getElement(int pos) const {
    if (pos < 0 || pos >= length)
        throw std::out_of_range("Invalid position");

    int index = head;
    for (int i = 0; i < pos; i++)
        index = elements[index].next;

    return elements[index].data;
}

// Best case: Θ(1) (primul element)
// Worst case: Θ(n)
// Total: O(n)
TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0 || pos >= length)
        throw std::out_of_range("Invalid position");

    int index = head;
    for (int i = 0; i < pos; i++)
        index = elements[index].next;

    TElem old = elements[index].data;
    elements[index].data = e;
    return old;
}

// Best case: Θ(1) (listă goală sau doar un element)
// Worst case: Θ(n)
// Total: O(n)
void IndexedList::addToEnd(TElem e) {
    if (firstEmpty == -1)
        resize();

    int newIndex = firstEmpty;
    firstEmpty = elements[firstEmpty].next;

    elements[newIndex].data = e;
    elements[newIndex].next = -1;

    if (head == -1)
        head = newIndex;
    else {
        int current = head;
        while (elements[current].next != -1)
            current = elements[current].next;
        elements[current].next = newIndex;
    }

    length++;
}

// Best case: Θ(1) (inserare la început)
// Worst case: Θ(n)
// Total: O(n)
void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos > length)
        throw std::out_of_range("Invalid position");

    if (firstEmpty == -1)
        resize();

    int newIndex = firstEmpty;
    firstEmpty = elements[firstEmpty].next;

    elements[newIndex].data = e;

    if (pos == 0) {
        elements[newIndex].next = head;
        head = newIndex;
    } else {
        int prev = head;
        for (int i = 0; i < pos - 1; i++)
            prev = elements[prev].next;

        elements[newIndex].next = elements[prev].next;
        elements[prev].next = newIndex;
    }

    length++;
}

// Best case: Θ(1) (ștergere de la început)
// Worst case: Θ(n)
// Total: O(n)
TElem IndexedList::remove(int pos) {
    if (pos < 0 || pos >= length)
        throw std::out_of_range("Invalid position");

    int removed;
    if (pos == 0) {
        int toDelete = head;
        removed = elements[toDelete].data;
        head = elements[head].next;

        elements[toDelete].next = firstEmpty;
        firstEmpty = toDelete;
    } else {
        int prev = head;
        for (int i = 0; i < pos - 1; i++)
            prev = elements[prev].next;

        int toDelete = elements[prev].next;
        removed = elements[toDelete].data;
        elements[prev].next = elements[toDelete].next;

        elements[toDelete].next = firstEmpty;
        firstEmpty = toDelete;
    }

    length--;
    return removed;
}

// Best case: Θ(1) (primul element)
// Worst case: Θ(n) (nu se găsește)
// Total: O(n)
int IndexedList::search(TElem e) const {
    int current = head;
    int pos = 0;

    while (current != -1) {
        if (elements[current].data == e)
            return pos;
        current = elements[current].next;
        pos++;
    }

    return -1;
}

// Θ(1)
ListIterator IndexedList::iterator() const {
    return ListIterator(*this);
}

// Θ(1)
IndexedList::~IndexedList() {
    delete[] elements;
}
