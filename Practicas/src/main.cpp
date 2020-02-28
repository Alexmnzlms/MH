#include <iostream>
#include "cc.h"

using namespace std;

int main(){
   Set_random(20061999);
   cout << "Ejecutando programa CCP" << endl;
   //par.mostrar_datos();
   for(int i = 0; i < 200; i++){
      CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
      par.mostrar_datos();
      par.copkm();
      par.mostrar_solucion(0);
   }
}
