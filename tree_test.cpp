#include "AVL.h"
#include <iostream>

int main() {
  AVL<int>* avl = new AVL<int>();

  avl->insert(4);   // 4

  avl->insert(7);   //     4
                    //        7
  
  avl->insert(6);   //     6
                    //   4   7

  avl->insert(10);  //     6
                    //   4   7
                    //         10

  avl->insert(12);  //     6
                    //   4      10
                    //        7     12

  avl->print();

  std::cout << "\n";
  avl->remove(6);

  avl->print();
  std::cout << "\n";
  avl->printInOrder();
  std::cout << "\n";
  avl->printPostOrder();

  return 0;

}
