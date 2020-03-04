#include <iostream>
#include "cc.h"

using namespace std;

int main(){
   cout << "Ejecutando programa CCP" << endl;
   //par.mostrar_datos();
   Set_random(20061999);
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(03032020);
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(987563214569);
   for(int i = 0; i < 5; i++){
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
}
