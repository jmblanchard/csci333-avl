#ifndef __AVL_H__
#define __AVL_H__

#include "Node.h"
#include <string>

template <typename T>
class AVL {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  void bfsPrint(Node<T> *n);

 public:
  AVL<T>();
  ~AVL<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};


#endif
