#pragma once
#include "IndexedList.h"

class ListIterator {
    friend class IndexedList;

private:
    const IndexedList& list;
    int current;

    ListIterator(const IndexedList& l);

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
    void jumpBackward(int k);
};
