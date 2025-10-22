#include "SetIterator.h"

#include <exception>

#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m)
{	//best.worst/average case -Θ(1)
    currentNode=set.head;
}


void SetIterator::first() {
    //best.worst/average case -Θ(1)
    currentNode=set.head;
}


void SetIterator::next() {
    //best.worst/average case -Θ(1)
    if (!valid())
        throw std::exception();
    currentNode=currentNode->next;
}


TElem SetIterator::getCurrent()
{	//best.worst/average case -Θ(1)
    if (!valid())
        throw std::exception();
    return currentNode->data;

}

bool SetIterator::valid() const {
    //best.worst/average case -Θ(1)
    return currentNode!=nullptr;
}



