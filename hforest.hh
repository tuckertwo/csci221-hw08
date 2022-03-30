#pragma once
#include "htree.hh"
#include <vector>

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
  std::vector<HTree::tree_ptr_t> forest_;
};
