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
   int ind_eval;
   std::vector<std::vector<int>> generacion;
   std::vector<std::vector<int>> seleccion;
   std::vector<double> f_generacion;
   std::vector<double> f_seleccion;
   std::vector<int> mejor_generacion;
   double f_mejor_generacion;

   double desv_gen;
   double infactibilidad;
   double lambda;
   double f_objetivo;

   int it_greedy;
   int eval_bl;
   int gen_ag_am;

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

   void generacion_inicial();
   int calcular_infact_sol(std::vector<int> & sol);
   double evaluar_solucion(std::vector<int> & sol);
   std::vector<int> torneo_binario(int t);
   void seleccionar_mejor();
   int seleccionar_peor();
   void operador_seleccion(int t);
   std::vector<int> operador_cruce_uniforme(std::vector<int> & p1, std::vector<int> & p2);
   std::vector<int> operador_cruce_segmento(std::vector<int> & p1, double f_p1, std::vector<int> & p2, double f_p2, int n = 0);
   void operador_cruce(int n, int s,double p);
   void conservar_elitismo();
   void reparar_solucion(std::vector<int> & sol);
   void reparar_seleccion();
   void mutar_solucion(std::vector<int> & sol);
   void mutar_seleccion();
   void leer_mejor_generado();
   void aplicar_generacional();
   void aplicar_estacionario(int n);
   bool mejor_valor(std::vector<int> & sol, double & f_sol,int i);
   void busqueda_local_suave(std:: vector<int> & sol, double & f_sol);
   void aplicar_BLS(double p, bool mejor);



public:
   CCP(const int n, const std::string p, const std::string r);
   int greedy(bool v = false);
   void busqueda_local(bool v = false);
   void AG(int g, int n, bool v = false, bool graph = false, bool ignore_eval=false, int maxgen = 0);
   void AM(int n, double p, bool mejor = false, bool v = false, bool graph = false, bool ignore_eval=false, int maxgen = 0);
   void BMB(bool v = false);
   void mostrar_datos();
   void mostrar_solucion(bool completo=false);
   std::vector<double> fila_datos(int n);
   void mostrar_generacion();
   void mostrar_seleccion();
   void mostrar_agm();
};


#endif
