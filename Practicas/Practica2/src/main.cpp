#include <iostream>
#include <ctime>
#include "cc.h"

using namespace std;

void buscar_semilla(){
   bool salir = false;
   bool fallo = false;
   int n;
   int n_max = 100;
   unsigned seed;
   while(!salir){
      seed = std::time(0);
      Set_random(seed);
      cout << "Seed: " << seed << endl;
      fallo = false;
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/rand_set.dat","data/rand_set_const_10.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de rand 10%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de rand 10%" << endl;
         }
      }
      Set_random(seed);
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/rand_set.dat","data/rand_set_const_20.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de rand 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de rand 20%" << endl;
         }
      }
      Set_random(seed);
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/iris_set.dat","data/iris_set_const_10.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de iris 10%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de iris 10%" << endl;
         }
      }
      Set_random(seed);
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/iris_set.dat","data/iris_set_const_20.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de iris 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de iris 20%" << endl;
         }
      }
      Set_random(seed);
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de ecoli 10%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de ecoli 10%" << endl;
         }
      }
      Set_random(seed);
      for(int i = 0; i < 5 && !fallo; i++){
         CCP par(1,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de ecoli 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de ecoli 20%" << endl;
         }
      }
      if(!fallo){
         salir = true;
      }
   }
}

int main(){
   unsigned long tini, tfin;
   double semillas [5] = {1584565171,1584764782,1584565259,1584564539,1522565615};
   cout << "Ejecutando programa CCP" << endl;

   cout << "Rand_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Rand_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/rand_set.dat","data/rand_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Iris_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Iris_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/iris_set.dat","data/iris_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Ecoli_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }

   cout << "Ecoli_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.greedy();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }

   cout << "Rand_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_local();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Rand_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/rand_set.dat","data/rand_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_local();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Iris_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_local();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Iris_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(3,"data/iris_set.dat","data/iris_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_local();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
   cout << "Ecoli_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_local();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }

   cout << "Ecoli_set 20%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
      cout << "Semilla: " << semillas[i] << endl;
      CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
      //par.mostrar_datos();
      cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
      tini= clock(); // Tiempo inicial
      par.busqueda_local();
      tfin= clock(); // Tiempo final
      cout << "--------------------T (ms.): " << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
      par.mostrar_solucion();
      cout << "-------------------------------------------------------" << endl;
   }
}
