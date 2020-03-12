#include "cc.h"

CCP::CCP(const int n, const std::string p, const std::string r){
   n_cluster = n;
   desv_gen = 0;
   infactibilidad = 0;
   lambda = 0;
   f_objetivo = 0;
   cargar_posiciones(p);
   cargar_restricciones(r);
   centroides.resize(n_cluster);
   clusters.resize(n_cluster);

   double max = posiciones[0][0], min = posiciones[0][0];
   for( unsigned i = 0; i < posiciones.size(); i++){
      for( unsigned j = 0; j < posiciones[i].size(); j++){
         if(posiciones[i][j] < min){
            min = posiciones[i][j];
         }
         if (posiciones[i][j] > max){
            max = posiciones[i][j];
         }
      }
   }
   for( int i = 0; i < n_cluster; i++){
      for( unsigned j = 0; j < posiciones[0].size(); j++){
         centroides[i].push_back(Randfloat(min,max-1));
      }
   }
   d_intracluster.resize(n_cluster);
   solucion.resize(posiciones.size());
   for( unsigned i = 0; i < solucion.size(); i++){
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
   for( unsigned i = 0; i < posiciones.size(); i++){
      for( unsigned j = 0; j < posiciones[i].size(); j++){
         std::cout << posiciones[i][j] << " ";
      }
      std::cout << std::endl;
   }

   std::map<std::pair<int,int>,int>::iterator it = restricciones.begin();
   for(; it != restricciones.end(); it++){
      std::cout << (*it).first.first << ", " << (*it).first.second << ": "  << (*it).second << std::endl;
   }

   std::cout << "Restricciones: " << restricciones.size() << std::endl;

   for( unsigned i = 0; i < centroides.size(); i++){
      for( unsigned j = 0; j < centroides[i].size(); j++){
         std::cout << centroides[i][j] << " ";
      }
      std::cout << std::endl;
   }
}

void CCP::mostrar_solucion(){
   std::cout << "Funcion Objetivo: " << f_objetivo << std::endl;
   std::cout << "Desviacion general: " << desv_gen << std::endl;
   std::cout << "Infactibilidad: " << infactibilidad << std::endl;
   double infactibilidad_aux = 0;
   /*for( unsigned i = 0; i < solucion.size(); i++){
      infactibilidad_aux += restricciones_incumplidas(i,solucion[i]) / 2;
   }*/
   std::cout << "Infactibilidad calculada: " << infactibilidad_aux << std::endl;
   std::cout << "Lambda: " << lambda << std::endl;
   std::cout << "Restricciones: " << restricciones.size() << std::endl;
   for( int j = 0; j < n_cluster; j++){
      std::cout << "Cluster " << j << " : ";
      for( unsigned k = 0; k < clusters[j].size(); k++){
         std::cout << clusters[j][k] << " ";
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
   for( unsigned j = 0; j < solucion.size(); j++){
      std::cout << solucion[j] << " ";
   }
   std::cout << std::endl;
   std::cout << std::endl;

   /*for( int i = 0; i < n_cluster; i++){
      std::cout << "Centroide: " << i << std::endl;
      for( unsigned j = 0; j < centroides[i].size(); j++){
         std::cout << centroides[i][j] << " ";
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;*/
}

void CCP::calcular_centroide(const int i){
   for( unsigned j = 0; j < centroides[i].size(); j++){
      centroides[i][j] = 0;
   }
   for( unsigned j = 0; j < clusters[i].size(); j++){
      for( unsigned k = 0; k < posiciones[clusters[i][j]].size(); k++){
            centroides[i][k] += (1.0/clusters[i].size()) * posiciones[clusters[i][j]][k];
      }
   }
}

void CCP::distancia_intracluster(const int i){
   double d_euclidea;
   for( int j = 0; j < n_cluster; j++){
      d_intracluster[j] = 0;
   }
   for( unsigned j = 0; j < clusters[i].size(); j++){
      for( unsigned k = 0; k < posiciones[clusters[i][j]].size(); k++){
         d_euclidea =  std::abs(posiciones[clusters[i][j]][k] - centroides[i][k]);
         d_euclidea *= d_euclidea;
         d_intracluster[i] += (1.0/clusters[i].size()) * d_euclidea;
      }
   }
}

void CCP::desviacion_general(){
   desv_gen = 0;
   for( int i = 0; i < n_cluster; i++){
      distancia_intracluster(i);
      desv_gen += (1.0/n_cluster)*d_intracluster[i];
   }
}

int CCP::buscar_cluster(const int n){
   for( int i = 0; i < n_cluster; i++){
      for( unsigned j = 0; j < clusters[i].size(); j++){
         if(clusters[i][j] == n){
            return i;
         }
      }
   }
   return -1;
}

void CCP::generar_solucion(){
   for( unsigned i = 0; i < solucion.size(); i++){
      solucion[i] = -1;
   }
   for( int i = 0; i < n_cluster; i++){
      for( unsigned j = 0; j < clusters[i].size(); j++){
         solucion[clusters[i][j]] = i;
      }
   }
}

double CCP::distancia_nodo_cluster(const int n, const int c){
   double d_euclidea = 0, componente = 0;
   for( unsigned i = 0; i < posiciones[n].size(); i++){
      componente = std::abs(posiciones[n][i] - centroides[c][i]);
      componente *= componente;
      d_euclidea += componente;
   }
   return d_euclidea;
}

double CCP::restricciones_incumplidas(const int n, const int c){
   double incumplidas = 0;
   std::pair<int,int> pareja;
   pareja.first = n;
   for( unsigned i = 0; i < clusters[c].size(); i++){
      pareja.second = clusters[c][i];
         auto it = restricciones.find(pareja);
         if(it->second == -1 && it != restricciones.end()){
            //std::cout << "Incumplido CL" << it->first.first << " con " << it->first.second << std::endl;
            incumplidas++;
         }
   }
   for( int i = 0; i < n_cluster; i++){
      if(i != c){
         for( unsigned j = 0; j < clusters[i].size(); j++){
            pareja.second = clusters[i][j];
               auto it = restricciones.find(pareja);
               if(it->second == 1 && it != restricciones.end()){
                  //std::cout << "Incumplido ML" << it->first.first << " con " << it->first.second << std::endl;
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

   int cluster = -1;
   double d_min, d, r_min;

   for( int i = 0; i < n_cluster; i++){
      pareja.first = restricciones_incumplidas(n,i);
      pareja.second = i;
      r.push_back(pareja);
   }

   std::sort(r.begin(),r.end());

   /*for( unsigned i = 0; i < r.size(); i++){
      std::cout << r[i]. first << " " << r[i].second << std::endl;
   }
   std::cout << "----------------------------------" << std::endl;*/

   r_min = r[0].first;
   d_min = 1000000.0;
   for( unsigned i = 0; i < r.size() && r[i].first == r_min; i++){
      d = distancia_nodo_cluster(n,r[i].second);
      if(d < d_min){
         d_min = d;
         cluster = r[i].second;
      }
   }

   infactibilidad += r_min;
   clusters[cluster].push_back(n);
}

void CCP::limpiar_clusters(){
   for( int i = 0; i < n_cluster; i++){
      clusters[i].clear();
   }
   infactibilidad = 0;
}

int CCP::greedy(){
   int i = 0, n_max = 100;
   bool cambio_c;
   std::vector<int> rsi;
   std::vector<std::vector<int>> solucion_ant = clusters;

   for( unsigned i = 0; i < posiciones.size(); i++){
      rsi.push_back(i);
   }

   std::random_shuffle(rsi.begin(), rsi.end(), Randint_shuffle);

   do {
      cambio_c = false;
      for( unsigned i = 0; i < rsi.size(); i++){
         asignar_cluster(rsi[i]);
      }
      for( int i = 0; i < n_cluster; i++){
         if(solucion_ant[i] != clusters[i]){
            calcular_centroide(i);
            cambio_c = true;
         }
      }
      solucion_ant = clusters;
      //mostrar_solucion();
      if(cambio_c){
         limpiar_clusters();
      }
      i++;
   } while(cambio_c && i < n_max);
   generar_solucion();
   desviacion_general();
   f_objetivo = desv_gen + infactibilidad;
   std::cout << "Iteraciones: " << i << std::endl;
   return i;
}

void CCP::generar_vecino(){
   bool salir = false;
   int pos, n, c;
   while(!salir && quedan_vecinos()){
      salir = false;
      pos = Randint(0,solucion.size()-1);
      n = Randint(0,n_cluster-1);
      auto it = vecindario.find(std::make_pair(pos,n));
      if(it != vecindario.end()){
         //std::cout << it->first.first << " " << it->first.second << " " << it->second << std::endl;
         salir = true;
         vecindario.erase(it);
         c = solucion[pos];
         solucion[pos] = -1;
         for( int i = 0; i < n_cluster; i++){
            clusters[i].clear();
         }
         for(unsigned j = 0; j < solucion.size(); j++){
            if(solucion[j] != -1){
               clusters[solucion[j]].push_back(j);
            }
         }
         infactibilidad -= restricciones_incumplidas(pos,c);
         infactibilidad += restricciones_incumplidas(pos,n);
         solucion[pos] = n;
         clusters[solucion[pos]].push_back(pos);
         //std::cout << infactibilidad << std::endl;
         //std::cout << infactibilidad << std::endl;
         //std::cout << "Cambio " << pos << " de " << c << " a " << n << std::endl;
         desviacion_general();
         f_objetivo = desv_gen + (infactibilidad*lambda);
         //std::cout << infactibilidad << std::endl;
      }
   }
}

void CCP::leer_vecino(){
   double infactibilidad_aux = infactibilidad;
   limpiar_clusters();
   infactibilidad = infactibilidad_aux;
   for( unsigned i = 0; i < solucion.size(); i++){
      clusters[solucion[i]].push_back(i);
      //infactibilidad += restricciones_incumplidas(i,solucion[i]);
      //std::cout << i << ", " << solucion[i] << ", " << infactibilidad << std::endl;
   }
   desviacion_general();
   if(lambda == 0){
      calcular_lambda();
   }
   f_objetivo = desv_gen + (infactibilidad*lambda);
}

void CCP::generar_vecindario(){
   vecindario.clear();
   for(unsigned i = 0; i < posiciones.size(); i++){
      for(int j = 0; j < n_cluster; j++){
         if(j != buscar_cluster(i) && clusters[buscar_cluster(i)].size() > (unsigned) 1){
            vecindario.insert(std::make_pair(i,j));
         }
      }
   }
}

bool CCP::quedan_vecinos(){
   if(vecindario.size() > 0){
      return true;
   }
   return false;
}

void CCP::solucion_inicial(){
   std::vector<int> index;
   std::vector<std::vector<int>> c;
   c.resize(n_cluster);

   for( unsigned i = 0; i < posiciones.size(); i++){
      index.push_back(i);
   }
   std::random_shuffle(index.begin(), index.end(), Randint_shuffle);
   auto it = index.begin();
   for( int i = 0; i < n_cluster; i++, it++){
      c[i].push_back(*it);
   }
   int random;
   for(; it != index.end(); it++){
      random = Randint(0,n_cluster-1);
      c[random].push_back(*it);
   }

   for( int i = 0; i < n_cluster; i++){
      for( unsigned j = 0; j < c[i].size(); j++){
         solucion[c[i][j]] = i;
      }
   }
}

double CCP::distancia_nodo_nodo(const int n, const int m){
   double d_euclidea = 0, componente = 0;
   for( unsigned i = 0; i < posiciones[n].size(); i++){
      componente = std::abs(posiciones[n][i] - posiciones[m][i]);
      componente *= componente;
      d_euclidea += componente;
   }
   return d_euclidea;
}

void CCP::calcular_lambda(){
   lambda = 0;
   double d, d_max = 0.0;
   int cluster;
   for( unsigned i = 0; i < posiciones.size(); i++){
      cluster = buscar_cluster(i);
      for(int j = 0; j < n_cluster; j++){
         if(j != cluster){
            for( unsigned k = 0; k < clusters.size(); k++){
               d = distancia_nodo_nodo(i,clusters[j][k]);
               if(d > d_max){
                  d_max = d;
               }
            }
         }
      }
   }
   lambda = d_max / restricciones.size();
}

void CCP::leer_solucion(){
   limpiar_clusters();
   for( unsigned i = 0; i < solucion.size(); i++){
      clusters[solucion[i]].push_back(i);
      //std::cout << i << ", " << solucion[i] << ", " << infactibilidad << std::endl;
   }
   for( unsigned i = 0; i < solucion.size(); i++){
      infactibilidad += restricciones_incumplidas(i,solucion[i]);
   }
   desviacion_general();
   if(lambda == 0){
      calcular_lambda();
   }
   infactibilidad /= 2;
   f_objetivo = desv_gen + (infactibilidad*lambda);
}

void CCP::busqueda_local(){
   double f_objetivo_ant, infactibilidad_ant;
   int i = 0;
   std::vector<int> solucion_ant;
   solucion_inicial();
   leer_solucion();
   generar_vecindario();
   f_objetivo_ant = f_objetivo;
   solucion_ant = solucion;
   infactibilidad_ant = infactibilidad;
   mostrar_solucion();

   do{
      /*auto it = vecindario.begin();
      for(; it != vecindario.end(); it++){
         std::cout << it->first << ", " << it->second << std::endl;
      }
      //std::cout << "Vecinos posibles: " << vecindario.size() << std::endl;
      infactibilidad_aux = infactibilidad_pos = 0;
      for( unsigned i = 0; i < solucion.size(); i++){
         infactibilidad_pos += restricciones_incumplidas(i,solucion[i]);
      }*/

      generar_vecino();
      i++;

      /*for( unsigned i = 0; i < solucion.size(); i++){
         infactibilidad_aux += restricciones_incumplidas(i,solucion[i]);
      }
      //if(infactibilidad <= infactibilidad_aux){
         std::cout << i << std::endl;
         std::cout << "Infactibilidad anterior al vecino: " << infactibilidad_pos << std::endl;
         std::cout << "Infactibilidad posterior al vecino: " << infactibilidad_aux << std::endl;
         std::cout << "Infactibilidad: " << infactibilidad << std::endl;
         //mostrar_solucion();
         //exit(1);
      //}
      */
      //mostrar_solucion();

      //std::cout << " FObj_ant: " << f_objetivo_ant << " FObj: " << f_objetivo << std::endl;

      if(f_objetivo < f_objetivo_ant){
         //std::cout << "Reinicio BL" << std::endl;
         //std::cout << "Infactibilidad: " << infactibilidad << std::endl;
         //std::cout << "Num Evaluaciones: " << i << std::endl;
         //mostrar_solucion();
         f_objetivo_ant = f_objetivo;
         solucion_ant = solucion;
         infactibilidad_ant = infactibilidad;
         generar_vecindario();
      }
      else{
         //mostrar_solucion();
         //std::cout << "Vecino no mejora" << std::endl;
         solucion = solucion_ant;
         //std::cout << "Nueva infactibilidad: " << infactibilidad << std::endl;
         infactibilidad = infactibilidad_ant;
         //std::cout << "Me quedo con: " << infactibilidad << std::endl;
         //leer_solucion();
      }
      if(!quedan_vecinos()){
         std::cout << "No quedan vecinos con los que probar" << std::endl;
         leer_vecino();
      }
      if(i >= 100000){
         std::cout << "Num Max Evaluaciones" << std::endl;
      }
   }while(i < 100000 && quedan_vecinos());
   std::cout << "Num Evaluaciones: " << i << std::endl;

}
