/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"
#include <cassert>
using namespace std;


// Accessor functions
HTree::key_t   HTree::get_key()   const {return key_;}
HTree::value_t HTree::get_value() const {return value_;}
HTree::tree_ptr_t HTree::get_child(Direction dir) const
{
  switch(dir)
  {
    case Direction::LEFT:  return left_;
    case Direction::RIGHT: return right_;
  }
  // This code shouldn't be reachable, but is required to satisfy -Werror
  assert(1!=1);
  return left_;
}

// Constructor
HTree::HTree(key_t key,
      value_t value,
      tree_ptr_t left,
      tree_ptr_t right)
  : key_(key), value_(value), left_(left), right_(right) {}

// Destructor
HTree::~HTree() {}

//////////////////////////////////////////////////////////////////////////////
HTree::possible_path_t HTree::path_to(key_t key) const
{
  HTree::possible_path_t subpath;
  if(key==key_)
  {
    return HTree::possible_path_t(new path_t());
  }
  else if(left_ && (subpath = left_->path_to(key)))
  {
    subpath->push_front(Direction::LEFT);
    return subpath;
  }
  else if(right_ && (subpath = right_->path_to(key)))
  {
    subpath->push_front(Direction::RIGHT);
    return subpath;
  }
  else
  {
    return nullptr;
  }
}

HTree::tree_ptr_t HTree::node_at(HTree::path_t path) const
{
  HTree::tree_ptr_t nextel = nullptr;
  if(path.empty())
  {
    nextel = HTree::tree_ptr_t(this);
  }
  else
  {
    // Yoink the first character off of the string ...
    nextel = this->get_child(path.front());
  }

  if(nextel && path.size()>1)
  {
    // ... and keep traversing.
    path.pop_front();
    return nextel->node_at(path);
  }
  else
  {
    return nextel;
  }
}
