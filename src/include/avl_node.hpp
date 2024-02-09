#pragma once
template <typename T> class AVLNode {
public:
  T value;
  int balance;
  AVLNode<T> *left, *right, *parent;

  AVLNode() : value(T()), balance(0), left(nullptr), right(nullptr) {}
  AVLNode(const T &item, AVLNode *given_parent = nullptr)
      : value(item), parent(given_parent), left(nullptr), right(nullptr),
        balance(0) {}
};
