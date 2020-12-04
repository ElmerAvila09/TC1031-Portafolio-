/*
Instituto Tecnológico y de Estudios Superiores de Monterrey.
Act 5.2 - Actividad Integral sobre el uso de códigos hash.
Programación de Estructuras de Datos y Algoritmos Fundamentales.
Carlos Enrique Lucio Domínguez | A00828524
Elmer Osiel Avila Vargas       | A00826359
Descripción: En esta aplicación se realiza una lectura del archivo de bitacora, crea una tabla hash cuya llave sea el ip (sin puerto) y cuyo valor sea un resumen de ese dominio. Este resumen incluye, el número de accesos, así como las fechas y razones de la falla. Finalmente se pueden hacer tantas consultas como el usuario quiera sobre las ips y su informacion.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*
  Descripcion: Reorganiza una linea de informacion completa en atributos de ip, fecha y error.
  Entrada: Una línea de texto con el registro y una variable ip, date y error por referencia.
  Salida: Ninguna.
  Complejidad: O(n), generalmente lineal debido a la función getline().
*/
void reorderInfo(string line, string &ip, string &date, string &error){
  stringstream registry(line);
  date = line.substr(0,15);

  for(int i=0; i<4; i++){
    getline(registry, ip, ' '); 
  }
  ip = ip.substr(0, ip.find(":"));
  getline(registry, error);
}

int main(){
  string line, ip, date, error;
  unordered_map<string, vector<pair<string, string>>> ips;
  
  fstream bitacora;
  bitacora.open("bitacoraACT5_2.txt", ios::in);
  
  // Llenado de informacion en la hash table.
  while(getline(bitacora, line)){
    reorderInfo(line, ip, date, error);
    
    auto got = ips.find (ip);
    if ( got != ips.end() ){
      ips[ip].push_back(make_pair(date, error));
    }
    else{
      vector<pair<string, string>> newPair(1, make_pair(date, error));
      ips[ip] = newPair;
    }
  }

  // Consulta de informacion de las ips
  string choice = "1";
  while(choice == "1"){
      
    cout << "Write the IP which you want to display the info (without the port): ";
    cin >> ip;

    auto got = ips.find (ip);
    if ( got != ips.end() ){
      cout << endl;
      cout << "IP: " << ip << "\nAccess quantity: " << ips[ip].size()<< endl;
      cout << "\nSummary" << endl;
      cout << "Date:\t\t\t Error:" << endl;
      for (int i=0; i<ips[ip].size(); i++){
        cout << ips[ip][i].first << "  " << ips[ip][i].second << endl;
      }
    }
    else{
      cout << endl;
      cout << "The IP was not found" << endl;
    }
    
    cout << endl;
    cout << "Would you like to try another IP? (1) -> Yes, (0) -> No" << endl;
    cin >> choice;
    cout << endl;
  }
}