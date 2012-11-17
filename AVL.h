#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>

template <typename T>
class AVL {
 private:
  Node<T>* root;
  int depth;

  void traversalPrint(Node<T>* root);
  void bfsPrint(Node<T> *n);

  void rotateLeft(Node<T> *n, Node<T> *n_parent);
  void rotateRight(Node<T> *n, Node<T> *n_parent);

  void reCalcBalance(Node<T> *n);

  void inOrderTraversal(Node<T> *n);
  void postOrderTraversal(Node<T> *n);

 public:
  AVL<T>();
  ~AVL<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
  void printInOrder();
  void printPostOrder();
};


#endif
