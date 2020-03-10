#include <iostream>
#include <ctime>
#include "cc.h"

using namespace std;

int main(){
   unsigned long tini, tfin;
   cout << "Ejecutando programa CCP" << endl;

   Set_random(1583493671);
   cout << "Ecoli_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << 1000.0*(tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }

   Set_random(987563214569);
   cout << "Ecoli_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << 1000.0*(tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
}
