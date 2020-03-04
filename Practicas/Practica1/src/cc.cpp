#include "cc.h"

CCP::CCP(const int n, const std::string p, const std::string r){
   n_cluster = n;
   desv_gen = 0;
   infactibilidad = 0;
   cargar_posiciones(p);
   cargar_restricciones(r);
   centroides.resize(n_cluster);
   clusters.resize(n_cluster);

   double max = posiciones[0][0], min = posiciones[0][0];
   for(int i = 0; i < posiciones.size(); i++){
      for(int j = 0; j < posiciones[i].size(); j++){
         if(posiciones[i][j] < min){
            min = posiciones[i][j];
         }
         if (posiciones[i][j] > max){
            max = posiciones[i][j];
         }
      }
   }
   for(int i = 0; i < n_cluster; i++){
      for(int j = 0; j < posiciones[0].size(); j++){
         centroides[i].push_back(Randfloat(min,max-1));
      }
   }
   d_intracluster.resize(n_cluster);
   solucion.resize(posiciones.size());
   for(int i = 0; i < solucion.size(); i++){
      solucion[i] = -1;
   }
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
         if (valor != 0 && i != j){
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

   std::cout << "Restricciones: " << restricciones.size() << std::endl;

   for(int i = 0; i < centroides.size(); i++){
      for(int j = 0; j < centroides[i].size(); j++){
         std::cout << centroides[i][j] << " ";
      }
      std::cout << std::endl;
   }
}

void CCP::mostrar_solucion(const int i){
   if(i == 0){ //solucion greedy
      std::cout << "Desviacion general: " << desv_gen << std::endl;
      std::cout << "Infactibilidad: " << infactibilidad << std::endl;
      for(int j = 0; j < n_cluster; j++){
         std::cout << "Cluster " << j << " : ";
         for(int k = 0; k < clusters[j].size(); k++){
            std::cout << clusters[j][k] << " ";
         }
         std::cout << std::endl;
      }/*
      std::cout << std::endl;
      for(int j = 0; j < solucion.size(); j++){
         std::cout << solucion[j] << " ";
      }
      std::cout << std::endl;

      */for(int i = 0; i < n_cluster; i++){
         std::cout << "Centroide: " << i << std::endl;
         for(int j = 0; j < centroides[i].size(); j++){
            std::cout << centroides[i][j] << " ";
         }
         std::cout << std::endl;
      }
      std::cout << std::endl;
   }
}

void CCP::calcular_centroide(const int i){
   for(int j = 0; j < centroides[i].size(); j++){
      centroides[i][j] = 0;
   }
   for(int j = 0; j < clusters[i].size(); j++){
      for(int k = 0; k < posiciones[clusters[i][j]].size(); k++){
            centroides[i][k] += (1.0/clusters[i].size()) * posiciones[clusters[i][j]][k];
      }
   }
}

void CCP::distancia_intracluster(const int i){
   double d_euclidea;
   for(int j = 0; j < n_cluster; j++){
      d_intracluster[j] = 0;
   }
   for(int j = 0; j < clusters[i].size(); j++){
      for(int k = 0; k < posiciones[clusters[i][j]].size(); k++){
         d_euclidea =  std::abs(posiciones[clusters[i][j]][k] - centroides[i][k]);
         d_euclidea *= d_euclidea;
         d_intracluster[i] += (1.0/clusters[i].size()) * d_euclidea;
      }
   }
}

void CCP::desviacion_general(){
   for(int i = 0; i < n_cluster; i++){
      distancia_intracluster(i);
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
   for(int i = 0; i < solucion.size(); i++){
      solucion[i] = -1;
   }
   for(int i = 0; i < n_cluster; i++){
      for(int j = 0; j < clusters[i].size(); j++){
         solucion[clusters[i][j]] = i;
      }
   }
}

double CCP::distancia_nodo_cluster(const int n, const int c){
   double d_euclidea = 0, componente = 0;
   for(int i = 0; i < posiciones[n].size(); i++){
      componente = std::abs(posiciones[n][i] - centroides[c][i]);
      componente *= componente;
      d_euclidea += componente;
   }
   return d_euclidea;
}



int CCP::restricciones_incumplidas(const int n, const int c){
   int incumplidas = 0;
   std::pair<int,int> pareja;
   pareja.first = n;
   for(int i = 0; i < clusters[c].size(); i++){
      pareja.second = clusters[c][i];
      auto it = restricciones.find(pareja);
      if(it->second == -1){
         incumplidas++;
      }
   }
   for(int i = 0; i < n_cluster; i++){
      if(i != c){
         for(int j = 0; j < clusters[i].size(); j++){
            pareja.second = clusters[i][j];
            auto it = restricciones.find(pareja);
            if(it->second == 1){
               incumplidas++;
            }
         }
      }
   }
   return incumplidas;
}

void CCP::asignar_cluster(const int n){
   std::pair<int,int> pareja;
   std::vector<std::pair<int,int>> r;

   int cluster = -1, r_min;
   double d_min, d;

   for(int i = 0; i < n_cluster; i++){
      pareja.first = restricciones_incumplidas(n,i);
      pareja.second = i;
      r.push_back(pareja);
   }

   std::sort(r.begin(),r.end());

   /*for(int i = 0; i < r.size(); i++){
      std::cout << r[i]. first << " " << r[i].second << std::endl;
   }
   std::cout << "----------------------------------" << std::endl;*/

   r_min = r[0].first;
   d_min = 1000000.0;
   for(int i = 0; i < r.size() && r[i].first == r_min; i++){
      d = distancia_nodo_cluster(n,r[i].second);
      if(d < d_min){
         d_min = d;
         cluster = r[i].second;
      }
   }

   infactibilidad += r_min;
   clusters[cluster].push_back(n);
}

/*void CCP::infactibilidad_total(){
   for(auto it = restricciones.begin(); it != restricciones.end(); it++){
      if(it->first.second > it->first.second){
         if(it->second == 1){
            for(int i = 0; i < n_cluster; i++){
               auto primero = std::find(clusters[i].begin(), clusters[i].end(), it->first.first);
               auto segundo = std::find(clusters[i].begin(), clusters[i].end(), it->first.second);
               if(primero != clusters[i].end() && segundo != clusters[i].end()){
                  infactibilidad++;
               }
            }
         }
      }
   }
}*/

void CCP::limpiar_clusters(){
   for(int i = 0; i < n_cluster; i++){
      clusters[i].clear();
   }
   infactibilidad = 0;

}

bool CCP::solucion_factible(){
   for(int i = 0; i < n_cluster; i++){
      if(clusters[i].size() == 0){
         return false;
      }
   }
   return true;
}

void CCP::greedy(){
   bool cambio_c;
   std::vector<int> rsi;
   std::vector<std::vector<int>> solucion_ant = clusters;

   for(int i = 0; i < posiciones.size(); i++){
      rsi.push_back(i);
   }

   std::random_shuffle(rsi.begin(), rsi.end(), Randint_shuffle);

   do {
      cambio_c = false;
      for(int i = 0; i < rsi.size(); i++){
         asignar_cluster(rsi[i]);
      }
      for(int i = 0; i < n_cluster; i++){
         if(solucion_ant[i] != clusters[i]){
            calcular_centroide(i);
            cambio_c = true;
         }
      }
      solucion_ant = clusters;
      //mostrar_solucion(0);
      if(cambio_c){
         limpiar_clusters();
      }
   } while(cambio_c);
   generar_solucion();
   desviacion_general();
}

void CCP::busqueda_local(){

}
