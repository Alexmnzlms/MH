#ifndef __CCP
#define __CCP

#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "random.h"

class CCP {

private:
   int n_cluster;
   std::vector<std::vector<double>> posiciones;
   std::vector<std::vector<double>> centroides;
   std::map<std::pair<int,int>,int> restricciones;
   std::multimap<int,int> vecindario;
   std::vector<std::vector<int>> clusters;
   std::vector<double> d_intracluster;
   std::vector<int> solucion;
   double desv_gen;
   double infactibilidad;
   double lambda;
   double f_objetivo;

   void cargar_posiciones(const std::string archivo);
   void cargar_restricciones(const std::string archivo);
   void calcular_centroide(const int i);
   void distancia_intracluster(const int i);
   void desviacion_general();
   void leer_solucion();
   void generar_solucion();
   void asignar_cluster(const int n);
   double distancia_nodo_cluster(const int n, const int c);
   double restricciones_incumplidas(const int n, const int c);
   void limpiar_clusters();

   void generar_vecino();
   int buscar_cluster(const int n);
   void solucion_inicial();
   void calcular_lambda();
   double distancia_nodo_nodo(const int n, const int m);
   void generar_vecindario();
   bool quedan_vecinos();


public:
   CCP(const int n, const std::string p, const std::string r);
   void mostrar_datos();
   void mostrar_solucion();
   int greedy();
   void busqueda_local();
   void busqueda_greedy();
};


#endif
