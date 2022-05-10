#include <iostream>
#include <fstream>
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
  std::string filename(argv[1]);
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
    char in_byte = in->get();
    if(in_byte != -1)
    {
      for(bool b : huffman.encode(in_byte))
      {
        bitout.output_bit(b);
      }
    }
  }
  for(bool b : huffman.encode(Huffman::HEOF))
  {
    bitout.output_bit(b);
  }
  return 0;
}
