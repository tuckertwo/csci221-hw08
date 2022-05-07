#include "htree.hh"
#include "hforest.hh"
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
  // Constructing trees
  HTree::tree_ptr_t leaf    = make_shared<HTree>(16, 65536);
  HTree::tree_ptr_t sequoia = make_shared<HTree>(154, 32768,
    make_shared<HTree>(0, 1, make_shared<HTree>(1, 2,
        make_shared<HTree>(2, 4, nullptr, nullptr))),
    make_shared<HTree>(4, 7, make_shared<HTree>(8, 256),
      make_shared<HTree>(7, 128)));

  // Constructing a forest
  HForest forest0 = HForest();
  assert(forest0.size() == 0);
  forest0.add_tree(leaf);
  forest0.add_tree(sequoia);
  assert(forest0.size() == 2);

  // Since HForest uses a heap internally, insertion order shouldn't
  // matter.
  HForest forest1 = HForest();
  forest1.add_tree(sequoia);
  forest1.add_tree(leaf);
  assert(forest1         == forest0);

  // Testing deletion
  HForest forest2 = HForest();
  forest2.add_tree(leaf);
  assert(forest0.pop_tree()->get_value() == sequoia->get_value());
  assert(forest0.size() == 1);
  assert(forest0         == forest2);
  assert(forest0.pop_tree()->get_value() == leaf->get_value());
  assert(forest0.size() == 0);
  assert(forest0.pop_tree() == nullptr);

  // Test inline forest creation
  HForest forest3 = HForest({leaf, sequoia});
  HForest forest4 = HForest({sequoia, leaf});
  assert(forest1         == forest3);
  assert(forest3         == forest4);
}
