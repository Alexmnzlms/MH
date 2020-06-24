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
   double semillas [5] = {/*123452244*/2024614690, 2024676296, 2024677261, 2024740484, 2024740899};
   bool nueva_semilla = false;
   bool grafica_genetico = false;
   bool grafica_es = false;
   bool grafica_bl = false;
   bool grafica_mvo = false;
   int n_graph_es = -1;
   int n_mvo = -1;

   bool solucion_completa = false;
   bool mostrar_iteracion = true;
   bool mostrar_media = true;

   bool mostrar_greedy = false;
   bool mostrar_bl = false;
   bool mostrar_ag = false;
   bool mostrar_am = false;
   bool mostrar_bmb = false;
   bool mostrar_es = false;
   bool mostrar_ils = false;
   bool mostrar_mvo = false;

   int tipo_ag = 0;
   int operador_ag = 0;
   string nombre_ag;

   int generaciones_am = 0;
   double probabilidad_am = 0;
   bool mejores_am = false;
   string nombre_am;

   int busqueda_ils = 0;
   string nombre_ils;


   vector<string> titulos {"Rand 10%", "Iris 10%", "Ecoli 10%", "Newthyroid 10%", "Rand 20%", "Iris 20%", "Ecoli 20%", "Newthyroid 20%"};
   vector<int> n_k {3,3,8,3,3,3,8,3};
   vector<bool> usar_conjunto {false,false,false,false,false,false,false,false};
   vector<string> datos {"data/rand_set.dat", "data/iris_set.dat", "data/ecoli_set.dat", "data/newthyroid_set.dat", "data/rand_set.dat", "data/iris_set.dat", "data/ecoli_set.dat", "data/newthyroid_set.dat"};
   vector<string> restricciones {"data/rand_set_const_10.const", "data/iris_set_const_10.const", "data/ecoli_set_const_10.const", "data/newthyroid_set_const_10.const", "data/rand_set_const_20.const", "data/iris_set_const_20.const", "data/ecoli_set_const_20.const", "data/newthyroid_set_const_20.const"};

   n_iteraciones = atoi(argv[1]);
   if(atoi(argv[2]) == 0){
      for(int i = 0; i < n_conjuntos_datos; i++){
         usar_conjunto[i] = true;
      }
   } else{
      usar_conjunto[atoi(argv[2]) - 1] = true;
   }

   char greedy_code[] = "G";
   char bl_code[] = "BL";
   char aggun_code[] = "AGG_UN";
   char aggsf_code[] = "AGG_SF";
   char ageun_code[] = "AGE_UN";
   char agesf_code[] = "AGE_SF";
   char am1_code[] = "AM_10-1.0";
   char am2_code[] = "AM_10-0.1";
   char am3_code[] = "AM_10-0.1mej";
   char sem_code[] = "SEM";
   char bmb_code[] = "BMB";
   char es_code[] = "ES";
   char ilsbl_code[] = "ILS";
   char ilses_code[] = "ILS-ES";
   char mvo_code[] = "MVO";

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
   } else if(strcmp(argv[3],am1_code) == 0){
      generaciones_am = 10;
      probabilidad_am = 1.0;
      nombre_am = argv[3];
      mostrar_am = true;
   } else if(strcmp(argv[3],am2_code) == 0){
      generaciones_am = 10;
      probabilidad_am = 0.1;
      nombre_am = argv[3];
      mostrar_am = true;
   } else if(strcmp(argv[3],am3_code) == 0){
      generaciones_am = 10;
      probabilidad_am = 0.1;
      mejores_am = true;
      nombre_am = argv[3];
      mostrar_am = true;
   } else if(strcmp(argv[3],sem_code) == 0){
      nueva_semilla = true;
   } else if(strcmp(argv[3],bmb_code) == 0){
      mostrar_bmb = true;
   } else if(strcmp(argv[3],es_code) == 0){
      mostrar_es = true;
   } else if(strcmp(argv[3],ilsbl_code) == 0){
      mostrar_ils = true;
      busqueda_ils = 0;
      nombre_ils = argv[3];
   } else if(strcmp(argv[3],ilses_code) == 0){
      mostrar_ils = true;
      busqueda_ils = 1;
      nombre_ils = argv[3];
   } else if(strcmp(argv[3],mvo_code) == 0){
      mostrar_mvo = true;
   }
   if(n_iteraciones == 0){
      if(mostrar_ag || mostrar_am){
         grafica_genetico = true;
      } else if(mostrar_es){
         grafica_es = true;
      } else if(mostrar_bl){
         grafica_bl = true;
      } else if(mostrar_mvo){
         grafica_mvo = true;
      }
   }

   if(argc > 4){
      char verbose[] = "v";
      if(strcmp(verbose, argv[4]) == 0){
         solucion_completa = true;
      } else {
         n_graph_es = atoi(argv[4]);
         n_mvo =  atoi(argv[4]);
      }
   }

   if(!grafica_genetico && !grafica_es && !grafica_bl){
      cout << "Ejecutando programa CCP" << endl;

      cout << "Semillas utilizadas: {";
      for(int i = 0; i < n_iteraciones; i++){
         cout << (unsigned) semillas[i];
         if(i != 4){
            cout << ", ";
         }
      }
      cout << "};" << endl << endl;
   }

   vector<vector<double>> greedy;
   vector<double> greedy_media;

   vector<vector<double>> bl;
   vector<double> bl_media;

   vector<vector<double>> ag;
   vector<double> ag_media;

   vector<vector<double>> am;
   vector<double> am_media;

   vector<vector<double>> bmb;
   vector<double> bmb_media;

   vector<vector<double>> es;
   vector<double> es_media;

   vector<vector<double>> ils;
   vector<double> ils_media;

   vector<vector<double>> mvo;
   vector<double> mvo_media;

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

   if(grafica_genetico){
      if(mostrar_ag){
         for(int c = 0; c < n_conjuntos_datos; c++){
            if(usar_conjunto[c]){
               Set_random(semillas[0]);
               CCP par(n_k[c],datos[c],restricciones[c]);
               par.AG(tipo_ag,operador_ag,false,true);
               par.mostrar_agm();
               return(0);
            }
         }
      } else if(mostrar_am){
         for(int c = 0; c < n_conjuntos_datos; c++){
            if(usar_conjunto[c]){
               Set_random(semillas[0]);
               CCP par(n_k[c],datos[c],restricciones[c]);
               par.AM(generaciones_am,probabilidad_am,mejores_am,false,true);
               par.mostrar_agm();
               return(0);
            }
         }
      }
   }
   if(grafica_es){
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            Set_random(semillas[0]);
            CCP par(n_k[c],datos[c],restricciones[c]);
            par.ES(false, true, 100000, true, n_graph_es);
            return(0);
         }
      }
   }
   if(grafica_bl){
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            Set_random(semillas[0]);
            CCP par(n_k[c],datos[c],restricciones[c]);
            par.busqueda_local(false, true, 100000, true);
            return(0);
         }
      }
   }

   if(grafica_mvo){
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            Set_random(semillas[0]);
            CCP par(n_k[c],datos[c],restricciones[c]);
            par.MVO(true, n_mvo, false);
            return(0);
         }
      }
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
               par.greedy(solucion_completa);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(0);
               fila.push_back(tiempo);
               greedy.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Iteraciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
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
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Iteraciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = greedy_media.begin(); it != greedy_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
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
               par.busqueda_local(solucion_completa);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(1);
               fila.push_back(tiempo);
               bl.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
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
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = bl_media.begin(); it != bl_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
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
            ag.clear();

            for(int i = 0; i < n_iteraciones; i++){
               Set_random(semillas[i]);
               CCP par(n_k[c],datos[c],restricciones[c]);

               tini= clock();
               par.AG(tipo_ag,operador_ag,solucion_completa,false);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(2);
               fila.push_back(tiempo);
               ag.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Generaciones" << "          " << "Evaluaciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }
            }

            if(mostrar_media){
               ag_media.clear();
               for(int i = 0; i < (int) ag[0].size(); i++){
                  ag_media.push_back(0);
               }

               for(int i = 0; i < (int) ag.size(); i++){
                  for(int j = 0; j < (int) ag[i].size(); j++){
                     ag_media[j] += (ag[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " "  << nombre_ag << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Generaciones" << "          " << "Evaluaciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = ag_media.begin(); it != ag_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }

   if(mostrar_am){
      cout << "----------------- Tabla de resultados " << nombre_am << " -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            am.clear();

            for(int i = 0; i < n_iteraciones; i++){
               Set_random(semillas[i]);
               CCP par(n_k[c],datos[c],restricciones[c]);

               tini= clock();
               par.AM(generaciones_am,probabilidad_am,mejores_am,solucion_completa,false);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(2);
               fila.push_back(tiempo);
               am.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Generaciones" << "          " << "Evaluaciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }
            }

            if(mostrar_media){
               am_media.clear();
               for(int i = 0; i < (int) am[0].size(); i++){
                  am_media.push_back(0);
               }

               for(int i = 0; i < (int) am.size(); i++){
                  for(int j = 0; j < (int) am[i].size(); j++){
                     am_media[j] += (am[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " "  << nombre_am << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Generaciones" << "          " << "Evaluaciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = am_media.begin(); it != am_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }

   if(mostrar_bmb){
      cout << "----------------- Tabla de resultados BMB -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            bmb.clear();

            for(int i = 0; i < n_iteraciones; i++){
               Set_random(semillas[i]);
               CCP par(n_k[c],datos[c],restricciones[c]);

               tini= clock();
               par.BMB(solucion_completa);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(1);
               fila.push_back(tiempo);
               bmb.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }
            }

            if(mostrar_media){
               bmb_media.clear();
               for(int i = 0; i < (int) bmb[0].size(); i++){
                  bmb_media.push_back(0);
               }

               for(int i = 0; i < (int) bmb.size(); i++){
                  for(int j = 0; j < (int) bmb[i].size(); j++){
                     bmb_media[j] += (bmb[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " BMB" << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = bmb_media.begin(); it != bmb_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }

   if(mostrar_es){
      cout << "----------------- Tabla de resultados ES -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            es.clear();

            for(int i = 0; i < n_iteraciones; i++){
               Set_random(semillas[i]);
               CCP par(n_k[c],datos[c],restricciones[c]);

               tini= clock();
               par.ES(solucion_completa);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(1);
               fila.push_back(tiempo);
               es.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }
            }

            if(mostrar_media){
               es_media.clear();
               for(int i = 0; i < (int) es[0].size(); i++){
                  es_media.push_back(0);
               }

               for(int i = 0; i < (int) es.size(); i++){
                  for(int j = 0; j < (int) es[i].size(); j++){
                     es_media[j] += (es[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " ES" << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = es_media.begin(); it != es_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }

   if(mostrar_ils){
      cout << "----------------- Tabla de resultados " << nombre_ils << " -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            ils.clear();

            for(int i = 0; i < n_iteraciones; i++){
               Set_random(semillas[i]);
               CCP par(n_k[c],datos[c],restricciones[c]);

               tini= clock();
               par.ILS(busqueda_ils,solucion_completa);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(1);
               fila.push_back(tiempo);
               ils.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }
            }

            if(mostrar_media){
               ils_media.clear();
               for(int i = 0; i < (int) ils[0].size(); i++){
                  ils_media.push_back(0);
               }

               for(int i = 0; i < (int) ils.size(); i++){
                  for(int j = 0; j < (int) ils[i].size(); j++){
                     ils_media[j] += (ils[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " "  << nombre_ils << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = ils_media.begin(); it != ils_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }

   if(mostrar_mvo){
      cout << "----------------- Tabla de resultados MVO -----------------" << endl;
      for(int c = 0; c < n_conjuntos_datos; c++){
         if(usar_conjunto[c]){
            mvo.clear();

            for(int i = 0; i < n_iteraciones; i++){
               Set_random(semillas[i]);
               CCP par(n_k[c],datos[c],restricciones[c]);

               tini= clock();
               par.MVO(false, n_mvo, solucion_completa);
               tfin= clock();

               double tiempo = (tfin-tini)/(double)CLOCKS_PER_SEC;
               vector<double> fila;
               fila = par.fila_datos(0);
               fila.push_back(tiempo);
               mvo.push_back(fila);

               if(solucion_completa){
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  cout << titulos[c] << endl;
                  cout << "Iteracion: " << i+1 << endl;
                  cout << "Semilla: " << semillas[i] << endl;
                  par.mostrar_solucion(true);
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }

               if(mostrar_iteracion){
                  if(i == 0){
                     cout << titulos[c] << endl;
                     cout << "i" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
                     cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
                  }
                  cout << i+1 << "          ";
                  for(auto it = fila.begin(); it != fila.end(); ++it){
                     cout << *it << "          ";
                  }
                  cout << endl;
                  cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               }
            }

            if(mostrar_media){
               mvo_media.clear();
               for(int i = 0; i < (int) mvo[0].size(); i++){
                  mvo_media.push_back(0);
               }

               for(int i = 0; i < (int) mvo.size(); i++){
                  for(int j = 0; j < (int) mvo[i].size(); j++){
                     mvo_media[j] += (mvo[i][j] / n_iteraciones);
                  }
               }

               cout << "Media: " << titulos[c] << " MVO " << endl;
               cout << "c" << "          " << "Tasa_C" << "          " << "Tasa_inf" << "          " << "Lambda" << "          " << "Agr." << "          " << "Evaluaciones" << "          " << "T" << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
               cout << c+1 << "          ";
               for(auto it = mvo_media.begin(); it != mvo_media.end(); ++it){
                  cout << *it << "          ";
               }
               cout << endl;
               cout << "-----------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
         }
      }
      cout << endl;
      cout << endl;
   }
}
