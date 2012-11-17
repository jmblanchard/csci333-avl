#include <string>
#include <algorithm>
#include "Node.h"

template <typename T>
Node<T>::Node(T v) {
  value = v;
  leftChild = 0;
  rightChild = 0;
  balance_ = 0;
  height_ = 0;
  left_height_ = 0;
  right_height_ = 0;
}

template <typename T>
T Node<T>::getValue() {
  return value;
}

template <typename T>
Node<T>*& Node<T>::getLeftChild() {
  return leftChild;
}

template <typename T>
void Node<T>::setLeftChild(Node<T>& lc) {
  leftChild = &lc;
}

template <typename T>
Node<T>*& Node<T>::getRightChild() {
  return rightChild;
}

template <typename T>
void Node<T>::setRightChild(Node<T>& rc) {
  rightChild = &rc;
}

template <typename T>
int Node<T>::getHeight() {
    return height_;
}

template <typename T>
void Node<T>::updateHeightAndBalance() {
    if (getLeftChild() == 0 && getRightChild() == 0) {
        height_ = 0;
        left_height_ = 0;
        right_height_ = 0;
    } else {
        if (getLeftChild() == 0)
            left_height_ = 0;
        else
            left_height_ = getLeftChild()->getHeight() + 1;
        if (getRightChild() == 0)
            right_height_ = 0;
        else
            right_height_ = getRightChild()->getHeight() + 1;

        height_ = std::max(left_height_, right_height_);
    }

    updateBalance();
}

template <typename T>
int Node<T>::getBalance() {
    return balance_;
}

template <typename T>
void Node<T>::updateBalance() {
    balance_ = left_height_ - right_height_;
}



template class Node<int>;
template class Node<double>;
template class Node<std::string>;

