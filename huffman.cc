#include <vector>
#include "huffman.hh"
#include <cassert>

using namespace std;

Huffman::Huffman() : freqtab_(Huffman::ALPHABET_SIZE, 0)
{
  tree_ = make_shared<HTree>(-1, -1);

  // This gives EOF a frequency of 1 and then builds our initial tree.
  update_freq(Huffman::HEOF);
}

Huffman::~Huffman() {}

void Huffman::update_freq(int symbol)
{
  // Make sure nothing's gone very wrong.
  assert(symbol < Huffman::ALPHABET_SIZE);

  // Update frequency table
  freqtab_.at(symbol) += 1;

  // Build a new Huffman tree.
  HForest forest = HForest();
  // I'd've used range-based for here if I didn't need the indices of the array.
  for(unsigned int i=0; i<freqtab_.size(); i++)
  {
    forest.add_tree(make_shared<HTree>(i, freqtab_.at(i)));
  }
  // Make sure all symbols are accounted for.
  assert(forest.size() == Huffman::ALPHABET_SIZE);

  int infinite_loop_preventor = 0;
  while(forest.size() > 1)
  {
    int init_size = forest.size();

    HTree::tree_ptr_t tree0 = forest.pop_tree(); // Lowest
    assert(tree0);
    HTree::tree_ptr_t tree1 = forest.pop_tree(); // Second-lowest
    assert(tree1);
    HTree::tree_ptr_t newtree = make_shared<HTree>(-1,
          tree0->get_value()+tree1->get_value(), tree0, tree1);
    forest.add_tree(newtree);

    assert(init_size-forest.size() == 1);

    // Make sure nothing's gone south; this should run in or around
    // O(n log n) time.
    assert(infinite_loop_preventor++ <= (Huffman::ALPHABET_SIZE^2));
  }
  assert(forest.size() == 1);
  tree_ = forest.pop_tree();
}

Huffman::bits_t Huffman::encode(int symbol)
{
  // Note: do not use update_freq on HEOF.
  bits_t bits = {};
  HTree::possible_path_t path = tree_->path_to(symbol);
  assert(path);
  for(HTree::Direction dir : *path)
  {
    if(dir == HTree::Direction::LEFT)
    {
      bits.push_back(0);
    }
    else
    {
      bits.push_back(1);
    }
  }

  if(symbol != Huffman::HEOF)
  {
    update_freq(symbol);
  }

  return bits;
}

int Huffman::decode(bool bit)
{
  HTree::tree_ptr_t child;
  if(bit)
  {
    child = tree_->get_child(HTree::Direction::RIGHT);
  }
  else
  {
    child = tree_->get_child(HTree::Direction::LEFT);
  }
  assert(child);
  tree_ = child;
  int key = tree_->get_key();
  if(key != -1)
  {
    update_freq(key); // This will clobber tree_
  }
  return key;
}
