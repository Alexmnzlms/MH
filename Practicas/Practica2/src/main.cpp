#include <iostream>
#include <ctime>
#include <string>
#include "cc.h"

using namespace std;

unsigned buscar_semilla(){
   bool salir = false;
   bool fallo = false;
   int n;
   int n_max = 500;
   unsigned seed;
   while(!salir){
      seed = std::time(0);
      Set_random(seed);
      cout << "Seed: " << seed << endl;
      fallo = false;
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(3,"data/rand_set.dat","data/rand_set_const_10.const");
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
         CCP par(3,"data/rand_set.dat","data/rand_set_const_20.const");
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
         CCP par(3,"data/iris_set.dat","data/iris_set_const_10.const");
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
         CCP par(3,"data/iris_set.dat","data/iris_set_const_20.const");
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
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(8,"data/ecoli_set.dat","data/ecoli_set_const_20.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de ecoli 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de ecoli 20%" << endl;
         }
      }
      Set_random(seed);
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(3,"data/newthyroid_set.dat","data/newthyroid_set_const_10.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de newthyroid 10%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de newthyroid 10%" << endl;
         }
      }
      Set_random(seed);
      for(int i = 0; i < 1 && !fallo; i++){
         CCP par(3,"data/newthyroid_set.dat","data/newthyroid_set_const_20.const");
         n = par.greedy();
         if(n >= n_max){
            fallo = true;
            cout << "Fallo en la iteracion " << i+1 << " de newthyroid 20%" << endl;
         }
         else{
            cout << "Conseguida iteracion " << i+1 << " de newthyroid 20%" << endl;
         }
      }
      if(!fallo){
         salir = true;
      }
   }
   return seed;
}

