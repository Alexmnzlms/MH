#include "cc.h"

CCP::CCP(const int n, const std::string p, const std::string r){
   Set_random(2020);
   n_cluster = n;
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
         if (valor != 0 && j > i){
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
void CCP::calcular_centroide(int i){

}
void CCP::distancia_euclidea(){

}
void CCP::desviacion_general(){

}
void CCP::copkm(){

}
