#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include "cc.h"

using namespace std;

unsigned buscar_semilla(){
   bool salir = false;
   bool fallo = false;
   int n;
   int n_max = 500;
   unsigned seed;
   while(!salir){
      seed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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

int main(int argc, char ** argv){
   unsigned long tini, tfin;
   int n_iteraciones = 5;
   int n_conjuntos_datos = 8;
   double semillas [5] = {2024614690, 2024676296, 2024677261, 2024740484, 2024740899};
   bool nueva_semilla = false;

   bool solucion_completa = true;
   bool mostrar_iteracion = true;
   bool mostrar_media = true;

   bool mostrar_greedy = false;
   bool mostrar_bl = false;
   bool mostrar_ag = false;

   int tipo_ag = 0;
   int operador_ag = 0;
   string nombre_ag;

   vector<string> titulos {"Rand 10%", "Iris 10%", "Ecoli 10%", "Newthyroid 10%", "Rand 20%", "Iris 20%", "Ecoli 20%", "Newthyroid 20%"};
   vector<int> n_k {3,3,8,3,3,3,8,3};
   vector<bool> usar_conjunto {false,false,false,false,false,false,false,false};
   vector<string> datos {"data/rand_set.dat", "data/iris_set.dat", "data/ecoli_set.dat", "data/newthyroid_set.dat", "data/rand_set.dat", "data/iris_set.dat", "data/ecoli_set.dat", "data/newthyroid_set.dat"};
   vector<string> restricciones {"data/rand_set_const_10.const", "data/iris_set_const_10.const", "data/ecoli_set_const_10.const", "data/newthyroid_set_const_10.const", "data/rand_set_const_20.const", "data/iris_set_const_20.const", "data/ecoli_set_const_20.const", "data/newthyroid_set_const_20.const"};

   n_iteraciones = atoi(argv[1]);
   usar_conjunto[atoi(argv[2])] = true;

   char greedy_code[] = "G";
   char bl_code[] = "BL";
   char aggun_code[] = "AGG_UN";
   char aggsf_code[] = "AGG_SF";
   char ageun_code[] = "AGE_UN";
   char agesf_code[] = "AGE_SF";
   char sem_code[] = "SEM";

   if(strcmp(argv[3],greedy_code) == 0){
      mostrar_greedy = true;
   } else if(strcmp(argv[3],bl_code) == 0){
      mostrar_bl = true;
   } else if(strcmp(argv[3],aggun_code) == 0){
      tipo_ag = 0;
      operador_ag = 0;
      nombre_ag = argv[3];
      mostrar_ag = true;
   } else if(strcmp(argv[3],aggsf_code) == 0){
      tipo_ag = 0;
      operador_ag = 1;
      nombre_ag = argv[3];
      mostrar_ag = true;
   } else if(strcmp(argv[3],ageun_code) == 0){
      tipo_ag = 1;
      operador_ag = 0;
      nombre_ag = argv[3];
      mostrar_ag = true;
   } else if(strcmp(argv[3],agesf_code) == 0){
      tipo_ag = 1;
      operador_ag = 1;
      nombre_ag = argv[3];
      mostrar_ag = true;
   } else if(strcmp(argv[3],sem_code) == 0){
      nueva_semilla = true;
   }


   cout << "Ejecutando programa CCP" << endl;

   cout << "Semillas utilizadas: {";
   for(int i = 0; i < n_iteraciones; i++){
      cout << (unsigned) semillas[i];
      if(i != 4){
         cout << ", ";
      }
   }
   cout << "};" << endl << endl;

   vector<vector<double>> greedy;
   vector<double> greedy_media;

   vector<vector<double>> bl;
   vector<double> bl_media;

   vector<vector<double>> agg;
   vector<double> agg_media;

   if(nueva_semilla){
      vector<unsigned> sems;
      for(int i = 0; i < n_iteraciones; i++){
         unsigned seed = buscar_semilla();
         cout << "----------------------------------------------------------------" << endl;
         cout << "Semilla encontrada: " << seed << endl;
         cout << "----------------------------------------------------------------" << endl;
         sems.push_back(seed);
      }

      cout << "{";
      for(int i = 0; i < n_iteraciones; i++){
         cout << sems[i];
         if(i != 4){
            cout << ", ";
         }
      }
      cout << "};" << endl;
      return(0);
   }

   if(mostrar_greedy){
      cout << "----------------- Tabla de resultados greedy -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
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
                  for(auto it = fila.begin(); it != fila.end(); ++it){
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

               for(int i = 0; i < (int) greedy.size(); i++){
                  for(int j = 0; j < (int) greedy[i].size(); j++){
                     greedy_media[j] += (greedy[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " greedy" << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "T" << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = greedy_media.begin(); it != greedy_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }

   if(mostrar_bl){
      cout << "----------------- Tabla de resultados BL -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            bl.clear();

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
                  for(it = fila.begin(); it != fila.end(); ++it){
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

               for(int i = 0; i < (int) bl.size(); i++){
                  for(int j = 0; j < (int) bl[i].size(); j++){
                     bl_media[j] += (bl[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " BL" << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "T" << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = bl_media.begin(); it != bl_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }

   if(mostrar_ag){
      cout << "----------------- Tabla de resultados " << nombre_ag << " -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            agg.clear();

            for(int i = 0; i < n_iteraciones; i++){
               Set_random(semillas[i]);
               CCP par(n_k[c],datos[c],restricciones[c]);

               tini= clock();
               par.AGG(tipo_ag,operador_ag);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos();
               fila.push_back(tiempo);
               agg.push_back(fila);

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
                  for(it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "---------------------------------------------------------------------------------------------------" << endl;
               }
            }

            if(mostrar_media){
               agg_media.clear();
               for(int i = 0; i < (int) agg[0].size(); i++){
                  agg_media.push_back(0);
               }

               for(int i = 0; i < (int) agg.size(); i++){
                  for(int j = 0; j < (int) agg[i].size(); j++){
                     agg_media[j] += (agg[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " "  << nombre_ag << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "T" << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = agg_media.begin(); it != agg_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "---------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }
}
