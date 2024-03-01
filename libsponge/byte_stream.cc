#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { _capacity = capacity; }

size_t ByteStream::write(const string &data) {
    size_t length = min(remaining_capacity(), data.length());
    _written_bytes += length;
    _bufferlist.append(BufferList(data.substr(0, length)));
    return length;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t length = min(_bufferlist.size(), len);
    string str = _bufferlist.concatenate();
    return str.substr(0, length);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t length = min(_bufferlist.size(), len);
    _read_bytes += length;
    _bufferlist.remove_prefix(length);
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    size_t length = min(_bufferlist.size(), len);
    string str = peek_output(length);
    pop_output(length);
    return str;
}

void ByteStream::end_input() { _end_input = true; }

bool ByteStream::input_ended() const { return _end_input; }

size_t ByteStream::buffer_size() const { return _bufferlist.size(); }

bool ByteStream::buffer_empty() const { return _bufferlist.size() == 0; }

bool ByteStream::eof() const { return buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return _written_bytes; }

size_t ByteStream::bytes_read() const { return _read_bytes; }

size_t ByteStream::remaining_capacity() const { return _capacity - _bufferlist.size(); }
