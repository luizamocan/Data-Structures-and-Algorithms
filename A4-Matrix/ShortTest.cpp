#include <cassert>
#include "Matrix.h"

using namespace std;

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    TElem old = m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);
    assert(old == 5);

    //tests for extra function
    Matrix tr(3, 3);
    tr.modify(0, 1, 10);
    tr.modify(1, 2, 20);
    tr.modify(2, 0, 30);

    tr.transpose();

    assert(tr.element(1, 0) == 10);
    assert(tr.element(2, 1) == 20);
    assert(tr.element(0, 2) == 30);

}