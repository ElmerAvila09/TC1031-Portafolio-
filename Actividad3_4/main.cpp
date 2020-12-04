/*
Instituto Tecnologico de Estudios Superiores de Monterrey 
Equipo 4: 
Elmer Osiel Avila Vargas - A00826359
Carlos Enrique Lucio Dominguez - A00828524
Descripcion: Almacena todos las ip distintas sin considerar el puerto junto a la cantidad de accesos tiene, del documento "bitacoraOrdenada", en una estructura tipo BST. Ordena los nodos considerando la cantidad de accesos y en segunda instancia la ip. Finalmente desplieg las 5 ips que tienen mas accesos.
Fecha de modifiacion:  25/10/2020
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<queue>

using namespace std;

#include "BST.h"

/*
  Descripcion: Toma un registro completo en formato string y obtiene la dirección ip sin el puerto.
  Entrada: Un registro en string.
  Salida: Dirección ip en string.
  Complejidad: O(n), lineal.
*/
string calculateIP(string str){
  string word;
  stringstream s(str);

  for (int i=0; i<=3; i++){
    getline(s, word, ' '); // getline() -> O(n)
  }

  word = word.substr(0, word.find(":")); // substr -> O(n)

  return word;
}

/*
  Descripcion: Genera una numero entero a partir de una direccion ip.
  Entrada: El string de la ip del que se quiere generar un numero.
  Salida: Long, la ip numerica.
  Complejidad: O(n), lineal.
*/
long calulateIPNum(string ip){
  int idx = 0;
  long dato = 0;
  long IPInt = 0;

  while (idx < ip.size()){
    if (ip[idx]!= '.'){
      dato = dato*10 + ip[idx]-'0';
    }
    else{
      IPInt = IPInt*1000 + dato;
      dato = 0;
    }
    idx++;
  }

  IPInt = IPInt*1000 + dato;
  return IPInt;
}

/*
  Descripcion: Lee el archivo "bitacora.txt" y por cada ip distinta agrega un nuevo
  nodo a la estructura, junto a la cantidad de accesos que tiene.
  Entrada: La estructura por parametro de referencia.
  Salida: Ninguna.
  Complejidad: O(n), lineal.
*/
void readFile(BST &tree){
  fstream bitacora;

  bitacora.open("bitacoraOrdenada.txt", ios::in); 
  string line, prev = "";
  
  getline(bitacora, prev);
  prev = calculateIP(prev);

  int counter = 1;

  while (getline(bitacora, line)){ // getline() -> O(n)

    line = calculateIP(line);

    if (line != prev){
      Info info(prev, calulateIPNum(prev), counter);
      tree.add(info);
      
      prev = line;
      counter = 1;
    }
    else{
      counter++;
    }

  }
  Info info(prev, calulateIPNum(prev), counter);
  tree.add(info);
  
  bitacora.close();
}

int main() {
  BST tree;
  readFile(tree);

  queue<Info> q;
  tree.inOrderCPrint(q, 5);
}