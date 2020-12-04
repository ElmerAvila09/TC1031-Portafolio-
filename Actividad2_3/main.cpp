/*
Instituto Tecnologico de Estudios Superiores de Monterrey 
Equipo 4: 
Elmer Osiel Avila Vargas - A00826359
Carlos Enrique Lucio Dominguez - A00828524
Descripcion: Ordena los datos de bitacora.txt en forma ascendente por direccion ip a partir del algoritmo de ordenamiento bubleSort, luego permite al usuario realizar tantas consultas quiera de un rango de ip's, para encontrar las posiciones de las direcciones requeridas se hace una busqueda secuencial, y finalmente se crea un documento ordenado cuyo nombre el usuario ingresa.
Fecha de modifiacion:  10/10/2020
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#include "DoubleLinkedList.h"

/*
  Descripcion: Toma un registro completo en formato string y obtiene la dirección ip como string, la cuál será util para calcular la clave de cada Nodo.
  Entrada: Un registro en string.
  Salida: Dirección ip en string.
  Complejidad: O(1), constante.
*/
string calculateIP(string str){
  string word;
  stringstream s(str);

  for (int i=0; i<=3; i++){
    getline(s, word, ' ');
  }

  return word;
}

/*
  Descripcion: Realiza el proceso necesario para generar una llave a partir de una direccion ip.
  Entrada: El string de la ip del que se quiere generar la llave.
  Salida: Long, la llave segun el ip dado.
  Complejidad: O(n), lineal.
*/
long calculateKey(string ip){
  int idx = 0;
  long dato = 0;
  long key = 0;

  while (idx < ip.size()){
    if (ip[idx]!= '.' && ip[idx]!=':'){
      dato = dato*10 + ip[idx]-'0';
    }
    else{
      key = key*1000 + dato;
      dato = 0;
    }
    idx++;
  }

  key = key*10000 + dato;
  return key;
}

/*
  Descripcion: Lee el archivo "bitacora.txt" y por cada registro agrega un nuevo Nodo al final de la lista.
  Entrada: La lista por parametro de referencia.
  Salida: Ninguna.
  Complejidad: O(n), lineal. El while depende del numero de registros en el archivo.
*/
void leerArchivo(DoubleLinkedList &list){
  fstream bitacora;

  bitacora.open("bitacora.txt", ios::in); 
  string line;
  
  while (getline(bitacora, line)){ // getline() -> O(n)
    list.addLast(Info(line, calculateKey(calculateIP(line))));
  }

  bitacora.close();
}

int main(){
  DoubleLinkedList list;

  leerArchivo(list);
  list.bubbleSort();

  bool choice = true;
  string ipInit, ipFin;
  long ipI, ipF;
  
  while(choice){
    cout << "Ingresa la dirección IP inicial: ";
    cin >> ipInit;
    ipI = calculateKey(ipInit);
    
    cout << "Ingresa la dirección IP final: ";
    cin >> ipFin;
    ipF = calculateKey(ipFin);

    cout << endl;
    
    list.searchPrint(ipI, ipF);

    cout << endl << "¿Desea realizar otra consulta? (1) si, (0) no" << endl;
    cin >> choice;
    cout << endl;
  }

  list.saveData();
}