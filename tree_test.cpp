#include "AVL.h"
#include <iostream>

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(10);
  avl->insert(6);
  avl->insert(3);
  avl->insert(2);
  avl->insert(7);
  avl->insert(12);
  avl->print();

  std::cout << "\n";
  avl->remove(6);
  avl->print();
  std::cout << "\n";
  avl->remove(3);
  avl->print();
  std::cout << "\n";
  avl->remove(10);

  avl->print();

  return 0;

}
