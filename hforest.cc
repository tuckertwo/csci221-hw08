#include "htree.hh"
#include "hforest.hh"
#include <vector>
#include <algorithm>

using namespace std;

// Constructor
// Warning: when exploring South American forests, beware of the
// Boa Constructor.
HForest::HForest()
{
  vector vector<HTree::tree_ptr_t> HForest::forest_ = {};
}

// Destructor (unremarkable)
HForest::~HForest() {}

int HForest::size() const
{
  return forest_.size();
}
