/*
Instituto Tecnologico de Estudios Superiores de Monterrey 
Equipo 4: 
Elmer Osiel Avila Vargas - A00826359
Carlos Enrique Lucio Dominguez - A00828524
Descripcion: Permite la creacion y modificacion de la estructura BST.
Fecha de modificacion:  25/10/2020
*/

#include "Node.h"

class BST{
  public:
    BST();
    ~BST();
    void add(Info data);
    void inOrderCPrint(queue<Info> &q, int n);

  private:
    Node *root;
    void inOrderC(Node *r, queue<Info> &q);
    void destroy(Node *root);
};

/*  Metodo constructor.
    Complejidad: O(1), constante.
  */
BST::BST(){
    root = nullptr;
}

/*  Metodo destructor.
    Complejidad: O(1), constante.
  */
BST::~BST(){
   destroy(root);
}

/*  Descripcion: Metodo que permite añadir un nuevo nodo a la estructura BST.
    Entrada: Una instancia del struct Info con la información del nodo.
    Salida: Ninguna
    Complejidad: O(n), lineal.
  */
void BST::add(Info data){
  Node *curr = root;
  Node *father = nullptr;
  while(curr != nullptr){
    father = curr;
    if(curr->getData().access == data.access){
      curr = (curr->getData().ipNum < data.ipNum) ? curr->getLeft() : curr->getRight(); 
    }
    else{
      curr = (curr->getData().access > data.access) ? curr->getLeft() : curr->getRight();
    }
  }

  if(father == nullptr){
    root = new Node(data);
  }
  else{
    if(father->getData().access == data.access){
      (father->getData().ipNum < data.ipNum) ? father->setLeft(new Node(data)) : father->setRight(new Node(data)); 
    }
    else{
      (father->getData().access > data.access) ? father->setLeft(new Node(data)) : father->setRight(new Node(data));
    }
  }
}

/*  Descripcion: Metodo recursivo que destruye la estructura a partir del recorrido postorden
    Entrada: Un apuntador de tipo nodo (la raiz).
    Salida: Ninguna
    Complejidad: O(n), lineal.
*/
void BST::destroy(Node *r){
  if(r != nullptr){
    destroy(r->getLeft());
    destroy(r->getRight());
    delete r;
  }
}

/*  Descripcion: Recorre el arbol en inorden converso y almacena la informacion del nodo en una fila.
    Entrada: Apuntador al nodo desde donde comenzara a recorrerse, y una fila.
    Salida: Ninguna.
    Complejidad: O(n), lineal.
*/
void BST::inOrderC(Node *r, queue<Info> &q){
  if(r != nullptr){
    inOrderC(r->getRight(), q);
    q.push(r->getData());
    inOrderC(r->getLeft(), q);
  }
}

/*  Descripcion: Imprime la estructura tipo arbol en inorden converso.
    Entrada: Una fila (queue) y el número de datos a imprimir en inorden converso.
    Salida: Ninguna.
    Complejidad: O(n), lineal.
*/
void BST::inOrderCPrint(queue<Info> &q, int n){
  inOrderC(root, q);
  for (int i=1; i<=n; i++){
    cout << i << ".- " <<q.front().ip << " " << q.front().access << " accesos" << endl;
    q.pop();
  }
}