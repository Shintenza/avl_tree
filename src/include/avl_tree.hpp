#pragma once
#include "avl_node.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>

template <typename T> class AVLTree {
public:
  AVLTree() : root(nullptr) {}
  ~AVLTree() { clear(); }
  void insert(const T &item) { root = insert(root, item); }
  void remove(const T &item) { root = remove(root, item); }

  void clear() {
    clear(root);
    root = nullptr;
  };

  T &max() const { return max(root); }
  T &min() const { return min(root); }

  void display() const { display(root, 0); }

  bool empty() const { return root == nullptr; }
  bool contains(const T &item) const {
    return search(root, item) ? true : false;
  };

  bool test_order();
  bool test_isBalanced() { return isBalanced(root); }

private:
  AVLNode<T> *root;

  AVLNode<T> *insert(AVLNode<T> *node, const T &item);
  AVLNode<T> *search(AVLNode<T> *node, const T &item) const;
  AVLNode<T> *remove(AVLNode<T> *node, const T &item);

  AVLNode<T> *balanceTree(AVLNode<T> *node);
  AVLNode<T> *rotateLeft(AVLNode<T> *node);
  AVLNode<T> *rotateRight(AVLNode<T> *node);
  AVLNode<T> *rotateLeftThenRight(AVLNode<T> *node);
  AVLNode<T> *rotateRightThenLeft(AVLNode<T> *node);

  T &max(AVLNode<T> *node) const;
  T &min(AVLNode<T> *node) const;

  void clear(AVLNode<T> *node);
  void setBalance(AVLNode<T> *node);
  void display(AVLNode<T> *node, int level) const;

  int height(AVLNode<T> *node);

  bool isBalanced(AVLNode<T> *node);
};

template <typename T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *node, const T &item) {
  if (node == nullptr) {
    return new AVLNode<T>(item);
  }

  if (node->value > item) {
    node->left = insert(node->left, item);
    node->left->parent = node;
  }

  if (node->value < item) {
    node->right = insert(node->right, item);
    node->right->parent = node;
  }
  return balanceTree(node);
}

template <typename T>
AVLNode<T> *AVLTree<T>::remove(AVLNode<T> *node, const T &item) {
  if (!node)
    return node;
  if (item < node->value) {
    node->left = remove(node->left, item);
  } else if (item > node->value) {
    node->right = remove(node->right, item);
  } else {
    if (!node->left || !node->right) {
      AVLNode<T> *tmp = node->left ? node->left : node->right;
      if (!tmp) {
        tmp = node;
        node = nullptr;
      } else {
        tmp->parent = node->parent;
        *node = *tmp;
      }
      delete tmp;
    } else {
      AVLNode<T> *inorderSucc = node->right;
      while (inorderSucc->left) {
        inorderSucc = inorderSucc->left;
      }

      node->value = inorderSucc->value;
      node->right = remove(node->right, inorderSucc->value);
    }
  }
  if (!node)
    return node;
  return balanceTree(node);
}

template <typename T>
AVLNode<T> *AVLTree<T>::search(AVLNode<T> *node, const T &item) const {
  if (!node || node->value == item)
    return node;
  if (item < node->value)
    return search(node->left, item);
  return search(node->right, item);
}

template <typename T> AVLNode<T> *AVLTree<T>::rotateLeft(AVLNode<T> *node) {
  AVLNode<T> *newSubtreeRoot = node->right;
  newSubtreeRoot->parent = node->parent;
  node->right = newSubtreeRoot->left;

  if (node->right) {
    node->right->parent = node;
  }

  node->parent = newSubtreeRoot;
  newSubtreeRoot->left = node;

  if (newSubtreeRoot->parent) {
    if (newSubtreeRoot->parent->left == node) {
      newSubtreeRoot->parent->left = newSubtreeRoot;
    } else {
      newSubtreeRoot->parent->right = newSubtreeRoot;
    }
  }

  setBalance(node);
  setBalance(newSubtreeRoot);
  return newSubtreeRoot;
}

template <typename T> AVLNode<T> *AVLTree<T>::rotateRight(AVLNode<T> *node) {
  AVLNode<T> *newSubtreeRoot = node->left;
  newSubtreeRoot->parent = node->parent;
  node->left = newSubtreeRoot->right;

  if (node->left) {
    node->left->parent = node;
  }

  newSubtreeRoot->right = node;
  node->parent = newSubtreeRoot;

  if (newSubtreeRoot->parent) {
    if (newSubtreeRoot->parent->right == node) {
      newSubtreeRoot->parent->right = newSubtreeRoot;
    } else {
      newSubtreeRoot->parent->left = newSubtreeRoot;
    }
  }
  setBalance(node);
  setBalance(newSubtreeRoot);
  return newSubtreeRoot;
}

template <typename T>
AVLNode<T> *AVLTree<T>::rotateLeftThenRight(AVLNode<T> *node) {
  node->left = rotateLeft(node->left);
  return rotateRight(node);
}

template <typename T>
AVLNode<T> *AVLTree<T>::rotateRightThenLeft(AVLNode<T> *node) {
  node->right = rotateRight(node->right);
  return rotateLeft(node);
}

template <typename T> int AVLTree<T>::height(AVLNode<T> *node) {
  if (node == nullptr)
    return -1;
  return 1 + std::max(height(node->left), height(node->right));
}

template <typename T> void AVLTree<T>::setBalance(AVLNode<T> *node) {
  node->balance = height(node->right) - height(node->left);
}

template <typename T> AVLNode<T> *AVLTree<T>::balanceTree(AVLNode<T> *node) {
  setBalance(node);

  if (node->balance == 2) {
    if (height(node->right->right) >= height(node->right->left)) {
      return rotateLeft(node);
    } else {
      return rotateRightThenLeft(node);
    }
  }
  if (node->balance == -2) {
    if (height(node->left->left) >= height(node->left->right)) {
      return rotateRight(node);
    } else {
      return rotateLeftThenRight(node);
    }
  }
  return node;
}

template <typename T>
void AVLTree<T>::display(AVLNode<T> *node, int level) const {
  if (node == nullptr)
    return;
  display(node->right, level + 1);
  std::cout << std::string(3 * level, ' ') << node->value << "("
            << node->balance << ")" << std::endl;
  display(node->left, level + 1);
}

template <typename T> bool AVLTree<T>::test_order() {
  std::vector<T> results;
  std::stack<AVLNode<T> *> nodeStack;

  AVLNode<T> *current = root;

  while (current || !nodeStack.empty()) {
    while (current) {
      nodeStack.push(current);
      current = current->left;
    }

    current = nodeStack.top();
    nodeStack.pop();
    results.push_back(current->value);
    current = current->right;
  }
  return std::is_sorted(results.begin(), results.end());
}

template <typename T> bool AVLTree<T>::isBalanced(AVLNode<T> *node) {
  if (!node)
    return true;

  if (std::abs(height(node->left) - height(node->right)) <= 1 &&
      isBalanced(node->left) && isBalanced(node->right)) {
    return true;
  }

  return false;
}

template <typename T> void AVLTree<T>::clear(AVLNode<T> *node) {
  if (!node)
    return;

  clear(node->left);
  clear(node->right);
  delete node;
}

template <typename T> T &AVLTree<T>::max(AVLNode<T> *node) const {
  AVLNode<T> *current = node;
  while (current->right) {
    current = current->right;
  }
  return current->value;
}

template <typename T> T &AVLTree<T>::min(AVLNode<T> *node) const {
  AVLNode<T> *current = node;
  while (current->left) {
    current = current->left;
  }
  return current->value;
}
