#include "cc.h"

CCP::CCP(const int n, const std::string p, const std::string r){
   Set_random(20061999);
   n_cluster = n;
   desv_gen = 0;
   cargar_posiciones(p);
   cargar_restricciones(r);
   centroides.resize(n_cluster);
   clusters.resize(n_cluster);

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
         centroides[i].push_back(Randfloat(min,max));
      }
   }
   d_intracluster.resize(n_cluster);
   solucion.resize(posiciones.size());
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
      if(solucion_factible()){
         std::cout << "Desviacion general: " << desv_gen << std::endl;
         for(int j = 0; j < n_cluster; j++){
            std::cout << "Cluster " << j << " : ";
            for(int k = 0; k < clusters[j].size(); k++){
               std::cout << clusters[j][k] << " ";
            }
            std::cout << std::endl;
         }
         std::cout << std::endl;
         for(int j = 0; j < solucion.size(); j++){
            std::cout << solucion[j] << " ";
         }
         std::cout << std::endl;
      }
   }
}

void CCP::calcular_centroide(int i){
   for(int j = 0; j < centroides[i].size(); j++){
      centroides[i][j] = 0;
   }
   for(int j = 0; j < clusters[i].size(); j++){
      for(int k = 0; k < posiciones[clusters[i][j]].size(); k++){
            centroides[i][k] += (1.0/clusters[i].size()) * posiciones[clusters[i][j]][k];
      }
   }

   /*std::cout << "Centroide: " << i << std::endl;
   for(int j = 0; j < centroides[i].size(); j++){
      std::cout << centroides[i][j] << " ";
   }
   std::cout << std::endl;*/
}

void CCP::distancia_intracluster(int i){
   double d_euclidea;
   for(int j = 0; j < n_cluster; j++){
      d_intracluster[j] = 0;
   }
   for(int j = 0; j < clusters[i].size(); j++){
      for(int k = 0; k < posiciones[clusters[i][j]].size(); k++){
         d_euclidea =  (posiciones[clusters[i][j]][k] - centroides[i][k]);
         d_euclidea = d_euclidea * d_euclidea;
         d_intracluster[i] += (1.0/clusters[i].size()) * d_euclidea;
      }
   }
}

void CCP::desviacion_general(){
   for(int i = 0; i < n_cluster; i++){
      desv_gen += (1.0/n_cluster)*d_intracluster[i];
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

int CCP::cluster_cercano(int n){
   int c = 0;
   double d_euclidea;
   double d_euclidea_min;
   for(int j = 0; j < posiciones[0].size(); j++){
      d_euclidea_min += posiciones[0][j] - centroides[0][j];
      d_euclidea_min = d_euclidea_min * d_euclidea_min;
   }
   for(int i = 0; i < n_cluster; i++){
      d_euclidea = 0;
      for(int k = 0; k < posiciones[n].size(); k++){
         d_euclidea += posiciones[n][k] - centroides[i][k];
         d_euclidea = d_euclidea * d_euclidea;
      }
      if(d_euclidea < d_euclidea_min){
         d_euclidea_min = d_euclidea;
         c = i;
      }
   }

   return c;
}

void CCP::asignar_cluster(int n, int c){
   if(comprueba_restriccion(n,c)){
      clusters[c].push_back(n);
      //std::cout << "Se asigna el nodo " << n << " al cluster " << c << std::endl;
   } else {
      //std::cout << "No se puede asignar el nodo " << n << " al cluster " << c << std::endl;
   }
   //std::cout << "Tamanio de cluster " << c << ": " << clusters[c].size() << std::endl;
}

bool CCP::comprueba_restriccion(int n, int c){
   std::pair<int,int> pareja;
   pareja.first = n;
   for(int i = 0; i < clusters[c].size(); i++){
      pareja.second = clusters[c][i];
      auto it = restricciones.find(pareja);
      if(it->second == -1){
         return false;
      }
   }
   for(int i = 0; i < n_cluster; i++){
      if(i != c){
         for(int j = 0; j < clusters[c].size(); j++){
            pareja.second = clusters[c][j];
            auto it = restricciones.find(pareja);
            if(it->second == 1){
               return false;
            }
         }
      }
   }
   return true;
}

void CCP::limpiar_clusters(){
   for(int i = 0; i < n_cluster; i++){
      clusters[i].clear();
   }
}

bool CCP::solucion_factible(){
   int suma;
   for(int i = 0; i < n_cluster; i++){
      if(clusters[i].size() == 0){
         return false;
      }
      suma += clusters[i].size();
   }
   if(suma != posiciones.size()){
      return false;
   }
   return true;
}

void CCP::copkm(){
   bool cambio_c;
   std::vector<int> rsi;
   std::vector<double> centroide_ant;

   for(int i = 0; i < posiciones.size(); i++){
      rsi.push_back(i);
   }

   std::random_shuffle(rsi.begin(), rsi.end());

   /*for(int i = 0; i < rsi.size(); i++){
      std::cout << rsi[i] << " ";
   }
   std::cout << std::endl;*/

   do {
      cambio_c = false;
      int cluster;
      int nodo;
      for(int i = 0; i < rsi.size(); i++){
         nodo = rsi[i];
         cluster = cluster_cercano(nodo);
         asignar_cluster(nodo,cluster);
      }
      for(int i = 0; i < n_cluster; i++){
         centroide_ant = centroides[i];
         calcular_centroide(i);
         if(centroide_ant != centroides[i]){
            cambio_c = true;
         }
      }
      /*for(int j = 0; j < n_cluster; j++){
         std::cout << "Cluster " << j << " : ";
         for(int k = 0; k < clusters[j].size(); k++){
            std::cout << clusters[j][k] << " ";
         }
         std::cout << std::endl;
      }*/
      if(cambio_c){
         limpiar_clusters();
      }
   } while(cambio_c);
   generar_solucion();
   desviacion_general();
}

void CCP::busqueda_local(){

}
