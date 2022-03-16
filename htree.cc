/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
tree_ptr_t create_tree(const key_type& key,
            const value_type& value,
            tree_ptr_t left,
            tree_ptr_t right)
{
  Tree* tree = new Tree({key, value, left, right});
  return tree;
}


//////////////////////////////////////////////////////////////////////////////
void destroy_tree(tree_ptr_t tree)
{
  // This for loop can be confusing; the tree traversal is done recursively.
  // (The for loop is just here to iterate over the left and right nodes to
  // eliminate some cut-and-pasting of code.)
  for(tree_ptr_t branch : {tree->left_, tree->right_})
  {
    if(branch)
    {
      destroy_tree(branch);
    }
  }

  delete tree;
}


//////////////////////////////////////////////////////////////////////////////
std::string path_to(tree_ptr_t tree, key_type key)
{
  string subpath;
  if(tree == nullptr)
  {
    return "-";
  }
  else if(key==tree->key_)
  {
      return "";
  }

  else if(tree->left_ &&(subpath = path_to(tree->left_, key))!="-"){
      return "L" + subpath;
  }

  else if(tree->right_ &&(subpath = path_to(tree->right_, key))!="-"){
      return "R" + subpath;
  }

  else{
      return "-";
  }
}


//////////////////////////////////////////////////////////////////////////////
tree_ptr_t node_at(tree_ptr_t tree, std::string path)
{
  if(tree == nullptr)
  {
    return nullptr;
  }
  else
  {
    tree_ptr_t nextel = nullptr;
    if(path == "")
    {
      nextel = tree;
    }
    else if(path[0] == 'L' && tree->left_)
    {
      nextel = tree->left_;
    }
    else if(path[0] == 'R' && tree->right_)
    {
      nextel = tree->right_;
    }

    if(nextel && path.length()>1)
    {
      // Yoink the first character off of the string and continue traversing.
      return node_at(nextel, path.substr(1));
    }
    else
    {
      return nextel;
    }
  }
}
