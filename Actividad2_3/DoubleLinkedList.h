/*
Instituto Tecnologico de Estudios Superiores de Monterrey 
Equipo 4: 
Elmer Osiel Avila Vargas - A00826359
Carlos Enrique Lucio Dominguez - A00828524
Descripcion: Clase DoubleLinkedList que permite agregar nuevos nodos,
ordenarlos por ip, imprimirlos, eliminarlos y guardarlos en un archivo txt.
*/

#include "Node.h"

class DoubleLinkedList{
  public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    void addFirst(Info data);
    void addLast(Info data);
    void print();
    void searchPrint(long init, long fin);
    bool isEmpty();
    void bubbleSort();
    void deleteAll();
    void saveData();
  
  private:
    Node *head, *tail;
    int size;
};

/*
Metodo constructo
Complejidad: O(1), constante
*/
DoubleLinkedList::DoubleLinkedList(){
  head = nullptr;
  tail = nullptr;
  size = 0;
}

/*
Metodo destructor.
Complejidad: O(n), lineal.
*/
DoubleLinkedList::~DoubleLinkedList(){
  deleteAll();
}

/*
  Descripcion: Agrega un nuevo nodo al comienzo de la lista doblemente encadenada.
  Entrada: Una estructura con los datos del nodo.
  Salida: Ninguna.
  Complejidad: O(1), constante.
*/
void DoubleLinkedList::addFirst(Info data){
  Node *temp = head;

  head = new Node(data, nullptr, head);
  size++;

  if (isEmpty()){
    tail = head;
  }
  else{
    temp->setPrevious(head);
  }
}

/*
  Descripcion: Agrega un nuevo nodo al final de la lista doblemente encadenada.
  Entrada: Una estructura con los datos del nodo.
  Salida: Ninguna.
  Complejidad: O(1), constante.
*/
void DoubleLinkedList::addLast(Info data){
  Node *temp = tail;

  tail = new Node(data, tail, nullptr);  
  size++;

  if (isEmpty()){
    head = tail;
  }
  else{
    temp->setNext(tail);
  }
}

/*
  Descripcion: Imprime toda la lista doblemente encadenada.
  Entrada: Ninguna.
  Salida: Ninguna.
  Complejidad: O(n), lineal.
*/
void DoubleLinkedList::print(){
  Node *curr = head;
  while (curr != nullptr){
    cout << curr->getData().registry << endl;
    curr = curr->getNext();
  }
}

/*
  Descripcion: Imprime un rango registros segun las llaves de 2 direcciones ip.
  Entrada: Dos numeros long que definiran el rango a imprimir.
  Salida: Ninguna.
  Complejidad: O(n), lineal.
*/
void DoubleLinkedList::searchPrint(long init, long fin){
  Node *curr = head;
  while(curr->getData().key < init){
    curr = curr->getNext();
  }
  while(curr->getData().key <= fin && curr->getNext() != nullptr){
    cout << curr->getData().registry << endl;
    curr = curr->getNext();
  }
  if (curr->getData().key <= fin && curr->getNext() == nullptr){
    cout << curr->getData().registry << endl;
  }
}

/*
  Descripcion: Revisa si una estructura doblemente encadenada esta vacia o no y regresa true o false respectivamente.
  Entrada: Ninguna.
  Salida: Booleano, true si la estructura se encuentra vacia, false si tiene nodos.
  Complejidad: O(1), constante.
*/
bool DoubleLinkedList::isEmpty(){
  return head == nullptr;
}

/*
  Descripcion: Ordena la estructura doblemente encadenada en forma ascendente por ip.
  Entrada: Ninguna.
  Salida: Ninguna.
  Complejidad: O(n^2), cuadratica.
*/
void DoubleLinkedList::bubbleSort(){
  Node *curr;
  bool interruptor = true;
  for(int pas = 0; pas<size-1 && interruptor; ++pas){
    interruptor = false;
    curr = head;
    // double perc = perc + ((double)(pas+(size-pas))/((pas+(size-pas))*size) * 100);
    // cout << perc << "%" << endl;
    for(int j=0; j<size-1-pas; ++j){
      if (curr->getNext()->getData().key < curr->getData().key){
        // X = curr
        // Y = curr->getNext()
        if (curr->getPrevious() == nullptr){
          // 1:
          // X -> N:
          curr->setNext(curr->getNext()->getNext());

          // 2:
          // Y -> X:
          curr->getNext()->getPrevious()->setNext(curr);
          
          // 3:
          // Y <- X:
          curr->setPrevious(curr->getNext()->getPrevious());

          // 4:
          // X <- N:
          curr->getNext()->setPrevious(curr);

          // 5:
          // nullptr <- Y:
          curr->getPrevious()->setPrevious(nullptr);
      
          head = curr->getPrevious();
        }
        else if (curr->getNext()->getNext() == nullptr){
          // 1:
          // P <- Y:
          curr->getNext()->setPrevious(curr->getPrevious());
          
          // 2:
          // Y <- X:
          curr->setPrevious(curr->getNext());

          // 3:
          // Y -> X:
          curr->getNext()->setNext(curr);

          // 4:
          // P -> Y:
          curr->getNext()->getPrevious()->setNext(curr->getNext());

          // 5:
          // X -> nullptr:
          curr -> setNext(nullptr);

          tail = curr;
        }
        else{
          // 1:
          // P -> Y:
          curr->getPrevious()->setNext(curr->getNext());

          // 2:
          // X <- N:
          curr->getNext()->getNext()->setPrevious(curr);

          // 3:
          // P <- Y: 
          curr->getNext()->setPrevious(curr->getPrevious());

          // 4:
          // X -> N: 
          curr->setNext(curr->getNext()->getNext());

          // 5:
          // Y -> X: 
          curr->getPrevious()->getNext()->setNext(curr);

          // 6:
          // Y <- X: 
          curr->setPrevious(curr->getPrevious()->getNext());
        }
        interruptor = true;
      }
      else{
        curr = curr->getNext();
      }
    }
  }
}

/*
  Descripcion: Guarda la informacion (registros) de la estructura doblemente encadenada en un archivo txt, cuyo
  nombre es dado por el usuario.
  Entrada: Ninguna.
  Salida: Ninguna.
  Complejidad: O(n), lineal.
*/
void DoubleLinkedList::saveData(){
  fstream salida;
  string nomSalida;
  Node *curr = head;

  cout << "Ingresa el nombre de salida del archivo con los registros ordenados: ";
  cin >> nomSalida;
  salida.open(nomSalida + ".txt", ios::out);

  for (int i=1; i<=size; i++){ // O(n)
    salida << curr->getData().registry << endl;
    curr = curr->getNext();
  }

  salida.close();
}

/*
  Descripcion: Método que elimina secuencialmente los nodos de la lista.
  Entrada: Ninguna.
  Salida: Ninguna.
  Complejidad: O(n), lineal.
*/
void DoubleLinkedList::deleteAll(){
  Node *curr = head;
  while(head != nullptr){
      head = head->getNext(); // avanza 1 a head
      delete curr; // elimina curr
      curr = head; // se alinea curr con head
  }
  size = 0;
}