#include <iostream>
#include "cc.h"

using namespace std;

int main(){
   cout << "Ejecutando programa CCP" << endl;
   //par.mostrar_datos();
   std::srand((unsigned) 15091999);
   Set_random(15091999);
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(20061999);
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(19031999);
   for(int i = 0; i < 5; i++){
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
}
