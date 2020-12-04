/*
Instituto Tecnologico de Estudios Superiores de Monterrey 
Equipo 4: 
Elmer Osiel Avila Vargas - A00826359
Carlos Enrique Lucio Dominguez - A00828524
Descripcion: Permite la creacion de cada uno de los nodos y las estructuras de datos de datos dentro de estos.
Fecha de modificacion:  25/10/2020
*/

// Estructura que contiene la informacion del nodo (ip, accesos).
// Ambos constructores tienen complejidad O(1), constante.
struct Info{
  long ipNum;
  string ip;
  int access;
  
  Info(){
    ip = "";
    ipNum = 0;
    access = 0;
  }

  Info(string str, long ipNum, int access){
    ip = str;
    this->ipNum = ipNum;
    this->access = access;
  }
};

class Node{
  public:
    Node(Info data);
    Node(Info data, Node *left, Node * right);
    Info getData();
    void setData(Info data);
    Node* getLeft();
    void setLeft(Node *left);
    Node* getRight();
    void setRight(Node *right);
  private:
    Info data;
    Node *left;
    Node *right;
};

/*  Metodo constructor.
    Complejidad: O(1), constante.
*/
Node::Node(Info data){
  this->data = data;
  this->left = nullptr;
  this->right = nullptr;
}

/*  Metodo constructor que permite ademas establecer los nodos apuntadores al siguiente nivel.
    Complejidad: O(1), constante.
*/
Node::Node(Info data, Node *left, Node * right){
  this->data = data;
  this->left = left;
  this->right = right;
}

/*  Descripcion: Obtiene el dato de un nodo.
    Entrada: Nada.
    Salidad: Dato en el nodo.
    Complejidad: O(1), constante.
*/
Info Node::getData(){
  return data;
}

/*  Descripcion: Establece el dato de un nodo.
    Entrada: Dato que se quiere establecer.
    Salidad: Nada.
    Complejidad: O(1), constante.
  */
void Node::setData(Info data){
  this->data = data;
}

/*  Descripcion: Obtener el apuntador al nodo hijo izquierdo.
    Entrada: Nada.
    Salidad: Nodo apuntador, hijo izquierdo.
    Complejidad: O(1), constante.
  */
Node* Node::getLeft(){
  return left;
}

/*  Descripcion: Establece el nodo al que se apuntara a la izquierda, es decir, el hijo izquierdo.
    Entrada: Nodo apuntador que se establecera como hijo izquierdo.
    Salidad: Nada.
    Complejidad: O(1), constante.
  */
void Node::setLeft(Node *left){
  this->left = left;
}

/*  Descripcion: Obtener el apuntador al nodo hijo derecho.
    Entrada: Nada.
    Salidad: Nodo apuntador, hijo derecho.
    Complejidad: O(1), constante.
  */
Node* Node::getRight(){
  return right;
}

/*  Descripcion: Establece el nodo al que se apuntara a la derecha, es decir, el hijo derecho.
    Entrada: Nodo apuntador que se establecera como hijo derecho.
    Salidad: Nada.
    Complejidad: O(1), constante.
  */
void Node::setRight(Node *right){
  this->right = right;
}