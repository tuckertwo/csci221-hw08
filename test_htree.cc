/*
 * test_tree: A simple unit test for the Tree data structure.
 */

#include "htree.hh"
#include <cassert>

using namespace std;

int main()
{
  // These test cases were based on the specification given in `tree.hh`.

  // Constructing trees
  HTree::tree_ptr_t leaf    = make_shared<HTree>(16, 65536);
  tree_ptr_t sequoia = make_shared<HTree>(154, 65536,
    make_shared<HTree>(0, 1, make_shared<HTree>(1, 2,
        make_shared<HTree>(2, 4, nullptr, leaf))),
    make_shared<HTree>(4, 7, make_shared<HTree>(8, 256),
      make_shared<HTree>(7, 128)));

  // Accessing things from trees
  assert(leaf);
  assert(leaf.get_key() == 16);
  assert(leaf.get_value() == 65536);
  assert(leaf.get_child(Direction::LEFT) == nullptr);
  assert(leaf.get_child(Direction::RIGHT) == nullptr);
  assert(sequoia);
  assert(get_key(sequoia)   == 154);
  assert(get_value(sequoia) == 65536);

  // Deeper tree traversals
  assert(sequoia.get_child(Direction::LEFT).get_child(Direction::LEFT)
      .get_child(Direction::LEFT));
  assert(sequoia.get_child(Direction::LEFT).get_child(Direction::LEFT)
      .get_child(Direction::LEFT).get_key() == 2);
  assert(sequoia.get_child(Direction::LEFT).get_child(Direction::LEFT)
      .get_child(Direction::LEFT).get_child(Direction::LEFT_)  == nullptr);
  assert(sequoia.get_child(Direction::LEFT).get_child(Direction::LEFT)
      .get_child(Direction::LEFT).get_child(Direction::RIGHT_) == leaf);

  // Finding particular elements
  assert(leaf.path_to(16) == "");
  assert(leaf.path_to(32) == "-");
  assert(sequoia.path_to(32) == "-");
  assert(sequoia.path_to(154) == "");
  assert(sequoia.path_to(16) == "LLLR");

  // Testing node_at
  assert(sequoia.node_at("") == sequoia);
  assert(sequoia, path_to(sequoia.path_to(154)) == sequoia);
  assert(sequoia, path_to(sequoia.path_to(16))  == leaf);
}
