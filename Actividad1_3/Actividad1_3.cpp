/*
Instituto Tecnologico de Estudios Superiores de Monterrey 
Equipo 4: 
Elmer Osiel Avila Vargas  -  A00826359
Carlos Enrique Lucio Dominguez -  A00828524
Descripcion: Ordena un los datos de bitacora.txt por fecha, dia y hora a partir del algoritmo de ordenamiento merge, luego permite al usuario realizar tantas consultas quiera de un rango de fechas, para encontrar las posiciones de las fechas se utiliza el metodo de busqueda binaria, y finalmente crea un documento ordenado con el nombre que el usuario le de.
Fecha de modifiacion:  12/9/2020
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

struct Registro{

  int llave = 0;
  string info;

  /*Metodo constructor de la estructura que guarda el string recibido en su atrubuto info.
    Entrada: Un string de informacion a guardar.
    Salida: Ninguna.
    Complejidad: O(1), constante.
  */
  Registro(string str){
    info = str;
  }

  /* Cambia el mes de letras a un numero de tipo string que luego se concatenara para la llave.
    Entrada: Un string del mes a cambiar.
    Salida: Un string del numero del mes.
    Complejidad: O(1), constante.
  */
  string cambiarMes(string mes){
    string numMes;
    
    if(mes == "Jan")
      numMes = "1";
    else if(mes == "Feb")
      numMes = "2";
    else if(mes == "Mar")
      numMes = "3";
    else if(mes == "Apr")
      numMes = "4";
    else if(mes == "May")
      numMes = "5";
    else if(mes == "Jun")
      numMes = "6";
    else if(mes == "Jul")
      numMes = "7";
    else if(mes == "Aug")
      numMes = "8";
    else if(mes == "Sep")
      numMes = "9";
    else if(mes == "Oct")
      numMes = "10";
    else if(mes == "Nov")
      numMes = "11";
    else
      numMes = "12";
    return numMes;
  }

  /* En caso de ser necesario cambia el formato del string del dia a dos digitos, ejemplo: de 9 a 09
    Entrada: Un string del dia a cambiar.
    Salida: Un string del numero del dia en formato de doble digito.
    Complejidad: O(1), constante.
  */
  string cambiarDia(string dia){
    string numDia;
    if (dia.size()==1){ // size() -> O(1)
      numDia = "0" + dia;
    }
    else{
      numDia = dia;
    }
    return numDia;
  }

  /* Cambia el formato de la hora a un numero con 6 digitos consecutivos, retirando asi los dos puntos (:) que se usara como parte de la llave.
    Entrada: Un string de la hora a cambiar.
    Salida: Un string del numero de la hora con formato para la llave.
    Complejidad: O(1), constante, el ciclo for no depende de una variable.
  */
  string cambiarHora(string hora){
    string word, hour, min, seg, numHora;
    stringstream s(hora);
    
    for (int i=1; i<=3; i++){
      if (i==1){
        getline(s, word, ':'); // O(n)
        hour = word;
      }
      else if (i==2){
        getline(s, word, ':'); // O(n)
        min = word;
      }
      else{
        getline(s, word, ' '); // O(n)
        seg = word;
      }
    }
    
    numHora = hour+min+seg;
    return numHora;
  }

  /* Realiza el proceso necesario para generar la llave que se utilizara para el ordenamiento del .txt
    Entrada: Un entero n que definira la longitud de la llave, de tal manera que sera hasta el mes, dia u hora.
    Salida: Ninguna.
    Complejidad: O(n), lineal. El ciclo for depende de la variable n.
  */
  void calcularLlave(int n){
    string word, dia, mes, hora, strllave = "";
    stringstream s(info);

    for (int i=1; i<=n; i++){
      if (i==1){
        getline(s, word, ' '); // O(n)
        mes = word;
        strllave += cambiarMes(mes); // O(1)
      }
      else if (i==2){
        getline(s, word, ' '); // O(n)
        dia = word;
        strllave += cambiarDia(dia); // O(1)
      }
      else{
        getline(s, word, ' '); // O(n)
        hora = word;
        strllave += cambiarHora(hora); // O(1)
      }
    }

    llave = stoi(strllave); // O(n)
  }
};

/* Lee el archivo "bitacora.txt" y por cada registro crea una instancia de la estructura Registro, la cual es añadida al vector apuntador.
  Entrada: Un vector apuntador de los registros.
  Salida: Ninguna.
  Complejidad: O(n), lineal. El while depende del numero de registros en el archivo.
*/
void leerArchivo(vector<Registro*> &Registros){
  fstream bitacora;

  bitacora.open("bitacora.txt", ios::in); 
  string line;

  while (getline(bitacora, line)){ // getline() -> O(n)
    Registros.push_back(new Registro(line));
  }

  bitacora.close();
}
/* Une la division de subarreglos que realiza el metodo merge
  Entrada: Un vector<Registro*> con los n registros, un vector auxiliar con la misma cantidad de espacios, un entero de posicion inicial para el vector y un entero de posicion final.
  Salida: Ninguna.
  Complejidad: O(n) ya que solo hay ciclos dependientes de variables y no anidados, cuya sumatoria elimina el coeficiente debido a que no tiene gran relevancia.
*/
void une(vector<Registro*> &vec, vector<Registro*> &aux, int ini, int fin){

    int m = (ini + fin) / 2;
    int i = ini, j = m+1, k = ini;
    while(i<=m && j<=fin){
        if(vec[i]->llave <= vec[j]->llave){
            aux[k++] = vec[i++];
        }
        else{
            aux[k++] = vec[j++];
        }
    }
    while (i <=m){
        aux[k++] = vec[i++];
    }
    while(j <= fin){
        aux[k++] = vec[j++];
    }
    for(int z=ini; z<=fin;z++){
        vec[z] = aux[z];
    }
}

