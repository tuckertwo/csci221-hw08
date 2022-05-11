#include <iostream>
#include <fstream>
#include <cassert>
#include "huffman.hh"
#include "bitio.hh"

void encwrite(Huffman& huff, BitOutput& bitout, int in_byte)
{
  for(bool b : huff.encode(in_byte))
  {
    bitout.output_bit(b);
  }
}

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cerr << "Incorrect number of arguments" << std::endl;
    return 1;
  }

  for(int argn = 1; argn<argc; argn++)
  {
    std::istream* in;
    std::ostream* out;
    std::string filename(argv[argn]);
    if(filename == "-")
    {
      in  = &std::cin;
      out = &std::cout;
    }
    else
    {
      std::ifstream* infile = new std::ifstream(filename);
      if(infile->fail() || infile->bad())
      {
        std::cerr<<"Cannot open "<<filename<<std::endl;
        return 2;
      }

      std::ofstream* outfile = new std::ofstream(filename+".comp");
      if(outfile->fail() || outfile->bad())
      {
        std::cerr<<"Cannot open "<<filename<<".comp"<<std::endl;
        return 2;
      }

      in  = infile;
      out = outfile;
    }

    BitInput  bitin(*in);
    BitOutput bitout(*out);
    Huffman   huffman;

    while(!in->fail())
    {
      int in_byte = in->get();
      assert(in_byte >= -1);
      if(in_byte >= 0)
      {
        encwrite(huffman, bitout, in_byte);
      }
    }
    encwrite(huffman, bitout, Huffman::HEOF);
  }
  return 0;
}
