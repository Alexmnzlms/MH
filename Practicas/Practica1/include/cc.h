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
   std::vector<std::vector<int>> clusters;
   std::vector<double> d_intracluster;
   std::vector<int> solucion;
   double desv_gen;

   void cargar_posiciones(const std::string archivo);
   void cargar_restricciones(const std::string archivo);
   void calcular_centroide(int i);
   void distancia_intracluster(int i);
   void desviacion_general();
   void generar_vecino();
   void leer_solucion();
   void generar_solucion();
   int cluster_cercano(int n);
   void asignar_cluster(int n, int c);
   bool comprueba_restriccion(int n, int c);
   void limpiar_clusters();
   bool solucion_factible();
   bool solucion_completa();

public:
   CCP(const int n, const std::string p, const std::string r);
   void mostrar_datos();
   void mostrar_solucion(int i);
   void copkm();
   void busqueda_local();
};


#endif
