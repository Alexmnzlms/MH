#include <iostream>
#include <ctime>
#include "cc.h"

using namespace std;

int main(){
   unsigned long tini, tfin;
   unsigned long semillas [5] = {1584564489,1584564539,1584564569,1584564602,1584564643};
   cout << "Ejecutando programa CCP" << endl;
/*
   cout << "Rand_set 10%" << endl;
   for(int i = 0; i < 5; i++){
      Set_random(semillas[i]);
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
   */

   bool salir = false;
   bool fallo = false;
   int n;
   int n_max = 100;
   unsigned seed;
   while(!salir){
      seed = std::time(0);
      Set_random(seed);
      cout << "Seed: " << seed << endl;
      //cout << "Ecoli_set 10%" << endl;
      fallo = false;
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/rand_set.dat","data/rand_set_const_10.const");
         //par.mostrar_datos();
         //cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de rand 10%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de rand 10%" << endl;
         }
         //par.mostrar_solucion();
         //cout << "-------------------------------------------------------" << endl;
      }
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/rand_set.dat","data/rand_set_const_20.const");
         //par.mostrar_datos();
         //cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de rand 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de rand 20%" << endl;
         }
         //par.mostrar_solucion();
         //cout << "-------------------------------------------------------" << endl;
      }
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/iris_set.dat","data/iris_set_const_10.const");
         //par.mostrar_datos();
         //cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de iris 10%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de iris 10%" << endl;
         }
         //par.mostrar_solucion();
         //cout << "-------------------------------------------------------" << endl;
      }
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/iris_set.dat","data/iris_set_const_20.const");
         //par.mostrar_datos();
         //cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de iris 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de iris 20%" << endl;
         }
         //par.mostrar_solucion();
         //cout << "-------------------------------------------------------" << endl;
      }
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_10.const");
         //par.mostrar_datos();
         //cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de ecoli 10%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de ecoli 10%" << endl;
         }
         //par.mostrar_solucion();
         //cout << "-------------------------------------------------------" << endl;
      }
      for(int i = 0; i < 5 && !fallo; i++){
         CCP par(1,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
         //par.mostrar_datos();
         //cout << "-------------------Iteracion: " << i+1 << "--------------------" << endl;
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de ecoli 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de ecoli 20%" << endl;
         }
         //par.mostrar_solucion();
         //cout << "-------------------------------------------------------" << endl;
      }
      if(!fallo){
         salir = true;
      }
   }

}
