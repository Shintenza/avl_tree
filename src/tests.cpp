#include "include/avl_tree.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("insertions", "[inserion]") {
  AVLTree<int> avl_tree;

  SECTION("test right rotation") {
    avl_tree.insert(10);
    avl_tree.insert(8);
    avl_tree.insert(7);
    avl_tree.insert(5);
    avl_tree.insert(4);

    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("test left rotation") {
    avl_tree.insert(1);
    avl_tree.insert(2);
    avl_tree.insert(3);
    avl_tree.insert(4);
    avl_tree.insert(5);

    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("test right then left rotation") {
    avl_tree.insert(3);
    avl_tree.insert(1);
    avl_tree.insert(6);
    avl_tree.insert(7);
    avl_tree.insert(4);
    avl_tree.insert(5);

    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("test left then right rotation") {
    avl_tree.insert(8);
    avl_tree.insert(9);
    avl_tree.insert(5);
    avl_tree.insert(2);
    avl_tree.insert(6);
    avl_tree.insert(7);

    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }
}

TEST_CASE("min/max", "[min_max]") {
  AVLTree<int> avl_tree;

  avl_tree.insert(8);
  avl_tree.insert(9);
  avl_tree.insert(5);
  avl_tree.insert(2);
  avl_tree.insert(6);
  avl_tree.insert(7);

  REQUIRE(avl_tree.max() == 9);
  REQUIRE(avl_tree.min() == 2);
}

TEST_CASE("includes", "include") {
  AVLTree<int> avl_tree;
  avl_tree.insert(2);
  avl_tree.insert(1);
  avl_tree.insert(4);
  avl_tree.insert(6);
  REQUIRE(avl_tree.contains(6));
}

TEST_CASE("empty", "[empty]") {
  AVLTree<int> avl_tree;

  REQUIRE(avl_tree.empty());

  avl_tree.insert(1);
  avl_tree.clear();

  REQUIRE(avl_tree.empty());

  avl_tree.insert(1);
  avl_tree.remove(1);

  REQUIRE(avl_tree.empty());
}

TEST_CASE("deletions", "[detetion]") {
  AVLTree<int> avl_tree;

  SECTION("remove a leaf node") {
    avl_tree.insert(2);
    avl_tree.insert(1);
    avl_tree.insert(3);

    avl_tree.remove(3);
    REQUIRE(!avl_tree.contains(3));
    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("remove a node with only one child") {
    avl_tree.insert(2);
    avl_tree.insert(1);
    avl_tree.insert(3);
    avl_tree.insert(4);

    avl_tree.remove(3);
    REQUIRE(!avl_tree.contains(3));
    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("remove a node with both children") {
    avl_tree.insert(1);
    avl_tree.insert(2);
    avl_tree.insert(3);

    avl_tree.remove(1);
    REQUIRE(!avl_tree.contains(1));
    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("with left rotation required") {
    avl_tree.insert(3);
    avl_tree.insert(1);
    avl_tree.insert(6);
    avl_tree.insert(7);
    avl_tree.insert(4);

    avl_tree.remove(1);

    REQUIRE(!avl_tree.contains(1));
    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("with right rotation required") {
    avl_tree.insert(5);
    avl_tree.insert(6);
    avl_tree.insert(3);
    avl_tree.insert(2);
    avl_tree.insert(4);
    avl_tree.remove(6);

    REQUIRE(!avl_tree.contains(6));
    REQUIRE(avl_tree.test_order());
    REQUIRE(avl_tree.test_isBalanced());
  }

  SECTION("delete root") {
    avl_tree.insert(2);
    avl_tree.remove(2);

    REQUIRE(!avl_tree.contains(2));
    REQUIRE(avl_tree.empty());

    avl_tree.insert(2);

    REQUIRE(avl_tree.contains(2));
  }
}
