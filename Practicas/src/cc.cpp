#include "cc.h"

CCP::CCP(const int n, const std::string p, const std::string r){
   Set_random(2020);
   n_cluster = n;
   desv_gen = 0;
   cargar_posiciones(p);
   cargar_restricciones(r);
   centroides.resize(n_cluster);

   double max = posiciones[0][0], min = posiciones[0][0];
   for(int i = 0; i < posiciones.size(); i++){
      for(int j = 0; j < posiciones[i].size(); j++){
         if(posiciones[i][j] < min){
            min = posiciones[i][j];
         } else if (posiciones[i][j] > max){
            max = posiciones[i][j];
         }
      }
   }
   for(int i = 0; i < n_cluster; i++){
      for(int j = 0; j < posiciones[0].size(); j++){
         centroides[i].push_back(Randfloat(min,max+1));
      }
   }
   d_intracluster.resize(n_cluster);
   solucion.resize(n_cluster*posiciones[0].size());
}

void CCP::cargar_posiciones(const std::string archivo){
   std::ifstream in(archivo);
   int i = 0;
   std::string variable;
   std::string dato;
   while(getline(in,variable)){
      posiciones.resize(i+1);
      std::istringstream iss(variable);
      while(getline(iss,dato,',')){
         posiciones[i].push_back(atof(dato.c_str()));
      }
      i++;
   }
}

void CCP::cargar_restricciones(const std::string archivo){
   std::ifstream in(archivo);
   int valor;
   int i = 0,j = 0;
   std::string fila;
   std::string restriccion;
   while(getline(in,fila)){
      std::istringstream iss(fila);
      while(getline(iss,restriccion,',')){
         std::pair<int,int> pareja(i,j);
         valor = atof(restriccion.c_str());
         if (valor != 0){
            restricciones.insert(std::pair<std::pair<int,int>,int>(pareja,valor));
         }
         j++;
      }
      i++;
      j=0;
   }

}

void CCP::mostrar_datos(){
   std::cout << posiciones.size() << std::endl;
   for(int i = 0; i < posiciones.size(); i++){
      for(int j = 0; j < posiciones[i].size(); j++){
         std::cout << posiciones[i][j] << " ";
      }
      std::cout << std::endl;
   }

   std::map<std::pair<int,int>,int>::iterator it = restricciones.begin();
   for(it; it != restricciones.end(); it++){
      std::cout << (*it).first.first << ", " << (*it).first.second << ": "  << (*it).second << std::endl;
   }

   for(int i = 0; i < centroides.size(); i++){
      for(int j = 0; j < centroides[i].size(); j++){
         std::cout << centroides[i][j] << " ";
      }
      std::cout << std::endl;
   }

}

void CCP::mostrar_solucion(int i){
   if(i == 0){ //solucion greedy
      std::cout << "Desviacion general: " << desv_gen << std::endl;
   }
   for(int j = 0; j < solucion.size(); j++){
      std::cout << j << " ";
   }
   std::cout << std::endl;
   for(int j = 0; j < solucion.size(); j++){
      std::cout << solucion[j] << " ";
   }
}

void CCP::calcular_centroide(int i){
   for(int j = 0; j < centroides[i].size(); j++){
      centroides[i][j] = 0;
   }
   for(int j = 0; j < clusters[i].size(); j++){
      for(int k = 0; k < posiciones[clusters[i][j]].size(); k++){
            centroides[i][k] += (1/clusters[i].size()) * posiciones[clusters[i][j]][k];
      }
   }
}

void CCP::distancia_intracluster(int i){
   int d_euclidea;
   for(int j = 0; j < n_cluster; j++){
      d_intracluster[j] = 0;
   }
   for(int j = 0; j < clusters[i].size(); j++){
      for(int k = 0; k < posiciones[clusters[i][j]].size(); k++){
         d_euclidea =  (posiciones[clusters[i][j]][k] - centroides[i][k]);
         d_euclidea = d_euclidea * d_euclidea;
         d_intracluster[i] += (1/clusters[i].size()) * d_euclidea;
      }
   }
}

void CCP::desviacion_general(){
   for(int i = 0; i < n_cluster; i++){
      desv_gen += (1/n_cluster)*d_intracluster[i];
   }
}

void CCP::generar_vecino(){

}

void CCP::leer_solucion(){
   for(int i = 0; i < solucion.size(); i++){
      clusters[solucion[i]].push_back(i);
   }
}

void CCP::generar_solucion(){
   for(int i = 0; i < n_cluster; i++){
      for(int j = 0; j < clusters[i].size(); j++){
         solucion[clusters[i][j]] = i;
      }
   }
}

void CCP::copkm(){

}

void CCP::busqueda_local(){

}
