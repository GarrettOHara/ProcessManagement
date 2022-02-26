#include <iostream>
#include "filea.h"
#include "fileb.h"

using namespace std;

int main(){
    filea a;
    fileb b;

    cout << a.add(3,3) << endl;

    cout << b.sub(3,3) << endl;
}