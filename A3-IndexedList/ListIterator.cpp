#include "ListIterator.h"
#include <stdexcept>

// Θ(1)
ListIterator::ListIterator(const IndexedList& l) : list(l), current(-1) {
    first();
}

// Θ(1)
void ListIterator::first() {
    current = list.head;
}

// Θ(1)
void ListIterator::next() {
    if (!valid())
        throw std::out_of_range("Invalid iterator");
    current = list.elements[current].next;
}

// Θ(1)
bool ListIterator::valid() const {
    return current != -1;
}

// Θ(1)
TElem ListIterator::getCurrent() const {
    if (!valid())
        throw std::out_of_range("Invalid iterator");
    return list.elements[current].data;
}

// Best case: Θ(k) (poziție aproape de început)
// Worst case: Θ(n) (poziție la final)
// Total: O(n)
void ListIterator::jumpBackward(int k) {
    if (!valid())
        throw std::out_of_range("Invalid iterator");
    if (k <= 0)
        throw std::invalid_argument("k must be positive");

    int index = list.head;
    int pos = 0;

    while (index != current && index != -1) {
        index = list.elements[index].next;
        pos++;
    }

    if (index == -1 || pos < k) {
        current = -1;
    } else {
        current = list.head;
        for (int i = 0; i < pos - k; ++i)
            current = list.elements[current].next;
    }
}
