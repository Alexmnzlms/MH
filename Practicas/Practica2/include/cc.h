#ifndef __CCP
#define __CCP

#include <vector>
#include <utility>
#include <map>
#include <set>
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
   std::vector<double> d_intracluster;
   std::vector<int> solucion;

   std::set<std::pair<int,int>> vecindario;
   std::vector<std::vector<int>> clusters;

   int poblacion;
   std::vector<std::vector<int>> generacion;
   std::vector<double> f_generacion;

   double desv_gen;
   double infactibilidad;
   double lambda;
   double f_objetivo;

   void cargar_posiciones(const std::string archivo);
   void cargar_restricciones(const std::string archivo);

   void calcular_centroide(const int i);
   void distancia_intracluster(const int i);
   void desviacion_general();
   void calcular_lambda();
   void infactibilidad_solucion();

   double distancia_nodo_cluster(const int n, const int c);
   double distancia_nodo_nodo(const int n, const int m);
   double restricciones_incumplidas(const int n, const int c);

   void asignar_cluster(const int n);
   int buscar_cluster(const int n);
   void limpiar_clusters();

   std::vector<int> crear_solucion();
   void solucion_inicial();
   void generar_solucion();
   void generar_vecino();
   void generar_vecindario();
   void leer_solucion();
   void leer_vecino();
   bool quedan_vecinos();

   int generacion_inicial();
   int calcular_infact_sol(std::vector<int> sol);
   double evaluar_solucion(std::vector<int> sol);
   void seleccion();

public:
   CCP(const int n, const std::string p, const std::string r);
   int greedy();
   void busqueda_local();
   void AGG_UN();
   void mostrar_datos();
   void mostrar_solucion(bool completo=false);
   std::vector<double> fila_datos();
   void mostrar_generacion(int e);
};


#endif
