#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll(){
    SortedMap sm(relatie1);
    assert(sm.size() == 0);
    assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
        TElem e = it.getCurrent();
        assert(e.second != NULL_TVALUE);
        it.next();
    }
    assert(sm.remove(1) == 3);
    assert(sm.isEmpty());


    assert(sm.getKeyRange() == -1); // map gol

    sm.add(10, 100);
    sm.add(3, 200);
    sm.add(25, 300);
    sm.add(7, 400);
    assert(sm.getKeyRange() == 22); // max 25 - min 3

    sm.add(-5, 500);
    assert(sm.getKeyRange() == 30); // max 25 - min -5

    sm.remove(25);
    assert(sm.getKeyRange() == 15); // max 10 - min -5

    sm.remove(10);
    sm.remove(7);
    sm.remove(3);
    sm.remove(-5);
    assert(sm.getKeyRange() == -1);
}