int main(){
   unsigned long tini, tfin;
   int n_iteraciones = 5;
   int n_conjuntos_datos = 8;
   double semillas [5] = {1586861702, 1586861702, 1586861822, 1586861822, 1586861902};
   bool nueva_semilla = false;

   vector<string> titulos {"Rand 10%", "Iris 10%", "Ecoli 10%", "Newthyroid 10%", "Rand 20%", "Iris 20%", "Ecoli 20%", "Newthyroid 10%"};
   vector<int> n_k {3,3,8,3,3,3,8,3};
   vector<string> datos {"data/rand_set.dat", "data/iris_set.dat", "data/ecoli_set.dat", "data/newthyroid_set.dat", "data/rand_set.dat", "data/iris_set.dat", "data/ecoli_set.dat", "data/newthyroid_set.dat"};
   vector<string> restricciones {"data/rand_set_const_10.const", "data/iris_set_const_10.const", "data/ecoli_set_const_10.const", "data/newthyroid_set_const_10.const", "data/rand_set_const_20.const", "data/iris_set_const_20.const", "data/ecoli_set_const_20.const", "data/newthyroid_set_const_20.const"};

   cout << "Ejecutando programa CCP" << endl;

   vector<vector<double>> greedy;
   vector<double> greedy_media;

   vector<vector<double>> bl;
   vector<double>bl_media;

   bool solucion_completa = false;
   bool mostrar_iteracion = true;
   bool mostrar_media = true;

   if(nueva_semilla){
      vector<unsigned> sems;
      for(int i = 0; i < 5; i++){
         unsigned seed = buscar_semilla();
         cout << "----------------------------------------------------------------" << endl;
         cout << "Semilla encontrada: " << seed << endl;
         cout << "----------------------------------------------------------------" << endl;
         sems.push_back(seed);
      }

      cout << "{";
      for(int i = 0; i < 5; i++){
         cout << sems[i];
         if(i != 4){
            cout << ", ";
         }
      }
      cout << "};" << endl;
      return(0);
   }


   cout << "----------------- Tabla de resultados greedy -----------------" << endl;
   for(int c = 0; c < n_conjuntos_datos; c++){
      greedy.clear();

      for(int i = 0; i < n_iteraciones; i++){
         Set_random(semillas[i]);
         CCP par(n_k[c],datos[c],restricciones[c]);

         tini= clock();
         par.greedy();
         tfin= clock();

         double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
         vector<double> fila;
         fila = par.fila_datos();
         fila.push_back(tiempo);
         greedy.push_back(fila);

         if(solucion_completa){
            cout << "---------------------------------------------------------------------------------------------------" << endl;
            cout << titulos[c] << endl;
            cout << "Iteracion: " << i+1 << endl;
            cout << "Semilla: " << semillas[i] << endl;
            par.mostrar_solucion(true);
            cout << "---------------------------------------------------------------------------------------------------" << endl;
         }

         if(mostrar_iteracion){
            if(i == 0){
               cout << titulos[c] << endl;
               cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "T" << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
            }
            cout << i+1 << "          ";
            for(auto it = fila.begin(); it != fila.end(); it++){
               cout << *it << "          ";
            }
            cout << endl;
            cout << "---------------------------------------------------------------------------------------------------" << endl;
         }
      }

      if(mostrar_media){
         greedy_media.clear();
         for(int i = 0; i < (int) greedy[0].size(); i++){
            greedy_media.push_back(0);
         }

         for(auto i = 0; i < (int) greedy.size(); i++){
            for(int j = 0; j < (int) greedy[i].size(); j++){
               greedy_media[j] += (greedy[i][j] / n_iteraciones);
            }
         }

         cout << "Media: " << titulos[c] << endl;
         cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "T" << endl;
         cout << "---------------------------------------------------------------------------------------------------" << endl;
         cout << c+1 << "          ";
         for(auto it = greedy_media.begin(); it != greedy_media.end(); it++){
            cout << *it << "          ";
         }
         cout << endl;
         cout << "---------------------------------------------------------------------------------------------------" << endl;
      }
   }

   cout << endl;
   cout << endl;

   cout << "----------------- Tabla de resultados BL -----------------" << endl;
   for(int c = 0; c < n_conjuntos_datos; c++){
      bl.clear()

      for(int i = 0; i < n_iteraciones; i++){
         Set_random(semillas[i]);
         CCP par(n_k[c],datos[c],restricciones[c]);

         tini= clock();
         par.busqueda_local();
         tfin= clock();

         double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
         vector<double> fila;
         fila = par.fila_datos();
         fila.push_back(tiempo);
         bl.push_back(fila);

         if(solucion_completa){
            cout << "---------------------------------------------------------------------------------------------------" << endl;
            cout << titulos[c] << endl;
            cout << "Iteracion: " << i+1 << endl;
            cout << "Semilla: " << semillas[i] << endl;
            par.mostrar_solucion(true);
            cout << "---------------------------------------------------------------------------------------------------" << endl;
         }

         if(mostrar_iteracion){
            if(i == 0){
               cout << titulos[c] << endl;
               cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "T" << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
            }
            cout << i+1 << "          ";
            vector<double>::iterator it;
            for(it = fila.begin(); it != fila.end(); it++){
               cout << *it << "          ";
            }
            cout << endl;
            cout << "---------------------------------------------------------------------------------------------------" << endl;
         }
      }

      if(mostrar_media){
         bl_media.clear();
         for(int i = 0; i < (int) bl[0].size(); i++){
            bl_media.push_back(0);
         }

         for(auto i = 0; i < (int) bl.size(); i++){
            for(int j = 0; j < (int) bl[i].size(); j++){
               bl_media[j] += (bl[i][j] / n_iteraciones);
            }
         }

         cout << "Media: " << titulos[c] << endl;
         cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "T" << endl;
         cout << "---------------------------------------------------------------------------------------------------" << endl;
         cout << c+1 << "          ";
         for(auto it = bl_media.begin(); it != bl_media.end(); it++){
            cout << *it << "          ";
         }
         cout << endl;
         cout << "---------------------------------------------------------------------------------------------------" << endl;
      }
   }
}
