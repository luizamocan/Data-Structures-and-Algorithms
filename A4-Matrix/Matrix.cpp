#include "Matrix.h"
#include <exception>
using namespace std;

//best/worst/total- Θ(capacity)
Matrix::Matrix(int nrLines, int nrCols): nrRows(nrLines), nrCols(nrCols) ,capacity(13),size(0){
	elements=new Triple[capacity];
	flags=new int[capacity];
	for(int i=0;i<capacity;i++) {
		flags[i]=0;
	}
}

//best/worst/total- Θ(1)
Matrix::~Matrix() {
	delete[] elements;
	delete[] flags;
}

//best/worst/total- Θ(1)
int Matrix::nrLines() const {
	return nrRows;
}

//best/worst/total- Θ(1)
int Matrix::nrColumns() const {
	return nrCols;
}

//best/worst/total- Θ(1)
int Matrix::hash(int row, int col, int i) const {
	int key=row*nrCols+col;
	return (key+i*i) % capacity;
}


//best case- Θ(n): every element reinserts in the new array in the first probe
//worst case-Θ(n* capacity): all n elements hash to the same position and must probe many times
//total- O(n* capacity)
void Matrix::resizeAndHash() {
	int oldCap = capacity;
	Triple* oldElems = elements;
	int* oldFlags = flags;

	capacity *= 2;
	elements = new Triple[capacity];
	flags = new int[capacity];
	for (int i = 0; i < capacity; ++i)
		flags[i] = 0;
	size = 0;

	for (int i = 0; i < oldCap; i++) {
		if (oldFlags[i] == 1) {
			insert(oldElems[i].row, oldElems[i].col, oldElems[i].value);
		}
	}

	delete[] oldElems;
	delete[] oldFlags;
}

//best case-Θ(1): first element
//worst case-Θ(capacity): last element or not found
//total: O(capacity)
TElem Matrix::search(int row, int col) const {
	for (int k = 0; k < capacity; k++) {
		int pos = hash(row, col, k);
		if (flags[pos] == 0) return NULL_TELEM;
		if (flags[pos] == 1 && elements[pos].row == row && elements[pos].col == col)
			return elements[pos].value;
	}
	return NULL_TELEM;
}


//best case-Θ(1)
//worst case-Θ(capacity)
//total-O(capacity)
TElem Matrix::insert(int row, int col, TElem val) {
	for (int k = 0; k < capacity; k++) {
		int pos = hash(row, col, k);
		if (flags[pos] == 0 || flags[pos] == 2) {
			elements[pos] = Triple(row, col, val);
			flags[pos] = 1;
			size++;
			if ((double)size / capacity > alpha)
				resizeAndHash();
			return NULL_TELEM;
		}
		if (flags[pos] == 1 && elements[pos].row == row && elements[pos].col == col) {
			TElem old = elements[pos].value;
			elements[pos].value = val;
			return old;
		}
	}
	throw exception();
}


//best case-Θ(1)
//worst case-Θ(capacity)
//total-O(capacity)
TElem Matrix::remove(int row, int col) {
	for (int k = 0; k < capacity; k++) {
		int pos = hash(row, col, k);
		if (flags[pos] == 0) return NULL_TELEM;
		if (flags[pos] == 1 && elements[pos].row == row && elements[pos].col == col) {
			TElem old = elements[pos].value;
			flags[pos] = 2;
			size--;
			return old;
		}
	}
	return NULL_TELEM;
}

//best case-Θ(1): first element
//worst case-Θ(capacity): last element or not found
//total: O(capacity)
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= nrRows || j < 0 || j >= nrCols)
		throw exception();
	return search(i, j);
}

//best case-Θ(1)
//worst case-Θ(capacity)
//total-O(capacity)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= nrRows || j < 0 || j >= nrCols)
		throw exception();

	if (e == NULL_TELEM) {
		return remove(i, j);
	} else {
		return insert(i, j, e);
	}
}

//best case-Θ(n)
//worst case-Θ(n*capacity)
//total-O(n*capacity)
void Matrix::transpose() {
	Triple* oldElements = elements;
	int* oldFlags = flags;
	int oldCapacity = capacity;


	std::swap(nrRows, nrCols);


	elements = new Triple[capacity];
	flags = new int[capacity];
	for (int i = 0; i < capacity; ++i)
		flags[i] = 0;

	size = 0;

	for (int i = 0; i < oldCapacity; ++i) {
		if (oldFlags[i] == 1) {
			insert(oldElements[i].col, oldElements[i].row, oldElements[i].value);
		}
	}

	delete[] oldElements;
	delete[] oldFlags;
}
