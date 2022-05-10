#include <cassert>
#include "bitio.hh"

BitInput::BitInput(std::istream& is)
  : is_(is), buf_(0), buf_len_(0) {}

// Read and output one bit from the input stream, MSB-first.
// So, for a file like so: 0101 0100  0101 0101  0100 0011  0100 1011 …
// repeated invocations of input_bit() would return 0, 1, 0, 1, 0, 1, 0, 0….
bool BitInput::input_bit()
{
  if(buf_len_ == 0) // If the buffer is empty,…
  {
    assert(!is_.fail()); // …make sure bad stuff isn't going on, and then…
    buf_ = is_.get();
    buf_len_ = 8; // Length (in bits) of a char.
  }

  bool retval = buf_>>8 & 0x1; // Grab the MSB of the buffer.
  buf_        = buf_<<1;
  buf_len_--;
  return retval;
}

BitOutput::BitOutput(std::ostream& os)
  : os_(os), buf_(0), buf_len_(0) {}

// Wrap up if the object gets destroyed with data remaining in the
// buffer.
BitOutput::~BitOutput()
{
  if(buf_len_ != 0)
  {
    os_.put(buf_ << (8-buf_len_));
    os_.flush();
  }
}

void BitOutput::output_bit(bool out)
{
  assert(buf_len_<=8);
  if(buf_len_ == 8) // If the buffer is full,…
  {
    os_.put(buf_); // …then purge the buffer.
    buf_len_ = 0;
    buf_     = 0;
  }

  buf_ = (buf_<<1) + (out);
  buf_len_++;
}