/* Ordena en forma ascendente los registros con el método Merge, utilizando la llave de cada instancia.
  Entrada: Un vector<Registro*> con los n registros, un vector auxiliar con la misma cantidad de espacios, un entero de posicion inicial para el vector y un entero de posicion final.
  Salida: Ninguna.
  Complejidad: O(n log n)
*/
void merge(vector<Registro*> &vec, vector<Registro*> &aux, int ini, int fin){
    if(ini < fin){
        int m = (ini + fin) / 2;
        merge(vec, aux, ini, m);
        merge(vec, aux, m+1, fin);
        une(vec, aux, ini, fin); // O(n)
    }
}

/*  Busca el registro inicial o final del rango establecido por el usuario con la llave mas grande o mas chica a partir de la busqueda binaria.
  Entrada: El vector<Registro*> con los registros ordenados, el entero de la llave a buscar y un booleano para determinar si la busqueda es para el registro inicial o final.
  Salida: Un entero de la posicion del registro buscado en el vector, ya sea inicial o final.
  Complejidad: O(log n), logaritmica.
*/
int busqBinaria(vector<Registro*> &vec, int n, bool inicio){
  int ini = 0, fin = vec.size() - 1, mit;
  
  if (inicio){
    while(ini <= fin){
      mit = (ini + fin) / 2;
      if((vec[mit]->llave)/1000000 == n && (vec[mit - 1] -> llave)/1000000 != n){
          return mit;
      }
      else if((vec[mit]->llave)/1000000 >= n){
          fin = mit - 1;
      }
      else{
          ini = mit + 1;
      }
    }

    return -1;
  }
  else{
    while(ini <= fin){

      mit = (ini + fin) / 2;
      if((vec[mit]->llave)/1000000 == n && (vec[mit + 1] -> llave)/1000000 != n){
          return mit;
      }
      else if((vec[mit]->llave)/1000000 <= n){
          ini = mit + 1;
      }
      else{
          fin = mit - 1;
      }
    }

    return -1;
  }

}

int main(){

  vector<Registro*> registros;
  leerArchivo(registros); // O(n)

  int tam = registros.size(), posIni, posFin; // size() -> O(1)

  vector<Registro*> aux(tam); // O(1)

  for (int i=0; i<=tam-1; i++){ // O(n)
    registros[i] -> calcularLlave(3);
  }

  merge(registros, aux, 0, tam-1); // O(n log n)

  string inicio, fi;
  bool des = true;

  fstream salida;
  string nomSalida;
  
  while(des){ // O(n)
    cout << "Ingresa la fecha inicial (Formato: Aug 24): ";
    getline(cin, inicio); // O(n)

    Registro ini(inicio); // O(1)
    ini.calcularLlave(2); // O(n)
    
    cout << "Ingresa la fecha final (Formato: Aug 25): ";
    getline(cin, fi); // O(n)
    cout << endl;

    Registro fin(fi); // O(1)
    fin.calcularLlave(2); // O(n)

    if(ini.llave <= (registros[0]->llave)/1000000){
      posIni = 0;
    }
    else if (ini.llave > (registros[tam-1]->llave)/1000000){
      posIni = -1;
    }
    else{
      posIni = busqBinaria(registros, ini.llave, true);
    }

    if(fin.llave >= (registros[tam-1]->llave)/1000000){
      posFin = tam-1;
    }
    else if(fin.llave < (registros[0]->llave)/1000000){
      posFin = -1;
    }
    else{
      posFin = busqBinaria(registros, fin.llave, false);
    }
    
    if(posIni == -1 || posFin == -1){
      cout << "Sin coincidencias/Fecha Invalida" << endl;
    }
    else{
      for(int i = posIni; i <= posFin; i++){ // O(n)
      cout << registros[i] -> info << endl;
      }
    }

    cout << endl << "¿Desea realizar otra consulta? (1) si, (0) no" << endl;
    cin >> des;
    cin.ignore();
  }

  cout << "Ingresa el nombre de salida del archivo con los registros ordenados: ";
  cin >> nomSalida;
  salida.open(nomSalida + ".txt", ios::out);

  for (int i=0; i<=tam-1; i++){ // O(n)
    salida << registros[i]->info << endl;
  }

  salida.close();
}