#include <iostream>
#include "cc.h"

using namespace std;

int main(){
   cout << "Ejecutando programa CCP" << endl;
   CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
   par.mostrar_datos();
}
