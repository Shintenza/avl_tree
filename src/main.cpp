#include "include/avl_tree.hpp"

int main() {
  AVLTree<double> avl_tree;
  avl_tree.insert(2);
  avl_tree.clear();

  avl_tree.test_order();


  return 0;
}
