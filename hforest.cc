#include "hforest.hh"
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

// Returns true if a>=b.
// Note: this function must be declared before the other forest functions.
bool compare_trees(const HTree::tree_ptr_t a,
    const HTree::tree_ptr_t b)
{
  if(!b) // No thing is greater than nothing.
  {
    return false;
  }
  else if(!a)
  {
    return true;
  }
  else
  {
    return a->get_value() >= b->get_value();
  }
}

// Constructor
// Warning: when exploring South American forests, beware of the
// Boa Constructor.
HForest::HForest(vector<HTree::tree_ptr_t> initial)
  : forest_(initial)
{
  make_heap(forest_.begin(), forest_.end(), compare_trees);
}

// Destructor (unremarkable)
HForest::~HForest() {}

bool HForest::operator==(HForest b)
{
  return forest_ == b.forest_;
}

int HForest::size() const
{
  return forest_.size();
}

void HForest::add_tree(HTree::tree_ptr_t tree)
{
  forest_.push_back(tree);
  push_heap(forest_.begin(), forest_.end(), compare_trees);
}

HTree::tree_ptr_t HForest::pop_tree()
{
  HTree::tree_ptr_t tree = nullptr;
  if(this->size() > 0)
  {
    pop_heap(forest_.begin(), forest_.end(), compare_trees);
    tree = forest_.back();
    forest_.pop_back();
  }
  return tree;
}
