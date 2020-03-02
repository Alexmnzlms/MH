#include <iostream>
#include "cc.h"

using namespace std;

int main(){
   cout << "Ejecutando programa CCP" << endl;
   //par.mostrar_datos();
   std::srand((unsigned) 15091999);
   Set_random(15091999);
   for(int i = 0; i < 1; i++){
      CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
      par.mostrar_datos();
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
}
