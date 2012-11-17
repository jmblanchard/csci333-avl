#include "AVL.h"
#include <queue>
#include <vector>
#include <iostream>
#include <assert.h>

template <typename T>
AVL<T>::AVL() {
  root = 0;
  depth = 0;
}

template <typename T>
AVL<T>::~AVL() {
  
}


template <typename T>
bool AVL<T>::find(T v) {
    Node<T> *curr = root;

    while (curr != 0 && curr->getValue() != v) {
        if (curr->getValue() > v) {
            curr = curr->getLeftChild();
        } else if (curr->getValue() < v) {
            curr = curr->getRightChild();
        }
    }

    if (curr == 0)
        return false;

    return true;
}

template <typename T>
void AVL<T>::insert(T v) {
    // node exists, exit
    if (find(v))
        return;

    Node<T> *temp = new Node<T>(v);
    Node<T> *curr = root;
    Node<T> *curr_parent = 0;
    Node<T> *critical_parent = 0;
    Node<T> *critical = 0;

    if (curr == 0) {
        root = temp;
    } else {
        // while we haven't found where to place it yet
        while (true) {
            // if we need to go left, else we go right
            if (curr->getValue() > v) {
                // if our current is 1, this becomes our critical point
                if (curr->getBalance() == 1) {
                    critical_parent = curr_parent;
                    critical = curr;
                }
                
                curr_parent = curr;
                curr = curr->getLeftChild();
                
                // we have found where we need to insert!
                if (curr == 0) {
                    curr_parent->setLeftChild(*temp);
                    break;
                }
            } else if (curr->getValue() < v) {
                // if our current is -1, this becomes our critical point
                if (curr->getBalance() == -1) {
                    critical_parent = curr_parent;
                    critical = curr;
                }

                curr_parent = curr;
                curr = curr->getRightChild();

                // we have found where we need to insert!
                if (curr == 0) {
                    curr_parent->setRightChild(*temp);
                    break;
                }
            }
        }

        // if we have a critical point we need to do rotations
        if (critical != 0) {
            reCalcBalance(critical);

            if (critical->getBalance() == 2) {
                if (critical->getLeftChild()->getBalance() == -1)
                    rotateLeft(critical->getLeftChild(), critical);

                rotateRight(critical, critical_parent);
            } else if (critical->getBalance() == -2) {
                if (critical->getRightChild()->getBalance() == 1)
                    rotateRight(critical->getRightChild(), critical);

                rotateLeft(critical, critical_parent);
            }
        }
    }

    reCalcBalance(root);
}

