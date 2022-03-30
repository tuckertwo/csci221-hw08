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
  // The forester
  // To be perfectly frank, I'm not sure if this should be a method of
  // the HForest class or if it instead should be its own function.
  bool compare_trees(const HTree::tree_ptr_t a,
      const HTree::tree_ptr_t b) const;
};
