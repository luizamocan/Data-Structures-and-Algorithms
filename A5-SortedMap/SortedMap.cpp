#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;
//best/worst/total-Θ(n)
SortedMap::SortedMap(Relation r) {
	this->capacity=10;
	this->nodes=new Node[capacity];
	for(int i=0;i<capacity-1;i++) {
		nodes[i].left=i+1;
	}
	nodes[capacity-1].left=-1;
	this->firstEmpty=0;
	this->root=-1;
	this->length=0;
	this->rel=r;
}

//best/worst/total-Θ(n)
void SortedMap::resize() {
	int newCapacity = capacity * 2;
	Node* newNodes = new Node[newCapacity];
	for (int i = 0; i < capacity; ++i)
		newNodes[i] = nodes[i];

	for (int i = capacity; i < newCapacity - 1; ++i)
		newNodes[i].left = i + 1;
	newNodes[newCapacity - 1].left = -1;

	firstEmpty = capacity;
	capacity = newCapacity;
	delete[] nodes;
	nodes = newNodes;
}

//best-Θ(1)
//worst-Θ(n) resize needed
//total-O(n)
int SortedMap::allocate() {
	if (firstEmpty == -1)
		resize();
	int pos = firstEmpty;
	firstEmpty = nodes[firstEmpty].left;
	return pos;

}

//best/worst/total-Θ(1)
void SortedMap::deallocate(int pos) {
	nodes[pos].left = firstEmpty;
	firstEmpty = pos;
}

//best-Θ(1)
//worst-Θ(n)
//total-O(n)
int SortedMap::findMin(int node) const {
	while (nodes[node].left != -1)
		node = nodes[node].left;
	return node;
}

//best-Θ(1)
//worst-Θ(n)
//total-O(n)
int SortedMap::removeRec(int node, TKey k, TValue &removed) {
	if (node == -1)
		return -1;

	if (nodes[node].key == k) {
		removed = nodes[node].value;
		if (nodes[node].left == -1 && nodes[node].right == -1) {
			deallocate(node);
			return -1;
		}
		else if (nodes[node].left == -1) {
			int right = nodes[node].right;
			deallocate(node);
			return right;
		}
		else if (nodes[node].right == -1) {
			int left = nodes[node].left;
			deallocate(node);
			return left;
		}
		else {
			int minRight = findMin(nodes[node].right);
			nodes[node].key = nodes[minRight].key;
			nodes[node].value = nodes[minRight].value;
			nodes[node].right = removeRec(nodes[node].right, nodes[minRight].key, removed);
			return node;
		}
	}

	if (rel(k, nodes[node].key))
		nodes[node].left = removeRec(nodes[node].left, k, removed);
	else
		nodes[node].right = removeRec(nodes[node].right, k, removed);

	return node;
}

//best-Θ(1)
//worst-Θ(n)
//total-O(n)
TValue SortedMap::add(TKey k, TValue v) {
	if (root == -1) {
		int newPos = allocate();
		nodes[newPos] = {k, v, -1, -1};
		root = newPos;
		length++;
		return NULL_TVALUE;
	}

	int current = root;
	int parent = -1;
	while (current != -1) {
		if (nodes[current].key == k) {
			TValue old = nodes[current].value;
			nodes[current].value = v;
			return old;
		}
		parent = current;
		if (rel(k, nodes[current].key))
			current = nodes[current].left;
		else
			current = nodes[current].right;
	}

	int newPos = allocate();
	nodes[newPos] = {k, v, -1, -1};
	if (rel(k, nodes[parent].key))
		nodes[parent].left = newPos;
	else
		nodes[parent].right = newPos;

	length++;
	return NULL_TVALUE;
}
//best-Θ(1)
//worst-Θ(n)
//total-O( n)
TValue SortedMap::search(TKey k) const {
	int current = root;
	while (current != -1) {
		if (nodes[current].key == k)
			return nodes[current].value;
		if (rel(k, nodes[current].key))
			current = nodes[current].left;
		else
			current = nodes[current].right;
	}
	return NULL_TVALUE;
}

//best-Θ(1)
//worst-Θ(n)
//total-O( n)
TValue SortedMap::remove(TKey k) {
	TValue removed = NULL_TVALUE;
	root = removeRec(root, k, removed);
	if (removed != NULL_TVALUE)
		length--;
	return removed;
}
//best/worst/total-Θ(1)
int SortedMap::size() const {
	return this->length;
}
//best/worst/total-Θ(1)
bool SortedMap::isEmpty() const {
	return this->length==0;
}

//best/worst/total-Θ(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

//best/worst/total-Θ(1)
SortedMap::~SortedMap() {
	delete []nodes;
}

//best case-Θ(1)
//worst case-Θ(n)
//total-O(n)
int SortedMap::getKeyRange() const {
	if (isEmpty())
		return -1;

	int minNode = root;
	while (nodes[minNode].left != -1)
		minNode = nodes[minNode].left;
	int minKey = nodes[minNode].key;

	int maxNode = root;
	while (nodes[maxNode].right != -1)
		maxNode = nodes[maxNode].right;
	int maxKey = nodes[maxNode].key;

	return maxKey - minKey;
}

