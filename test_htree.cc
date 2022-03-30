/*
 * test_tree: A simple unit test for the Tree data structure.
 */

#include "htree.hh"
#include <cassert>

using namespace std;
using Direction = HTree::Direction;

int main()
{
  // These test cases were based on the specification given in `tree.hh`.

  // Constructing trees
  HTree::tree_ptr_t leaf    = make_shared<HTree>(16, 65536);
  HTree::tree_ptr_t sequoia = make_shared<HTree>(154, 65536,
    make_shared<HTree>(0, 1, make_shared<HTree>(1, 2,
        make_shared<HTree>(2, 4, nullptr, leaf))),
    make_shared<HTree>(4, 7, make_shared<HTree>(8, 256),
      make_shared<HTree>(7, 128)));

  // Accessing things from trees
  assert(leaf);
  assert(leaf->get_key() == 16);
  assert(leaf->get_value() == 65536);
  assert(leaf->get_child(Direction::LEFT) == nullptr);
  assert(leaf->get_child(Direction::RIGHT) == nullptr);
  assert(sequoia);
  assert(sequoia->get_key()   == 154);
  assert(sequoia->get_value() == 65536);

  // Deeper tree traversals
  assert(sequoia->get_child(Direction::LEFT)->get_child(Direction::LEFT)
      ->get_child(Direction::LEFT));
  assert(sequoia->get_child(Direction::LEFT)->get_child(Direction::LEFT)
      ->get_child(Direction::LEFT)->get_key() == 2);
  assert(sequoia->get_child(Direction::LEFT)->get_child(Direction::LEFT)
      ->get_child(Direction::LEFT)->get_child(Direction::LEFT)  == nullptr);
  assert(sequoia->get_child(Direction::LEFT)->get_child(Direction::LEFT)
      ->get_child(Direction::LEFT)->get_child(Direction::RIGHT) == leaf);

  // Finding particular elements
  assert(leaf->path_to(16)->size()==0);
  assert(leaf->path_to(32) == nullptr);
  assert(sequoia->path_to(32) == nullptr);
  assert(sequoia->path_to(154)->size()==0);
  HTree::path_t path = {Direction::LEFT, Direction::LEFT,
      Direction::LEFT, Direction::RIGHT};
  assert(*(sequoia->path_to(16)) == path);
}
