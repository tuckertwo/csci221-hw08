#include <iostream>
#include "huffman.hh"
#include "bitio.hh"

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "Incorrect number of arguments" << std::endl;
    return 1;
  }


  std::istream* in;
  std::ostream* out;
  if(*argv[1] == '-')
  {
    in  = &std::cin;
    out = &std::cout;
  }
  else
  {
    return 2;
  }

  BitInput  bitin(*in);
  BitOutput bitout(*out);
  Huffman   huffman;

  while(!in->fail())
  {
    for(bool b : huffman.encode(in->get()))
    {
      bitout.output_bit(b);
    }
  }
  for(bool b : huffman.encode(Huffman::HEOF))
  {
    bitout.output_bit(b);
  }
  return 0;
}
