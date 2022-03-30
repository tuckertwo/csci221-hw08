#pragma once
#include "htree.hh"
#include <list>

class HForest
{
 public:
   HForest();
   ~HForest();

   // Get the size of the forest
   // /i.e./ how many trees are in the heap.
   int size() const;

   // Add a tree to the forest/heap
   void add_tree(HTree::tree_ptr_t tree);

   // Remove a tree from the forest/heap
   HTree::tree_ptr_t pop_tree();

 private:
  std::vector forest_;
  // the forester
  bool compare_trees(HTree::tree_ptr_t a, HTree::tree_ptr_t b);
};
