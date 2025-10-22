#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	//best/worst.average complexity- Θ(1)
	head=nullptr;
	length=0;
}


bool Set::add(TElem elem) {
	//best case -element is the first in the search- Θ(1)
	//worst case -element is the last in the search- Θ(n)
	//average case- Θ(n)
	if (search(elem))
		return false;
	Node* newNode = new Node{elem, head};
	head = newNode;
	length++;
	return true;
}


bool Set::remove(TElem elem) {
	//best case -element is the first Θ(1)
	//average/worst case Θ(n)
	Node* current = head;
	Node* prev = nullptr;

	while (current != nullptr) {
		if (current->data == elem) {
			if (prev == nullptr) {
				head = current->next;
			} else {
				prev->next = current->next;
			}
			delete current;
			length--;
			return true;
		}
		prev = current;
		current = current->next;
	}
	return false; // Element not found
}

bool Set::search(TElem elem) const {
	//best case -element is the first in the search- Θ(1)
	//worst case -element is the last in the search- Θ(n)
	//average case- Θ(n)
	Node* current = head;
	while (current != nullptr) {
		if (current->data == elem) return true;
		current = current->next;
	}
	return false;
}


int Set::size() const {
	//best/worst/average case -Θ(1)
	return length;
}


bool Set::isEmpty() const {
	//best/worst/average case -Θ(1)
	return length == 0;
}


Set::~Set() {
	//best/worst/average case - delete every node -Θ(n)
	Node* current = head;
	while (current != nullptr) {
		Node* toDelete=current;
		current = current->next;
		delete toDelete;
	}
}


SetIterator Set::iterator() const {
	//best/worst/average case - Θ(1)
	return SetIterator(*this);
}


void Set::intersection(const Set &s) {
	//best/worst/average Θ(n*m) , where n,m are the nr of elements in each set
	Node* current = head;
	Node* prev=nullptr;

	while (current != nullptr) {
		if (!s.search(current->data)) {
			Node* toDelete = current;
			if (prev == nullptr) {
				head = current->next;
				current = head;
			} else {
				prev->next = current->next;
				current = current->next;
			}
			delete toDelete;
			length--;
		} else {
			prev = current;
			current = current->next;
		}
	}
}


