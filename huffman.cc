#include <vector>
#include "huffman.hh"
#include <cassert>

using namespace std;

Huffman()
{
  vector<int> freqtab_(Huffman::ALPHABET_SIZE, 0);

  // This gives EOF a frequency of 1 and then builds our initial tree.
  this->update_freq(Huffman::HEOF);
}

void Huffman::update_freq(int symbol)
bits_t Huffman::encode(int symbol)
int Huffman::decode(bool bit)
