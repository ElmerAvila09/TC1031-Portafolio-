/*
Instituto Tecnologico de Estudios Superiores de Monterrey 
Equipo 4: 
Elmer Osiel Avila Vargas - A00826359
Carlos Enrique Lucio Dominguez - A00828524
Descripcion: Clase Nodo que permite tener una lista doblemente encadenada
de nodos ya que es la responsable de realizar la creacion de los mismos, asi
como modificar sus conexiones e informacion.
*/

// Estructura que contiene la llave y el registro.
// Ambos constructores tienen complejidad O(1), constante.
struct Info{
  long key;
  string registry;

  Info(){
    registry = "";
    key = 0;
  }

  Info(string str, long key){
    registry = str;
    this->key = key;
  }
};

class Node{
  public:
    Node(Info data);
    Node(Info data, Node *previous, Node *next);
    Info getData();
    Node* getNext();
    Node* getPrevious();
    void setData(Info data);
    void setNext(Node *next);
    void setPrevious(Node *previous);
  
  private:
    Node *previous;
    Node *next;

    // Instancia de la estrctura Info, que actúa como atributo de Node.
    Info data;
    int size;
};

// Método constructor que recibe una instancia de la estructura Info.
// Complejidad: O(1), constante.
Node::Node(Info data){
  this -> data = data;
  previous = nullptr;
  next = nullptr;
}

// Método constructor que recibe una instancia de la estructura Info y dos apuntadores de la clase Nodo.
// Complejidad: O(1), constante.
Node::Node(Info data, Node* previous, Node* next){
  this -> data = data;
  this -> previous = previous;
  this -> next = next;
}

/*
  Descripcion: Método que obtiene la estructura Info de un Nodo.
  Entrada: Ninguna.
  Salida: La instancia de la estructura Info.
  Complejidad: O(1), constante.
*/
Info Node::getData(){
  return data;
}

/*
  Descripcion: Método que obtiene el siguiente Nodo de un Nodo.
  Entrada: Ninguna.
  Salida: El siguiente Nodo de un Nodo.
  Complejidad: O(1), constante.
*/
Node* Node::getNext(){
  return next;
}

/*
  Descripcion: Método que obtiene el Nodo previo a un Nodo.
  Entrada: Ninguna.
  Salida: El Nodo previo a un Nodo.
  Complejidad: O(1), constante.
*/
Node* Node::getPrevious(){
  return previous;
}

/*
  Descripcion: Método set de la estructura Info de un Nodo.
  Entrada: Una instancia de la clase Info.
  Salida: Ninguna.
  Complejidad: O(1), constante.
*/
void Node::setData(Info data){
  this -> data = data;
}

/*
  Descripcion: Método set del siguiente Nodo de un Nodo.
  Entrada: Una apuntador de la clase Nodo.
  Salida: Ninguna.
  Complejidad: O(1), constante.
*/
void Node::setNext(Node *next){
  this -> next = next;
}

/*
  Descripcion: Método set del Nodo previo a un Nodo.
  Entrada: Una apuntador de la clase Nodo.
  Salida: Ninguna.
  Complejidad: O(1), constante.
*/
void Node::setPrevious(Node *prev){
  this -> previous = prev;
}