
#include <exception>
#include <cassert>
#include <iostream>
#include "ShortTest.h"
#include "IndexedList.h"
#include "ListIterator.h"



void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);
    assert(list.size() == 1);
    list.addToPosition(0,2);
    assert(list.size() == 2);
    ListIterator it = list.iterator();
    assert(it.valid());
    it.next();
    assert(it.getCurrent() == 1);
    it.first();
    assert(it.getCurrent() == 2);
    assert(list.search(1) == 1);
    assert(list.setElement(1,3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);
}


void testJumpBackward() {
    IndexedList list;
    for (int i = 1; i <= 10; ++i) {
        list.addToEnd(i * 10);  // List: 10, 20, ..., 100
    }

    ListIterator it = list.iterator();
    for (int i = 0; i < 5; i++) it.next();
    assert(it.getCurrent() == 60);

    it.jumpBackward(3);
    assert(it.valid());
    assert(it.getCurrent() == 30);

    it.jumpBackward(3);
    assert(!it.valid());


    std::cout << "All jumpBackward tests passed.\n";
}
