#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;
//best/worst/total-Θ(1)
SMIterator::SMIterator(const SortedMap& m) : map(m){
    stackCapacity = map.size()+10;
    stack=new int[stackCapacity];
    stackTop=-1;
    currentNode=-1;
    first();
}
//best-Θ(1)
//worst-Θ(n)
//total-O( n)
void SMIterator::first() {
    currentNode = map.root;
    stackTop = -1;

    while (currentNode != -1) {
        stack[++stackTop] = currentNode;
        currentNode = map.nodes[currentNode].left;
    }

    if (stackTop != -1)
        currentNode = stack[stackTop];
    else
        currentNode = -1;
}
//best-Θ(1)
//worst-Θ(n)
//total-O(n)
void SMIterator::next(){
    if (!valid())
        throw exception();
    int node=stack[stackTop--]; //pop current node
    int rightChild=map.nodes[node].right;
    while (rightChild!=-1) {
        stack[++stackTop]=rightChild;
        rightChild=map.nodes[rightChild].left;
    }
    if (stackTop!=-1)
        currentNode=stack[stackTop];
    else
        currentNode=-1;
}
//best/total/worst-Θ(1)
bool SMIterator::valid() const{
    return currentNode!=-1;
}

//best/total/worst-Θ(1)
TElem SMIterator::getCurrent() const{
    if (!valid())
        throw exception();
    int node=currentNode;
    return {map.nodes[node].key,map.nodes[node].value};
}

//best/total/worst-Θ(1)
SMIterator::~SMIterator() {
    delete [] stack;
}
