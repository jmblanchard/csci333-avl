#include "AVL.h"
#include <iostream>

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(4);
  avl->insert(7);
  avl->insert(6);

  avl->print();

  return 0;

}
