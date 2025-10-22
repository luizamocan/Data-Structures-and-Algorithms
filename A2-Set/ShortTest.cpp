#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"

void testAll() {
    Set s;
    assert(s.isEmpty() == true);
    assert(s.size() == 0);
    assert(s.add(5)==true);
    assert(s.add(1)==true);
    assert(s.add(10)==true);
    assert(s.add(7)==true);
    assert(s.add(1)==false);
    assert(s.add(10)==false);
    assert(s.add(-3)==true);
    assert(s.size() == 5);
    assert(s.search(10) == true);
    assert(s.search(16) == false);
    assert(s.remove(1) == true);
    assert(s.remove(6) == false);
    assert(s.size() == 4);


    SetIterator it = s.iterator();
    it.first();
    int sum = 0;
    while (it.valid()) {
        TElem e = it.getCurrent();
        sum += e;
        it.next();
    }
    assert(sum == 19);

    //test intersection
    Set a;
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    Set b;
    b.add(3);
    b.add(4);
    b.add(5);
    b.add(6);

    a.intersection(b);

    assert(a.size() == 2);
    assert(a.search(3) == true);
    assert(a.search(4) == true);
    assert(a.search(1) == false);
    assert(a.search(2) == false);

}

