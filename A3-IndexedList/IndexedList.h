#pragma once

typedef int TElem;
#define NULL_TELEM -11111

class ListIterator;

class IndexedList {
    friend class ListIterator;

private:
    struct SLLANode {
        TElem data;
        int next;
    };

    SLLANode* elements;
    int capacity;
    int head;
    int firstEmpty;
    int length;

    void resize();

public:
    IndexedList();

    int size() const;
    bool isEmpty() const;

    TElem getElement(int pos) const;
    TElem setElement(int pos, TElem e);

    void addToEnd(TElem e);
    void addToPosition(int pos, TElem e);

    TElem remove(int pos);

    int search(TElem e) const;

    ListIterator iterator() const;

    ~IndexedList();
};
