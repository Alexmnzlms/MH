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
#include "random.h"

class CCP {

private:
   int n_cluster;
   std::vector<std::vector<double>> posiciones;
   std::vector<std::vector<double>> centroides;
   std::map<std::pair<int,int>,int> restricciones;
   std::vector<std::vector<int>> clusters;


   void cargar_posiciones(const std::string archivo);
   void cargar_restricciones(const std::string archivo);
   void calcular_centroide(int i);
   void distancia_euclidea();
   void desviacion_general();

public:
   CCP(const int n, const std::string p, const std::string r);
   void mostrar_datos();
   void copkm();
};


#endif
