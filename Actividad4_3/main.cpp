/*
Instituto Tecnológico y de Estudios Superiores de Monterrey.
Actividad 4.3. Actividad Integral de Grafos.
Programación de Estructuras de Datos y Algoritmos Fundamentales.
Carlos Enrique Lucio Domínguez | A00828524
Elmer Osiel Avila Vargas       | A00826359
Descripción: En esta aplicación se realiza una lectura del archivo de bitacora, donde se da una cantidad de nodos y arcos a leer, para después ser representados por una lista de adjacencia. Por otro lado, se determina el botmaster y la cantidad de salidas desde su ip mediante el uso de un unordered_map.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
  int n, m, iSalida, iEntrada;
  unordered_map<string, pair<int, int>> nodosIps;
  
  fstream bitacora;
  string line, ipSalida, ipEntrada;

  bitacora.open("bitacoraACT4_3(B).txt", ios::in);
  bitacora >> n >> m;
  getline(bitacora, line);
  
  vector<vector<int>> listAdj(n);

  // Llenado del unordered_map. Se le asigna numero de nodo a las ips lo cual servira al momento
  // de crear la lista de adyacencia, ademas se inicializa un outdregree de 0
  for (int i=0; i<n; i++){
    getline(bitacora, line);
    pair<int, int> datos;
    datos.first = i;
    datos.second = 0;
    nodosIps[line] = datos;
  }
  
  // Complejidad del llenado de la lista de adyacencias: O(m).
  for(int i=0; i<m; i++){
    getline(bitacora, line);
    stringstream registro(line);
    for (int a=0; a<4; a++){
      getline(registro, ipSalida, ' ');
    }

    ipSalida = ipSalida.substr(0, ipSalida.find(":"));
    getline(registro, ipEntrada, ' ');
    ipEntrada = ipEntrada.substr(0, ipEntrada.find(":"));
    // Llenado outdregree
    nodosIps[ipSalida].second++;

    iSalida = nodosIps[ipSalida].first;
    iEntrada = nodosIps[ipEntrada].first;
    
    // Llenado de la lista de adyacencia
    listAdj[iSalida].push_back(iEntrada);
  }

  int max = 0;
  vector<string> maxIps;

  // Comparaciones en el outdregree de los nodos para determinar los botmasters y la cantidad de
  // salidas desde su ip.
  for (pair<string, pair<int, int>> x : nodosIps){ 
    //cout << x.first << " " << x.second.first << " " << x.second.second << endl;
    if(x.second.second > max){
      maxIps.erase(maxIps.begin(), maxIps.end());
      max = x.second.second;
      maxIps.push_back(x.first);
    }

    else if(x.second.second == max){
      maxIps.push_back(x.first);
    }
  }
  
  // Desplegado de los resultados
  // Complejidad: O(n), lineal.
  cout << "Mayor cantidad de salidas: " << max << endl;
  for(int i=0; i<maxIps.size(); i++){
    cout << "Ip: " << maxIps[i] << endl;
  }
}
