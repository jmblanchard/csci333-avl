#ifndef __NODE_H__
#define __NODE_H__

template <typename T>
class Node {
 private:
  T value;
  int balance_;
  int height_, left_height_, right_height_;
  Node<T>* leftChild;
  Node<T>* rightChild;

  void updateBalance();

 public:
  Node<T>(T v);
  T getValue();

  Node<T>*& getLeftChild();
  void setLeftChild(Node<T>& n);

  Node<T>*& getRightChild();
  void setRightChild(Node<T>& n);

  void updateHeightAndBalance();
  int getHeight();

  int getBalance();
};
#endif
