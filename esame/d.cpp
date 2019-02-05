#include <iostream>
#include "data.h"

int main(){
    data * d = new data(13,04,2000);
    data * e = new data(13,04,2000);
    if (d->valida())
        d->stampa();
    if (d->Bisestile())
        std::cout<< "Bisestile!";
    if(*e<*d)
        std::cout << "minore";
}
