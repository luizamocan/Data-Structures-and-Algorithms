#include "Stack.h"
#include <exception>



using namespace std;
#define INITIAL_CAPACITY 10

Stack::Stack() {
    //best/worst/total O(1)
    this->capacity = INITIAL_CAPACITY;
    this->elements = new TElem[this->capacity];
    this->topIndex = -1;
}
void Stack::resize() {
    //best/worst O(n)-we need to copy all  the elements
    int newCapacity = this->capacity * 2;
    auto *newElements = new TElem[newCapacity];

    for (int i = 0; i < this->topIndex + 1; i++) {
        newElements[i] = this->elements[i];
    }
    delete[] this->elements; //free old memory
    this->elements = newElements;
    this->capacity = newCapacity;
}


void Stack::push(TElem e) {
    //best case O(1)
    //worst case O(n)-resize needed
    //average complexity O(1)
    if (this->topIndex  +1 == this->capacity ) {
        resize();
    }
    this->elements[++this->topIndex] = e;
}

TElem Stack::top() const {
    //best/worst/total O(1)-just return the top element
    if (this->isEmpty()) {
        throw exception();
    }
    return this->elements[this->topIndex];
}

TElem Stack::pop() {
    //best/worst/total O(1)-just decrement topIndex
    if (this->isEmpty()) {
        throw exception();
    }
    return this->elements[this->topIndex--];

}


bool Stack::isEmpty() const {
    //best/worst/total O(1)-just checks the topIndex
    return this->topIndex == -1;
}

Stack::~Stack() {
    //best/worst/total O(1)
    delete[] this->elements;
}
TElem Stack::popMinimum() {
    //best/worst/average O(n)
    if (this->isEmpty()) {
        throw exception();
    }
    int minIndex = 0;
    for (int i = 1; i <= this->topIndex; ++i) {
        if (this->elements[i] < this->elements[minIndex]) {
            minIndex = i;
        }
    }

    TElem minElement = this->elements[minIndex];
    for (int i = minIndex; i < this->topIndex; ++i) {
        this->elements[i] = this->elements[i + 1];
    }
    this->topIndex--;
    return minElement;


}