template <typename T>
void AVL<T>::remove(T v) {
    assert(root != 0);
    Node<T> *toDelete = root;
    Node<T> *prev = 0;
    bool left = false;

    // NEW
    std::vector<Node<T> *> nodes_to_balance;

    // find node
    while (toDelete != 0 && toDelete->getValue() != v) {
        // NEW: trace back to root for balancing
        nodes_to_balance.push_back(toDelete);

        prev = toDelete;
        if (toDelete->getValue() < v) {
            toDelete = toDelete->getRightChild();
            left = false;
        }
        else {
            toDelete = toDelete->getLeftChild();
            left = true;
        }
    }

    if (toDelete == 0) // return if not found
        return;

    if (toDelete->getLeftChild() == 0
            && toDelete->getRightChild() == 0) { // no children? 
        if (prev == 0) {
            root = 0;
        } else {
            if (left) {
                prev->setLeftChild(*(toDelete->getRightChild()));
            } else {
                prev->setRightChild(*(toDelete->getRightChild()));
            }
        }

        delete toDelete;
    } else if ((toDelete->getLeftChild() != 0) 
            != (toDelete->getRightChild() != 0)) { // one child?

        if (toDelete->getLeftChild() != 0) { // left child exists
            if (prev == 0) { // toDelete is root
                root = toDelete->getLeftChild();
            } else { // toDelete is not root
                if (left) {
                    prev->setLeftChild(*(toDelete->getLeftChild()));
                } else {
                    prev->setRightChild(*(toDelete->getLeftChild()));
                }
            }
        } else { // right child exists
            if (prev == 0) {
                root = toDelete->getRightChild();
            } else {
                if (left) {
                    prev->setLeftChild(*(toDelete->getRightChild()));
                } else {
                    prev->setRightChild(*(toDelete->getRightChild()));
                }
            }
        }

        delete toDelete;
    } else { // find inorder predecessor (left then right all the way down)
        Node<T> *parent_iop = toDelete;
        Node<T> *iop = toDelete->getLeftChild();
        nodes_to_balance.push_back(toDelete);

        // NEW: we need this to replace toDelete with iop when we find it
        int position_of_delete = nodes_to_balance.size() - 1;

        while (iop->getRightChild() != 0) {
            parent_iop = iop;
            iop = iop->getRightChild();

            // NEW: we add the all the way to the parent iop for rebalancing
            nodes_to_balance.push_back(parent_iop);
        }

        // NEW: we've found iop, we replace toDelete in nodes_to_balance
        // with it so we don't have a null pointer
        nodes_to_balance[position_of_delete] = iop;

        iop->setRightChild(*(toDelete->getRightChild()));

        if (parent_iop == toDelete) {
        } else {
            parent_iop->setRightChild(*(iop->getLeftChild()));
        }
        
        if (iop != toDelete->getLeftChild()) {
            iop->setLeftChild(*(toDelete->getLeftChild()));
        }

        if (prev == 0) {
            root = iop;
        } else {
            if (left) {
                prev->setLeftChild(*iop);
            } else {
                prev->setRightChild(*iop);
            }
        }

        delete toDelete;
    }

    // NEW: now we run through nodes_to_balance, balancing along the way
    while (!nodes_to_balance.empty()) {
        reCalcBalance(nodes_to_balance.back());

        if (nodes_to_balance.back()->getBalance() == 2) {
            if (nodes_to_balance.back()->getLeftChild()->getBalance() == -1)
                rotateLeft(nodes_to_balance.back()->getLeftChild(),
                        nodes_to_balance.back());

            if (nodes_to_balance.back() == root) {
                rotateRight(nodes_to_balance.back(), (Node<T> *)0);
            } else {
                rotateRight(nodes_to_balance.back(),
                        nodes_to_balance[nodes_to_balance.size()-2]);
            }
        } else if (nodes_to_balance.back()->getBalance() == -2) {
            if (nodes_to_balance.back()->getRightChild()->getBalance() == 1)
                rotateRight(nodes_to_balance.back()->getRightChild(),
                        nodes_to_balance.back());

            if (nodes_to_balance.back() == root) {
                rotateLeft(nodes_to_balance.back(), (Node<T> *)0);
            } else {
                rotateLeft(nodes_to_balance.back(), 
                        nodes_to_balance[nodes_to_balance.size()-2]);
            }
        }

        nodes_to_balance.pop_back();
    }
}

template <typename T>
void AVL<T>::print() {
  //traversalPrint(root);
  bfsPrint(root);
}

template <typename T>
void AVL<T>::bfsPrint(Node<T> *n) {
    int items_on_curr_level = 1;
    int items_on_next_level = 0;
    std::queue<Node<T> *> q;
    q.push(n);

    while (!q.empty()) {
        if (items_on_curr_level == 0) {
            std::cout << "\n";
            items_on_curr_level = items_on_next_level;
            items_on_next_level = 0;
        }
        
        if (q.front()->getLeftChild() != 0) {
            q.push(q.front()->getLeftChild());
            items_on_next_level++;
        }
        if (q.front()->getRightChild() != 0) {
            q.push(q.front()->getRightChild());
            items_on_next_level++;
        }

        std::cout << " " << q.front()->getValue();
        q.pop();
        items_on_curr_level--;
    }

    std::cout << std::endl;
}

template <typename T>
void AVL<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void AVL<T>::rotateLeft(Node<T> *n, Node<T> *n_parent) {
    // do our swap here
    Node<T> *temp = n->getRightChild();
    n->setRightChild(*(temp->getLeftChild()));
    temp->setLeftChild(*n);

    // if we have a parent, we need to set its new child
    // else, we are at the root, set new root
    if (n_parent != 0) {
        if (n_parent->getLeftChild() == n) {
            n_parent->setLeftChild(*temp);
        } else {
            n_parent->setRightChild(*temp);
        }
    } else {
        root = temp;
    }
}

template <typename T>
void AVL<T>::rotateRight(Node<T> *n, Node<T> *n_parent) {
    // do our swap here
    Node<T> *temp = n->getLeftChild();
    n->setLeftChild(*(temp->getRightChild()));
    temp->setRightChild(*n);

    // if we have a parent, we need to set its new child
    // else, we are at the root, set new root
    if (n_parent != 0) {
        if (n_parent->getLeftChild() == n) {
            n_parent->setLeftChild(*temp);
        } else {
            n_parent->setRightChild(*temp);
        }
    } else {
        root = temp;
    }
}

template <typename T>
void AVL<T>::reCalcBalance(Node<T> *n) {
    if (n->getLeftChild() != 0)
        reCalcBalance(n->getLeftChild());
    if (n->getRightChild() != 0)
        reCalcBalance(n->getRightChild());
    n->updateHeightAndBalance();
}

template class AVL<int>;
template class AVL<double>;
template class AVL<std::string>;
