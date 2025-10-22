#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

int main(){
    testAll();
    testJumpBackward();
    testAllExtended();
    cout<<"Finished LI Tests!"<<endl;
}