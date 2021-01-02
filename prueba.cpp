#include <iostream>
#include <vector>
#include <stdlib.h>
#include <list>
using namespace std;


int main() {
    list<int> Solucion[10];
    Solucion[5] = 420;
    for(int i = 0; i < 10; i++) {
        cout << Solucion[i] << endl;
    }
    
    return 0;
}