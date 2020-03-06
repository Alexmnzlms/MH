#include <iostream>
#include <ctime>
#include "cc.h"

using namespace std;

int main(){
   cout << "Ejecutando programa CCP" << endl;
   //par.mostrar_datos();
   Set_random(20061999);
   cout << "Rand_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(20061999);
   cout << "Rand_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/rand_set.dat","data/rand_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(03032020);
   cout << "Iris_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(03032020);
   cout << "Iris_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(3,"data/iris_set.dat","data/iris_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
   Set_random(1583493671);
   cout << "Ecoli_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }

   Set_random(987563214569);
   cout << "Ecoli_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.greedy();
      par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }*/

   /*bool salir = false;
   bool fallo = false;
   int n;
   unsigned seed;
   while(!salir){
      seed = std::time(0);
      Set_random(seed);
      cout << "Seed: " << seed << endl;
      //cout << "Ecoli_set 10%" << endl;
      fallo = false;
      for(int i = 0; i < 5 && !fallo; i++){
         CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
         //par.mostrar_datos();
         //cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
         n = par.greedy();
         if(n >= 1000){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << endl;
         }
         //par.mostrar_solucion(0);
         //cout << "-------------------------------------------------------" << endl;
      }
      if(!fallo){
         salir = true;
      }
   }*/

   Set_random(20061999);
   cout << "Rand_set 10%" << endl;
   for(int i = 0; i < 1; i++){
      CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      par.busqueda_local();
      //par.mostrar_solucion(0);
      cout << "-------------------------------------------------------" << endl;
   }
}
