#include "cc.h"

/////////////////////////////////////////////////////////////////////////////////
CCP::CCP(const int n, const std::string p, const std::string r){
   n_cluster = n;
   desv_gen = 0;
   infactibilidad = 0;
   lambda = 0;
   f_objetivo = 0;
   poblacion = 0;
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

void CCP::calc_f_objetivo(){
   f_objetivo = desv_gen + (infactibilidad * lambda);
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
      random = Randint(0,n_cluster);
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

void CCP::generar_vecino(bool bl){
   bool salir = false;
   int pos, n, c;
   while(!salir && quedan_vecinos()){
      salir = false;
      pos = Randint(0,solucion.size());
      n = Randint(0,n_cluster);
      std::pair<int,int> pareja = std::make_pair(pos,n);
      auto it = vecindario.find(pareja);
      if(it != vecindario.end()){
         salir = true;
         if(bl){
            vecindario.erase(it);
         }
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

         for( int i = 0; i < n_cluster; i++){
            calcular_centroide(i);
         }
         desviacion_general();
         //infactibilidad_solucion();
         calc_f_objetivo();
      }
   }
}

void CCP::generar_vecino_es(){
   bool salir = false;
   int pos, n, c;
   while(!salir){
      salir = false;
      pos = Randint(0,solucion.size());
      n = Randint(0,n_cluster);
      if((clusters[solucion[pos]].size() - 1) > 0){
         salir = true;
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

         for( int i = 0; i < n_cluster; i++){
            calcular_centroide(i);
         }
         desviacion_general();
         //infactibilidad_solucion();
         calc_f_objetivo();
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
   // std::cout << "F objetivo: " << f_objetivo << std::endl;
   // for(auto it = solucion.begin(); it != solucion.end(); ++it){
   //    std::cout << *it;
   // }
   // std::cout << std::endl;
   // for(auto it = vecindario.begin(); it != vecindario.end(); ++it){
   //    std::cout << "(" << it->first << "," << it->second << ")";
   // }
   // std::cout << std::endl;
}

void CCP::leer_solucion(int n){
   limpiar_clusters();
   for( unsigned i = 0; i < solucion.size(); i++){
      clusters[solucion[i]].push_back(i);
   }
   for( int i = 0; i < n_cluster; i++){
      calcular_centroide(i);
   }
   desviacion_general();
   if(n < 0){
      infactibilidad_solucion();
   } else {
      infactibilidad = n;
   }

   calc_f_objetivo();
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

std::vector<int> CCP::torneo_binario(int t){
   std::vector<int> ganadores;
   int index_a, index_b;
   index_a = index_b = -1;
   for(int i = 0; i < t; i++){
      while(index_a == index_b){
         index_a = Randint(0, (int)f_generacion.size());
         index_b = Randint(0, (int)f_generacion.size());
      }
      if(f_generacion[index_a] <= f_generacion[index_b]){
         ganadores.push_back(index_a);
      } else {
         ganadores.push_back(index_b);
      }
      index_a = index_b;
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
   f_mejor_generacion = evaluar_solucion(mejor_generacion);
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

void CCP::operador_seleccion(int t){
   std::vector<int> seleccionados = torneo_binario(t);

   for(int i = 0; i < (int) seleccionados.size(); i++){
      seleccion.push_back(generacion[seleccionados[i]]);
      f_seleccion.push_back(f_generacion[seleccionados[i]]);
   }
}

std::vector<int> CCP::operador_cruce_uniforme(std::vector<int> & p1, std::vector<int> & p2){
   int genoma = ((int) p1.size() / 2);
   int gen;
   std::set<int> genes;

   for(int i = 0; i < genoma; i++){
      gen = Randint(0,((int) p1.size()));
      auto it = genes.find(gen);
      if(it == genes.end()){
         genes.insert(gen);
      } else {
         i--;
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

std::vector<int> CCP::operador_cruce_segmento(std::vector<int> & p1, double f_p1, std::vector<int> & p2, double f_p2, int n){
   int r,v,tam = (int) p1.size();
   r = Randint(0, tam);
   v = Randint(0, tam);
   std::set<int> genes_dominantes;
   int genoma = ((tam - v) / 2);
   int gen;
   std::set<int> genes;

   for(int i = 0; i < v; i++){
      genes_dominantes.insert((r+i)%tam);
   }



   for(int i = 0; i < genoma; i++){
      gen = Randint(0,tam);
      auto it = genes.find(gen);
      auto dom = genes_dominantes.find(gen);
      if(it == genes.end() && dom == genes_dominantes.end()){
         genes.insert(gen);
      } else {
         i--;
      }
   }


   std::vector<int> mejor;
   std::vector<int> peor;

   if(f_p1 <= f_p2){
      mejor = p1;
      peor = p2;
   } else {
      mejor = p2;
      peor = p1;
   }

   std::vector<int> descendiente;
   for(int i = 0; i < tam; i++){
      auto it = genes_dominantes.find(i);
      if(n == 0){
         if(it != genes_dominantes.end()){
            descendiente.push_back(mejor[i]);
         } else {
            auto it = genes.find(i);
            if(it != genes.end()){
               descendiente.push_back(p1[i]);
            } else {
               descendiente.push_back(p2[i]);
            }
         }
      } else if(n == 1){
         if(it != genes_dominantes.end()){
            descendiente.push_back(peor[i]);
         } else {
            auto it = genes.find(i);
            if(it != genes.end()){
               descendiente.push_back(p1[i]);
            } else {
               descendiente.push_back(p2[i]);
            }
         }
      }

   }
   return descendiente;
}

void CCP::operador_cruce(int n, int s,double p){
   int n_hijos = 2;
   std::vector<std::vector<int>> new_seleccion;
   std::vector<int> desc;
   int p_cruce = (s / 2) * p;

   for(int i = 0; i < p_cruce; i++){
      for(int j = 0; j < n_hijos; j++){
         if(n == 0){
            desc = operador_cruce_uniforme(seleccion[i*2],seleccion[i*2+1]);
         } else if(n == 1){
            desc = operador_cruce_segmento(seleccion[i*2],f_seleccion[i*2],seleccion[i*2+1],f_seleccion[i*2+1]);
         }
         new_seleccion.push_back(desc);
      }
   }
   for(int i = p_cruce*2; i < s; i++){
      new_seleccion.push_back(seleccion[i]);
   }

   seleccion = new_seleccion;

   mutar_seleccion();
   reparar_seleccion();

   std::vector<double> f_new_seleccion;
   for(int i = 0; i < s; i++){
      f_new_seleccion.push_back(evaluar_solucion(seleccion[i]));
   }
   f_seleccion = f_new_seleccion;
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

void CCP::reparar_seleccion(){
   for(int i = 0; i < (int) seleccion.size(); i++){
      reparar_solucion(seleccion[i]);
   }

}

void CCP::mutar_solucion(std::vector<int> & sol){
   int aleatorio, mutacion, p_mutacion = 1000;
   for(int i = 0; i < (int)sol.size(); i++){
      mutacion= Randint(1,p_mutacion);
      if(mutacion == 1){
         aleatorio = Randint(0,n_cluster);
         sol[i] = aleatorio;
      }
   }
}

void CCP::mutar_seleccion(){
   for(int i = 0; i < (int) seleccion.size(); i++){
      mutar_solucion(seleccion[i]);
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
   calc_f_objetivo();
}

void CCP::aplicar_generacional(){
   generacion = seleccion;
   f_generacion = f_seleccion;
   conservar_elitismo();
   seleccion.clear();
   f_seleccion.clear();
}

void CCP::aplicar_estacionario(int n){
   std::vector<std::vector<int>> estacion;
   std::vector<double> f_estacion;
   std::vector<std::vector<int>> peores;
   std::vector<double> f_peores;
   int index_peor;

   double max, min;
   int i_max, i_min;

   for(int i = 0; i < n; i++){
      index_peor = seleccionar_peor();

      peores.push_back(generacion[index_peor]);
      f_peores.push_back(f_generacion[index_peor]);

      generacion.erase(std::find(generacion.begin(), generacion.end(), generacion[index_peor]));
      f_generacion.erase(std::find(f_generacion.begin(), f_generacion.end(), f_generacion[index_peor]));
   }

   std::vector<int> comprobado_peor;
   std::vector<int> comprobado_selec;

   for(int i = 0; i < n; i++){
      min = 100000000.0;
      max = -1*min;
      i_min = -1;
      i_max = i_min;
      for(int j = 0; j < n; j++){
         auto it = std::find(comprobado_selec.begin(), comprobado_selec.end(), j);
         if(f_seleccion[j] < min && it == comprobado_selec.end()){
            min = f_seleccion[j];
            i_min = j;
         }
      }
      for(int j = 0; j < n; j++){
         auto it = std::find(comprobado_peor.begin(), comprobado_peor.end(), j);
         if(f_peores[j] > max && it == comprobado_peor.end()){
            max = f_peores[j];
            i_max = j;
         }
      }

      if(f_seleccion[i_min] < f_peores[i_max]){
         estacion.push_back(seleccion[i_min]);
         f_estacion.push_back(f_seleccion[i_min]);
      } else{
         estacion.push_back(peores[i_max]);
         f_estacion.push_back(f_peores[i_max]);
      }
      comprobado_selec.push_back(i_min);
      comprobado_peor.push_back(i_max);
   }

   for(int i = 0; i < n; i++){
      generacion.push_back(estacion[i]);
      f_generacion.push_back(f_estacion[i]);
   }

   seleccion.clear();
   f_seleccion.clear();
}

bool CCP::mejor_valor(std::vector<int> & sol, double & f_sol, int i){
   double min = f_sol;
   int cluster_min = -1;
   std::vector<int> sol_comp;
   double f_sol_comp;
   std::vector<std::vector<int>> c;
   c.resize(n_cluster);
   for( int j = 0; j < (int) sol.size(); j++){
      c[sol[j]].push_back(j);
   }

   for(int j = 0; j < n_cluster; j++){
      sol_comp = sol;
      if(sol[i] != j && ((int) c[j].size()) > 1 ){
         sol_comp[i] = j;
         f_sol_comp = evaluar_solucion(sol_comp);
         if(min > f_sol_comp){
            cluster_min = j;
            min = f_sol_comp;
         }
      }
   }
   if(cluster_min == -1){
      return false;
   } else {
      sol[i] = cluster_min;
      f_sol = evaluar_solucion(sol);
      return true;
   }
}

void CCP::busqueda_local_suave(std::vector<int> & sol, double & f_sol){
   int i = 0;
   std::vector<int> rsi;
   int tam = (int) sol.size();
   bool mejora;
   int fallos;
   int umbral = 0.1*tam;
   for( int i = 0; i < tam; i++){
      rsi.push_back(i);
   }

   std::random_shuffle(rsi.begin(), rsi.end(), Randint_shuffle);

   mejora = true;
   while((mejora || fallos < umbral) && i < tam){
      if(mejor_valor(sol,f_sol,rsi[i])){
         mejora = true;
      } else {
         fallos++;
      }

      i++;
   }

}

void CCP::aplicar_BLS(double p, bool mejor){
   int probabilidad = p * ((int) generacion.size());
   std::vector<int> index_mejores;
   double f_mejor;
   int i_mejor;

   if(mejor){
      for(int i = 0; i < probabilidad; i++){
         f_mejor = 1000000.0;
         i_mejor = -1;
         for(int j = 0; j < (int) generacion.size(); j++){
            auto it = std::find(index_mejores.begin(), index_mejores.end(), j);
            if(f_generacion[j] < f_mejor && it == index_mejores.end()){
               i_mejor = j;
               f_mejor = f_generacion[j];
            }
         }
         //std::cout << "Aplico BLS al mejor: " << i_mejor << std::endl;
         index_mejores.push_back(i_mejor);
      }

      for(int i = 0; i < (int) index_mejores.size(); i++){
         busqueda_local_suave(generacion[index_mejores[i]], f_generacion[index_mejores[i]]);
      }

   } else {
      for(int i = 0; i < probabilidad; i++){
         //std::cout << "Aplico BLS: " << i << std::endl;
         busqueda_local_suave(generacion[i], f_generacion[i]);
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////
void CCP::mutacion_ILS(){
   std::vector<int> index;
   int tam = (int) solucion.size();
   int r = Randint(0,tam);
   int fin = ((r+(int)(0.1*tam))%tam) - 1;

   for(int i = r; i != fin+1; i = (i+1)%tam){
      index.push_back(i);
   }

   for(int i = 0; i < tam; i++){
      if(index.end() != std::find(index.begin(),index.end(),i)){
         solucion[i] = Randint(0,n_cluster);
      }
   }

   reparar_solucion(solucion);
   leer_solucion();
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
int CCP::greedy(bool v){
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

      if(v){
         mostrar_solucion(true);
      }

      if(cambio_c){
         limpiar_clusters();
      }
      i++;

   } while(cambio_c && i < n_max);

   generar_solucion();
   desviacion_general();
   infactibilidad_solucion();
   calc_f_objetivo();

   it_greedy = i;
   return i;
}

void CCP::busqueda_local(bool v, bool sol_ini, int neval, bool graph){
   double f_objetivo_ant, infactibilidad_ant;
   int i = 0;
   std::vector<int> solucion_ant;

   if(sol_ini){
      solucion_inicial();
   }

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
         if(v){
            mostrar_solucion(true);
         }
      }
      else{
         solucion = solucion_ant;
         infactibilidad = infactibilidad_ant;
      }
      if(graph){
         std::cout << i << " " << f_objetivo_ant << std::endl;
      }
   }while(i < neval && quedan_vecinos());
   //std::cout << "Num Evaluaciones: " << i << std::endl;
   leer_solucion();
   eval_bl = i;
}

void CCP::AG(int g, int n, bool v, bool graph, bool ignore_eval,int maxgen){
   int generacion = 0;
   int select = 0;
   double p_cruce = 0;
   poblacion = 50;
   int lim_eval = 100000;


   if(g == 0){
      select = poblacion;
      p_cruce = 0.7;
   } else {
      select = 2;
      p_cruce = 1;
   }

   if(ignore_eval){
      lim_eval = 0;
   }

   generacion_inicial();

   do{
      generacion++;
      seleccionar_mejor();

      if(graph){
         std::cout << generacion << " ";
         std::cout << f_mejor_generacion << std::endl;
      }

      if(v){
         std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
         std::cout << "Generacion: " << generacion << std::endl;
         mostrar_generacion();
         std::cout << std::endl << std::endl;

      }

      operador_seleccion(select);
      if(v){
         std::cout << std::endl;
         std::cout << "Seleccion" << std::endl;
         mostrar_seleccion();
         std::cout << "Generacion: " << generacion << std::endl;
      }


      operador_cruce(n,select,p_cruce);
      if(v){
         std::cout << std::endl << "Cruce" << std::endl;
         mostrar_seleccion();
         std::cout << "Generacion: " << generacion << std::endl;
         std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
      }

      if(g == 0){
         aplicar_generacional();
      } else {
         aplicar_estacionario(select);
      }


   }while(ind_eval < lim_eval || generacion < maxgen);
   leer_mejor_generado();
   gen_ag_am = generacion;
}

void CCP::AM(int n, double p, bool mejor, bool v, bool graph, bool ignore_eval,int maxgen){
   int generacion = 0;
   double p_cruce = 0.7;
   poblacion = 10;
   int select = poblacion;
   int lim_eval = 100000;

   if(ignore_eval){
      lim_eval = 0;
   }

   generacion_inicial();

   do{
      generacion++;
      seleccionar_mejor();

      if(graph){
         std::cout << generacion << " ";
         std::cout << f_mejor_generacion << std::endl;
      }

      if(v){
         std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
         std::cout << "Generacion: " << generacion << std::endl;
         mostrar_generacion();
         std::cout << std::endl << std::endl;
      }

      operador_seleccion(select);
      if(v){
         std::cout << std::endl;
         std::cout << "Seleccion" << std::endl;
         mostrar_seleccion();
         std::cout << "Generacion: " << generacion << std::endl;
      }

      operador_cruce(0,select,p_cruce);
      if(v){
         std::cout << std::endl << "Cruce" << std::endl;
         mostrar_seleccion();
         std::cout << "Generacion: " << generacion << std::endl;
         std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
      }

      aplicar_generacional();

      if(generacion%n == 0){
         aplicar_BLS(p,mejor);
      }

   }while(ind_eval < lim_eval || generacion < maxgen);//while(ind_eval < 100000 || generacion < 650);
   leer_mejor_generado();
   gen_ag_am = generacion;
}

void CCP::BMB(bool v){
   std::vector<int> mejor_sol;
   double f_sol;
   double mejor = 100000.0;
   int eval = 0;
   for(int i = 0; i < 10; i++){
      busqueda_local(v,true,10000);
      eval += eval_bl;
      f_sol = evaluar_solucion(solucion);
      if(f_sol < mejor){
         mejor_sol = solucion;
         mejor = f_sol;
      }
   }

   solucion = mejor_sol;
   leer_solucion();
   eval_bl = eval;
}

void CCP::ES(bool v, bool sol_ini, int neval, bool graph, int n_graph){
   double mu = 0.3;
   double phi = mu;

   if(sol_ini){
      solucion_inicial();
   }

   leer_solucion();

   double t_0 = (mu * f_objetivo) / (-1 * log(phi));
   double t_f = 0.001;//0.001;
   double t_actual = t_0;

   int max_vecinos = 10 * ((int) solucion.size());
   int max_exitos = 0.1 * max_vecinos;
   int vecinos, exitos = 1, eval = 0;
   double uniforme;

   std::vector<int> mejor_sol = solucion;
   double f_objetivo_mejor = f_objetivo;
   std::vector<int> solucion_acp = solucion;
   double f_objetivo_acp = f_objetivo;
   int infactibilidad_ant = infactibilidad;
   double diferencia;
   bool aceptacion;

   while(eval < neval && t_actual > t_f && exitos != 0){
      vecinos = 0;
      exitos = 0;

      while(vecinos < max_vecinos && exitos < max_exitos){
         infactibilidad_ant = infactibilidad;
         generar_vecino_es();
         vecinos++;
         eval++;
         diferencia = f_objetivo - f_objetivo_acp;
         uniforme = Rand();
         aceptacion = false;
         if(diferencia < 0){
            aceptacion = true;
         } else if (uniforme <= exp((-diferencia) / t_actual)){
            aceptacion = true;
         }
         if(aceptacion){
            exitos++;
            solucion_acp = solucion;
            f_objetivo_acp = f_objetivo;
            //leer_solucion();

            if(f_objetivo < f_objetivo_mejor){
               mejor_sol = solucion;
               f_objetivo_mejor = f_objetivo;
               if(v){
                  mostrar_solucion(true);
               }
            }
         } else {
            solucion = solucion_acp;
            leer_solucion(infactibilidad_ant);
         }

         if(v){
            std::cout << "--------------------------------------" << std::endl;
            std::cout << "TEMPERATURA INI: " << t_0 << std::endl;
            std::cout << "TEMPERATURA: " << t_actual << std::endl;
            std::cout << "Mejor solucion: " << f_objetivo_mejor << std::endl;
            std::cout << "Evaluaciones: " << eval << std::endl;
            std::cout << "Vecino actual: " << f_objetivo << std::endl;
            std::cout << "Ultimo aceptado: " << f_objetivo_acp << std::endl;
            std::cout << "Vecinos: " << vecinos << std::endl;
            std::cout << "Exitos: " << exitos << std::endl;
            std::cout << "Diferencia: " << diferencia << std::endl;
            std::cout << "Probabilidad: " << uniforme << std::endl;
            std::cout << "Metropoli: " << exp(-diferencia / t_actual) << std::endl;
            if( vecinos == exitos){
               std::cout << "YES" << std::endl;
            } else {
               std::cout << "NO - " << vecinos - exitos << std::endl;
            }
            if((diferencia < 0) /*|| (uniforme <= exp(-diferencia / t_actual))*/){
               std::cout << "ACEPTADO" << std::endl;
            } else {
               std::cout << "XXXXXXXX" << std::endl;
            }
            std::cout << "--------------------------------------" << std::endl;
         }
         if(graph){
            if(n_graph == 0){
               std::cout << eval << " " << f_objetivo << std::endl;
            } else if(n_graph == 1){
               std::cout << eval << " " << f_objetivo_acp << std::endl;
            } else {
               std::cout << eval << " " << f_objetivo_mejor << std::endl;
            }
         }
      }

      solucion = solucion_acp;
      f_objetivo = f_objetivo_acp;
      leer_solucion();
      // double beta = (t_0 - t_f) / ( (neval/max_vecinos)*t_0*t_f );
      // t_actual = t_actual / (1 + beta * t_actual);
      t_actual = t_actual * 0.9;
   }
   solucion = mejor_sol;
   leer_solucion();
   if(v){
      mostrar_solucion(true);
   }

   eval_bl = eval;
}

void CCP::ILS(int metodo, bool v){
   int eval = 0;
   solucion_inicial();
   leer_solucion();

   std::vector<int> mejor_sol = solucion;
   double f_mejor_sol = f_objetivo;

   for(int i = 0; i <= 10; i++){
      if(v){
         std::cout << "Inicial " << f_objetivo << std::endl;
      }

      if(metodo == 0){
         busqueda_local(v, false, 10000);
         leer_solucion();

      } else {
         ES(v, false, 10000);
         leer_solucion();
      }

      if(f_objetivo < f_mejor_sol){
         mejor_sol = solucion;
         f_mejor_sol = f_objetivo;
      }

      if(v){
         std::cout << "Final " << f_objetivo << std::endl;
         std::cout << "Mejor " << f_mejor_sol << std::endl;
         std::cout << "Iteracion " << i << std::endl;
      }

      solucion = mejor_sol;
      leer_solucion();
      mutacion_ILS();

      eval += eval_bl;

   }

   solucion = mejor_sol;
   leer_solucion();
   eval_bl = eval;
}

//////////////////////////////////////////////////////////////////////////////////
void CCP::iniciar_universe(){
   for(int i = 0; i < tam_multiverse; i++){
      universe.push_back(crear_solucion());
   }
}

void CCP::sort_universes(){
   sorted_universe.clear();

   double max = 0.0;
   for(int i = 0; i < tam_multiverse; i++){
      if(max < f_universe[i]){
         max = f_universe[i];
      }
   }

   std::vector<std::pair<double,int>> sorted;
   for(int i = 0; i < tam_multiverse; i++){
      sorted_universe.push_back(std::make_pair((f_universe[i]/max), i));
   }

   std::sort(sorted_universe.begin(), sorted_universe.end());
}

void CCP::normalize_inflation_rate(){
   double max = 0.0;
   for(int i = 0; i < tam_multiverse; i++){
      if(max < f_universe[i]){
         max = f_universe[i];
      }
   }

   for(int i = 0; i < tam_multiverse; i++){
      f_universe[i] = f_universe[i]/max;
   }
}

void CCP::evaluate_fitness(){
   f_universe.clear();
   for(auto it = universe.begin(); it != universe.end(); ++it){
      f_universe.push_back(evaluar_solucion(*it));
   }
}

int CCP::roulette_wheel_selection(){
   double suma = 0;
   for(int i = 0; i < tam_multiverse; i++){
      suma += (1.0 - f_universe[i]);
   }

   float random = Randfloat(0,suma);
   float acumulado = 0.0;
   int index = 0;

   // std::cout << "random: " << random << std::endl;

   while(random >= acumulado){
      // std::cout << "acumulado: " << acumulado << std::endl;
      acumulado += (1.0 - f_universe[index]);
      index++;
   }

   // std::cout << "index: " << index - 1 << std::endl;

   if(index - 1 >= tam_multiverse){
      return 0;
   }

   return index - 1;

}

void CCP::local_search_mvo(std::vector<int> & sol){
   int iter = 0, iter_max = 1000;
   int fallos = 0;
   double f_ant;
   std::vector<int> sol_ant;
   int infactibilidad_ant;

   solucion = sol;
   leer_solucion();

   int pos, n, c;
   bool salir;

   while(iter < iter_max && fallos < 500){
      sol_ant = solucion;
      f_ant = f_objetivo;
      infactibilidad_ant = infactibilidad;
      salir = false;

      while(!salir){
         salir = false;
         pos = Randint(0,solucion.size());
         n = Randint(0,n_cluster);
         if((clusters[solucion[pos]].size() - 1) > 0){
            salir = true;
            c = solucion[pos];
            solucion[pos] = -1;
            for( int i = 0; i < n_cluster; i++){
               clusters[i].clear();
            }
            for(unsigned j = 0; j < sol.size(); j++){
               if(solucion[j] != -1){
                  clusters[solucion[j]].push_back(j);
               }
            }
            infactibilidad -= restricciones_incumplidas(pos,c);
            infactibilidad += restricciones_incumplidas(pos,n);
            solucion[pos] = n;
            clusters[solucion[pos]].push_back(pos);

            for( int i = 0; i < n_cluster; i++){
               calcular_centroide(i);
            }
            desviacion_general();
            //infactibilidad_solucion();
            calc_f_objetivo();
         }
      }

      if(f_objetivo > f_ant){
         f_objetivo = f_ant;
         sol = sol_ant;
         infactibilidad = infactibilidad_ant;
         leer_solucion(infactibilidad);
         fallos++;
      }

      iter++;
   }

   sol = solucion;
}

void CCP::MVO(bool graph, int n, bool v){
   tam_multiverse = 30;
   iniciar_universe();
   int max_iter = 100000;
   int iter = 0;
   double min = 0.2;
   double max = 1.0;
   double p = (double) n_cluster;
   double wep, tdr = 0;
   int best_universe;
   double comp;
   bool exit = false;

   int black_hole_index, white_hole_index;
   evaluate_fitness();
   //normalize_inflation_rate();
   sort_universes();

   std::vector<int> mejor_sol = universe[sorted_universe[0].second];
   double f_mejor_sol;

   while(iter < max_iter && !exit){
      mejor_sol = universe[sorted_universe[0].second];



      for(int i = 0; i < tam_multiverse; i++){
         wep = min + iter * ((max - min)/max_iter);
         tdr = 1.0 - (pow(iter,1.0/p)/pow(max_iter,1.0/p));

         black_hole_index = i;
         for(int j = 0; j < (int) universe[i].size(); j++){
            double r1 = Rand();
            if(r1 < f_universe[i]){
               white_hole_index = roulette_wheel_selection();
               universe[black_hole_index][j] = universe[sorted_universe[white_hole_index].second][j];
            }
            double r2 = Rand();
            if(r2 < wep){
               double r3 = Rand();
               double r4 = Rand();
               best_universe = sorted_universe[0].second;
               int new_val = -1;
               if(r3 < 0.5){
                  new_val = universe[best_universe][j] + (int)(tdr * r4 * (n_cluster-1));
                  if(new_val > (n_cluster - 1)){
                     new_val = n_cluster - 1;
                  }
               } else {
                  new_val = universe[best_universe][j] - (int)(tdr * r4 * (n_cluster-1));
                  if(new_val < 0){
                     new_val = 0;
                  }
               }
               universe[i][j] = new_val;
               reparar_solucion(universe[i]);
            }
         }
         // mostrar_universo(iter);
      }
      evaluate_fitness();
      //normalize_inflation_rate();
      sort_universes();

      if(n == 1){
         f_mejor_sol = evaluar_solucion(mejor_sol);
         if( f_mejor_sol < evaluar_solucion(universe[sorted_universe[0].second])){
            universe[sorted_universe[tam_multiverse-1].second] = mejor_sol;
            f_universe[sorted_universe[tam_multiverse-1].second] = f_mejor_sol;
            //normalize_inflation_rate();
            sort_universes();
         }
      } else if (n == 2){
         if(iter > 0 && (iter % 10) == 0){
            for(int i = 0; i < 0.1*tam_multiverse; i++){
               local_search_mvo(universe[sorted_universe[i].second]);
               f_universe[sorted_universe[i].second] = evaluar_solucion(universe[sorted_universe[i].second]);
               //normalize_inflation_rate();
               sort_universes();
            }
         }
         f_mejor_sol = evaluar_solucion(mejor_sol);
         if( f_mejor_sol < evaluar_solucion(universe[sorted_universe[0].second])){
            universe[sorted_universe[tam_multiverse-1].second] = mejor_sol;
            f_universe[sorted_universe[tam_multiverse-1].second] = f_mejor_sol;
            //normalize_inflation_rate();
            sort_universes();
         }
      }

      // evaluate_fitness();
      // normalize_inflation_rate();
      // sort_universes();

      comp = 0;
      exit = false;
      for(int k = 0; k < tam_multiverse; k++){
         comp += sorted_universe[k].first;
      }
      if((comp / tam_multiverse) == 1.0 && (int)(tdr * (n_cluster-1)) == 0){
         exit = true;
      }

      if(graph){
         std::cout << iter << " " << evaluar_solucion(universe[sorted_universe[0].second]) << std::endl;
      }

      if(v){
        mostrar_universo(iter);
        std::cout << "WEP: " << wep << std::endl;
        std::cout << "TDR: " << tdr << std::endl;
      }


      iter++;
   }
   solucion = universe[sorted_universe[0].second];
   it_greedy = iter;
   leer_solucion();
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
   std::cout << "Real: " << calcular_infact_sol(solucion) << std::endl;
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
         std::cout << solucion[j];
      }
      std::cout << std::endl;
      std::cout << std::endl;
   }
}

std::vector<double> CCP::fila_datos(int n){
   std::vector<double> fila;
   fila.push_back(desv_gen);
   fila.push_back(infactibilidad);
   fila.push_back(lambda);
   fila.push_back(f_objetivo);
   if(n == 0){
      fila.push_back(it_greedy);
   } else if(n == 1){
      fila.push_back(eval_bl);
   } else if(n == 2){
      fila.push_back(gen_ag_am);
      fila.push_back(ind_eval);
   }

   return fila;
}

void CCP::mostrar_generacion(){
   std::cout << "Tamaño de la poblacion: " << (int) generacion.size() << std::endl;

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
   std::cout << " F: " << f_mejor_generacion << std::endl;

   std::cout << "Evaluaciones: " << ind_eval << std::endl;
}

void CCP::mostrar_universo(int n){
   std::cout << "Tamaño de la poblacion: " << (int) universe.size() << std::endl;

   for(int i = 0; i < (int) universe.size(); i++){
      for(int j = 0; j < (int) universe[i].size(); j++){
         std::cout << universe[i][j];
      }
      std::cout << " F: " << f_universe[i] << std::endl;
   }

   std::cout << "Mejor generado: ";
   for(int j = 0; j < (int) universe[sorted_universe[0].second].size(); j++){
      std::cout << universe[sorted_universe[0].second][j];
   }
   std::cout << " F: " << f_universe[sorted_universe[0].second] << std::endl;
   //std::cout << "F(normalized): " << sort_universes[0].first << std::endl;
   std::cout << "Evaluaciones: " << n << std::endl;
}

void CCP::mostrar_seleccion(){
   std::cout << "Tamaño de la seleccion: " << (int) seleccion.size() << std::endl;
   for(int i = 0; i < (int) seleccion.size(); i++){
      for(int j = 0; j < (int) seleccion[i].size(); j++){
         std::cout << seleccion[i][j];
      }
      std::cout << " F: " << f_seleccion[i] << std::endl;
   }

   std::cout << "Mejor generado: ";
   for(int j = 0; j < (int) mejor_generacion.size(); j++){
      std::cout << mejor_generacion[j];
   }
   std::cout << " F: " << f_mejor_generacion << std::endl;

   std::cout << "Evaluaciones: " << ind_eval << std::endl;
}

void CCP::mostrar_agm(){
   std::cout << gen_ag_am << " " << f_objetivo << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////
