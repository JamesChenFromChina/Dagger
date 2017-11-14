
#ifndef DCIRCULARBUFFER_H
#define DCIRCULARBUFFER_H

#include <cstdint>
#include <cstring>


class DCircularBuffer {
private:
    size_t _capacity;
    uint8_t *_buffer;
    size_t _rpos;
    size_t _wpos;

public:
    DCircularBuffer() : _capacity(0) {}
    DCircularBuffer(std::size_t size) : _capacity(size), _buffer(new uint8_t[size]), _rpos(0), _wpos(0) { }
    DCircularBuffer(const DCircularBuffer &buf) {
    }

    DCircularBuffer(DCircularBuffer &&buf) noexcept {
    }

    virtual ~DCircularBuffer() noexcept {
        delete[] _buffer;
    }



    void Expand(std::size_t size) {
        _capacity = size;
    }

    std::size_t Capacity() {
        return _capacity;
    }

    void Store(const uint8_t *data,size_t size) {
        memcpy(_buffer + _wpos, data, size);
        _wpos += size;
    }

    void Read(uint8_t *data,size_t size) {
        memcpy(data, _buffer + _rpos, size);
        _rpos += size;
    }
};

#endif /* DCIRCULARBUFFER_H */




