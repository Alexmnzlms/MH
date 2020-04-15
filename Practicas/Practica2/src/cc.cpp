#include "cc.h"

/////////////////////////////////////////////////////////////////////////////////
CCP::CCP(const int n, const std::string p, const std::string r){
   n_cluster = n;
   desv_gen = 0;
   infactibilidad = 0;
   lambda = 0;
   f_objetivo = 0;
   poblacion = 50;
   ind_eval = 0;
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

   calcular_lambda();
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
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

void CCP::calcular_lambda(){
   lambda = 0;
   double d, d_max = 0.0;
   for( int i = 0; i < (int) posiciones.size(); i++){
      for( int j = i+1; j < (int) posiciones.size(); j++){
         d = distancia_nodo_nodo(i,j);
         if(d > d_max){
            d_max = d;
         }
      }
   }
   lambda = d_max / restricciones.size();
   //std::cout << "Distancia maxima del conjunto: " << d_max << std::endl;
   //std::cout << "Numero de restricciones: " << restricciones.size() << std::endl;
   //std::cout << "Lambda: " << lambda << std::endl;
}

void CCP::infactibilidad_solucion(){
   infactibilidad = calcular_infact_sol(solucion);
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
double CCP::distancia_nodo_cluster(const int n, const int c){
   double d_euclidea = 0, componente = 0;
   for( unsigned i = 0; i < posiciones[n].size(); i++){
      componente = std::abs(posiciones[n][i] - centroides[c][i]);
      componente *= componente;
      d_euclidea += componente;
   }
   return d_euclidea;
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

double CCP::restricciones_incumplidas(const int n, const int c){
   double incumplidas = 0;
   std::pair<int,int> pareja;
   pareja.first = n;
   for( unsigned i = 0; i < clusters[c].size(); i++){
      pareja.second = clusters[c][i];
      auto it = restricciones.find(pareja);
      if(it->second == -1 && it != restricciones.end()){
         incumplidas++;
      }
   }
   for( int i = 0; i < n_cluster; i++){
      if(i != c){
         for( unsigned j = 0; j < clusters[i].size(); j++){
            pareja.second = clusters[i][j];
            auto it = restricciones.find(pareja);
            if(it->second == 1 && it != restricciones.end()){
               incumplidas++;
            }
         }
      }
   }
   return incumplidas;
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
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

   r_min = r[0].first;
   d_min = 1000000.0;
   for( unsigned i = 0; i < r.size() && r[i].first == r_min; i++){
      d = distancia_nodo_cluster(n,r[i].second);
      if(d < d_min){
         d_min = d;
         cluster = r[i].second;
      }
   }
   clusters[cluster].push_back(n);
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

void CCP::limpiar_clusters(){
   for( int i = 0; i < n_cluster; i++){
      clusters[i].clear();
   }
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
std::vector<int> CCP::crear_solucion(){
   std::vector<int> sol;
   std::vector<int> index;
   std::vector<std::vector<int>> c;
   c.resize(n_cluster);
   sol.resize(posiciones.size());

   for( unsigned i = 0; i < posiciones.size(); i++){
      index.push_back(i);
   }
   std::random_shuffle(index.begin(), index.end(), Randint_shuffle);
   auto it = index.begin();
   for( int i = 0; i < n_cluster; i++, ++it){
      c[i].push_back(*it);
   }
   int random;
   for(; it != index.end(); ++it){
      random = Randint(0,n_cluster-1);
      c[random].push_back(*it);
   }

   for( int i = 0; i < n_cluster; i++){
      for( unsigned j = 0; j < c[i].size(); j++){
         sol[c[i][j]] = i;
      }
   }

   return sol;
}

void CCP::solucion_inicial(){
   solucion = crear_solucion();

   for(int i = 0; i < n_cluster; i++){
      calcular_centroide(i);
   }
}

void CCP::generar_solucion(){
   for( int i = 0; i < n_cluster; i++){
      for( unsigned j = 0; j < clusters[i].size(); j++){
         solucion[clusters[i][j]] = i;
      }
   }
}

void CCP::generar_vecino(){
   bool salir = false;
   int pos, n;
   while(!salir && quedan_vecinos()){
      salir = false;
      pos = Randint(0,solucion.size()-1);
      n = Randint(0,n_cluster-1);
      auto it = vecindario.find(std::make_pair(pos,n));
      if(it != vecindario.end()){
         salir = true;
         vecindario.erase(it);
         for( int i = 0; i < n_cluster; i++){
            clusters[i].clear();
         }
         for(unsigned j = 0; j < solucion.size(); j++){
               clusters[solucion[j]].push_back(j);
         }
         solucion[pos] = n;
         clusters[solucion[pos]].push_back(pos);
         for( int i = 0; i < n_cluster; i++){
            calcular_centroide(i);
         }
         desviacion_general();
         infactibilidad_solucion();
         f_objetivo = desv_gen + (infactibilidad*lambda);
      }
   }
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

void CCP::leer_solucion(){
   limpiar_clusters();
   for( unsigned i = 0; i < solucion.size(); i++){
      clusters[solucion[i]].push_back(i);
   }
   for( int i = 0; i < n_cluster; i++){
      calcular_centroide(i);
   }
   desviacion_general();
   infactibilidad_solucion();
   f_objetivo = desv_gen + (infactibilidad*lambda);
}

void CCP::leer_vecino(){
   limpiar_clusters();
   for( unsigned i = 0; i < solucion.size(); i++){
      clusters[solucion[i]].push_back(i);
   }
   for(int i = 0; i < n_cluster; i++){
      calcular_centroide(i);
   }
   desviacion_general();
   f_objetivo = desv_gen + (infactibilidad*lambda);
}

bool CCP::quedan_vecinos(){
   if(vecindario.size() > 0){
      return true;
   }
   return false;
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
void CCP::generacion_inicial(){
   for(int i = 0; i < poblacion; i++){
      generacion.push_back(crear_solucion());
   }
   for(auto it = generacion.begin(); it != generacion.end(); ++it){
      f_generacion.push_back(evaluar_solucion(*it));
   }

   seleccionar_mejor();
}

int CCP::calcular_infact_sol(std::vector<int> & sol){
   int infactibilidad = 0;
   for(int i = 0; i < (int) sol.size(); i++){
      for(int j = i+1; j < (int) sol.size(); j++){
         std::pair<int,int> pareja = std::make_pair(i,j);
         auto it = restricciones.find(pareja);
         if(it != restricciones.end()){
            if(it->second == -1 && sol[i] == sol[j]){
               infactibilidad++;
            } else if(it->second == 1 && sol[i] != sol[j]){
               infactibilidad++;
            }
         }
      }
   }
   return infactibilidad;
}

double CCP::evaluar_solucion(std::vector<int> & sol){
   ind_eval++;

   std::vector<std::vector<double>> cent;
   std::vector<double> d_intra;
   std::vector<std::vector<int>> c;
   double desv_sol;
   double d_euclidea;
   int infact;
   double evaluacion;

   c.resize(n_cluster);
   for( int i = 0; i < (int) sol.size(); i++){
      c[sol[i]].push_back(i);
   }

   cent.resize(n_cluster);
   for( int i = 0; i < n_cluster; i++){
      cent[i].resize(posiciones[0].size());
   }
   for( int i = 0; i < n_cluster; i++){
      for(int j = 0; j < (int) posiciones[0].size(); j++){
         cent[i].push_back(0);
      }
   }
   for(int i = 0; i < n_cluster; i++){
      for( int j = 0; j < (int) c[i].size(); j++){
         for( int k = 0; k < (int) posiciones[c[i][j]].size(); k++){
               cent[i][k] += (1.0/c[i].size()) * posiciones[c[i][j]][k];
         }
      }
   }

   d_intra.resize(n_cluster);
   for(int i = 0; i < n_cluster; i++){
      for( int j = 0; j < n_cluster; j++){
         d_intracluster.push_back(0);
      }
      for( int j = 0; j < (int) c[i].size(); j++){
         for( int k = 0; k < (int) posiciones[c[i][j]].size(); k++){
            d_euclidea =  std::abs(posiciones[c[i][j]][k] - cent[i][k]);
            d_euclidea *= d_euclidea;
            d_intra[i] += (1.0/c[i].size()) * d_euclidea;
         }
      }
   }

   desv_sol = 0;
   for( int i = 0; i < n_cluster; i++){
      desv_sol += (1.0/n_cluster)*d_intra[i];
   }

   infact = calcular_infact_sol(sol);

   evaluacion = desv_sol + lambda*infact;

   return evaluacion;
}

std::vector<int> CCP::torneo_binario(){
   std::vector<int> ganadores;
   int index_a, index_b;
   for(int i = 0; i < poblacion; i++){
      index_a = Randint(0, poblacion-1);
      index_b = Randint(0, poblacion-1);
      if(f_generacion[index_a] <= f_generacion[index_b]){
         ganadores.push_back(index_a);
      } else {
         ganadores.push_back(index_b);
      }
   }

   return ganadores;
}

void CCP::seleccionar_mejor(){
   std::vector<int> mejor;
   int index_mejor = -1;
   double d_min = 100000000.0;
   for(int i = 0; i < (int) f_generacion.size(); i++){
      if(d_min > f_generacion[i]){
         d_min = f_generacion[i];
         index_mejor = i;
      }
   }

   mejor_generacion = generacion[index_mejor];
}

int CCP::seleccionar_peor(){
   int index_peor = -1;
   double d_max = -100000000.0;
   for(int i = 0; i < (int) f_generacion.size(); i++){
      if(d_max < f_generacion[i]){
         d_max = f_generacion[i];
         index_peor = i;
      }
   }

   return index_peor;
}

void CCP::seleccion(){
   std::vector<int> seleccionados = torneo_binario();
   std::vector<std::vector<int>> poblacion_seleccionada;
   std::vector<double> f_poblacion_seleccionada;

   for(int i = 0; i < (int) seleccionados.size(); i++){
      poblacion_seleccionada.push_back(generacion[seleccionados[i]]);
      f_poblacion_seleccionada.push_back(f_generacion[seleccionados[i]]);
   }

   generacion = poblacion_seleccionada;
   f_generacion = f_poblacion_seleccionada;
}

std::vector<int> CCP::operador_cruce_uniforme(std::vector<int> & p1, std::vector<int> & p2){
   int genoma = ((int) p1.size() / 2);
   int gen;
   std::set<int> genes;

   for(int i = 0; i < genoma; i++){
      gen = Randint(0,((int) p1.size())-1);
      auto it = genes.find(gen);
      if(it == genes.end()){
         genes.insert(gen);
      }
   }

   /*for(auto it = genes.begin(); it != genes.end(); ++it){
      std::cout << *it << std::endl;
   }*/

   std::vector<int> descendiente;
   for(int i = 0; i < (int) p1.size(); i++){
      auto it = genes.find(i);
      if(it != genes.end()){
         descendiente.push_back(p1[i]);
      } else {
         descendiente.push_back(p2[i]);
      }
   }
   return descendiente;
}

void CCP::cruce_uniforme(){
   int n_hijos = 2;
   std::vector<std::vector<int>> new_generacion;
   std::vector<int> desc;
   int p_cruce = (poblacion / 2) * 0.7;

   for(int i = 0; i < p_cruce; i++){
      for(int j = 0; j < n_hijos; j++){
         desc = operador_cruce_uniforme(generacion[i*2],generacion[i*2+1]);
         new_generacion.push_back(desc);
      }
   }
   for(int i = p_cruce*2; i < poblacion; i++){
      new_generacion.push_back(generacion[i]);
   }

   generacion = new_generacion;

   mutar_generacion();
   reparar_generacion();

   std::vector<double> f_new_generacion;
   for(int i = 0; i < (int) generacion.size(); i++){
      f_new_generacion.push_back(evaluar_solucion(generacion[i]));
   }
   f_generacion = f_new_generacion;

   conservar_elitismo();
}

void CCP::conservar_elitismo(){
   auto coincidencia = std::find(generacion.begin(), generacion.end(), mejor_generacion);

   if(coincidencia == generacion.end()){
      int sustituir = seleccionar_peor();
      generacion[sustituir] = mejor_generacion;
      f_generacion[sustituir] = evaluar_solucion(mejor_generacion);
   }
}

void CCP::reparar_solucion(std::vector<int> & sol){
   bool reparacion = false;
   int aleatorio = 0;
   int tam_sol = ((int) sol.size())-1;
   std::vector<std::vector<int>> c;
   std::vector<int> c_vacio;
   c.resize(n_cluster);

   for(int i = 0; i < (int) sol.size(); i++){
      c[sol[i]].push_back(i);
   }

   for(int i = 0; i < n_cluster; i++){
      if(c[i].empty()){
         reparacion = true;
         c_vacio.push_back(i);
      }
   }
   if(reparacion){
      for(auto it = c_vacio.begin(); it != c_vacio.end(); ++it){
         aleatorio = Randint(0, tam_sol);
         while(( (int) c[sol[aleatorio]].size()) <= 1){
            aleatorio = Randint(0, tam_sol);
         }

         c[sol[aleatorio]].erase(std::find(c[sol[aleatorio]].begin(), c[sol[aleatorio]].end(),aleatorio));
         sol[aleatorio] = *it;
         c[sol[aleatorio]].push_back(aleatorio);
      }
   }
}

void CCP::reparar_generacion(){
   for(int i = 0; i < (int) generacion.size(); i++){
      reparar_solucion(generacion[i]);
   }

}

void CCP::mutar_solucion(std::vector<int> & sol){
   int aleatorio, mutacion, p_mutacion = 1000;
   for(int i = 0; i < (int)sol.size(); i++){
      mutacion= Randint(1,p_mutacion);
      if(mutacion == 1){
         aleatorio = Randint(0,n_cluster-1);
         sol[i] = aleatorio;
      }
   }
}

void CCP::mutar_generacion(){
   for(int i = 0; i < (int) generacion.size(); i++){
      mutar_solucion(generacion[i]);
   }
}

void CCP::leer_mejor_generado(){
   limpiar_clusters();
   solucion = mejor_generacion;
   for( unsigned i = 0; i < solucion.size(); i++){
      clusters[solucion[i]].push_back(i);
   }
   for( int i = 0; i < n_cluster; i++){
      calcular_centroide(i);
   }
   desviacion_general();
   infactibilidad_solucion();
   f_objetivo = desv_gen + (infactibilidad*lambda);
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
int CCP::greedy(){
   int i = 0, n_max = 500;
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
   infactibilidad_solucion();

   f_objetivo = desv_gen + infactibilidad * lambda;
   return i;
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

   do{
      generar_vecino();
      i++;

      if(f_objetivo < f_objetivo_ant){
         f_objetivo_ant = f_objetivo;
         solucion_ant = solucion;
         infactibilidad_ant = infactibilidad;
         generar_vecindario();
      }
      else{
         solucion = solucion_ant;
         infactibilidad = infactibilidad_ant;
      }
      if(!quedan_vecinos()){
         //std::cout << "No quedan vecinos con los que probar" << std::endl;
         leer_vecino();
      }
      if(i >= 100000){
         //std::cout << "Num Max Evaluaciones" << std::endl;
      }
   }while(i < 100000 && quedan_vecinos());
   //std::cout << "Num Evaluaciones: " << i << std::endl;

}

void CCP::AGG_UN(){
   int generacion = 0;
   generacion_inicial();

   do{
      generacion++;
      seleccionar_mejor();
      //std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
      //std::cout << "Generacion: " << generacion << std::endl;
      //mostrar_generacion();
      //std::cout << std::endl << std::endl;

      seleccion();
      //std::cout << std::endl;
      //std::cout << "Seleccion" << std::endl;
      //mostrar_generacion();

      cruce_uniforme();
      //std::cout << std::endl << "Cruce" << std::endl;
      //mostrar_generacion();
      // std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
   }while(ind_eval < 100000);
   leer_mejor_generado();
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
void CCP::mostrar_datos(){
   std::cout << posiciones.size() << std::endl;
   for( unsigned i = 0; i < posiciones.size(); i++){
      for( unsigned j = 0; j < posiciones[i].size(); j++){
         std::cout << posiciones[i][j] << " ";
      }
      std::cout << std::endl;
   }

   std::map<std::pair<int,int>,int>::iterator it = restricciones.begin();
   for(; it != restricciones.end(); ++it){
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

void CCP::mostrar_solucion(bool completo){
   std::cout << "Funcion Objetivo: " << f_objetivo << std::endl;
   std::cout << "Desviacion general: " << desv_gen << std::endl;
   std::cout << "Infactibilidad: " << infactibilidad << std::endl;
   std::cout << "Lambda: " << lambda << std::endl;
   if(completo){
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
   }
}

std::vector<double> CCP::fila_datos(){
   std::vector<double> fila;
   fila.push_back(desv_gen);
   fila.push_back(infactibilidad);
   fila.push_back(lambda);
   fila.push_back(f_objetivo);

   return fila;
}

void CCP::mostrar_generacion(){
   for(int i = 0; i < (int) generacion.size(); i++){
      for(int j = 0; j < (int) generacion[i].size(); j++){
         std::cout << generacion[i][j];
      }
      std::cout << " F: " << f_generacion[i] << std::endl;
   }

   std::cout << "Mejor generado: ";
   for(int j = 0; j < (int) mejor_generacion.size(); j++){
      std::cout << mejor_generacion[j];
   }
   std::cout << " F: " << evaluar_solucion(mejor_generacion) << std::endl;

   std::cout << "Evaluaciones: " << ind_eval << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////
