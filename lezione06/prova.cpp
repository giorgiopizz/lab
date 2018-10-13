//prova.cpp

#include <iostream>
using namespace std;
int numero(){
        int* ciao=new int(20);
        return *ciao;
}

int main() {
        cout << numero();
}
